// Partition-Bruecke fuer ESP32 (Solo1, 4 MB)
//
// Wird per OTA (Tasmota oder eigene Firmware) in einen App-Bereich geladen und
//  1. nimmt die Zielfirmware per Web-Upload entgegen und schreibt sie roh in den
//     Bereich, den sie in der NEUEN Tabelle belegen wird (ohne den laufenden Code
//     zu beruehren),
//  2. prueft das Abbild,
//  3. schreibt die neue Partitionstabelle, setzt otadata und startet neu.
//
// Bis zum Schreiben der Zielfirmware bleibt die alte Firmware als Rueckfallebene erhalten.
// Kritisch ist nur das Schreiben der Tabelle selbst (ein Sektor).

#include <Arduino.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WiFi.h>
#include <WiFiManager.h>

#include <esp_app_format.h>
#include <esp_flash.h>
#include <esp_flash_partitions.h>
#include <esp_image_format.h>
#include <esp_ota_ops.h>
#include <esp_partition.h>
#include <esp_rom_crc.h>
#include <esp_rom_md5.h>

#include "partitionstabelle.h"

using namespace bruecke;

static const uint32_t SEKTOR = 0x1000;
static const uint32_t TABELLE_ADR = 0x8000;
static const uint32_t FLASH_SOLL = 0x400000;

static WebServer server(80);

enum class Zustand
{
    Bereit,       // wartet auf Upload
    Hochgeladen,  // Abbild geprueft, Umstellung moeglich
    Umgestellt,   // Tabelle geschrieben, Neustart folgt
    Gesperrt      // Voraussetzungen nicht erfuellt
};

static Zustand zustand = Zustand::Gesperrt;
static String meldung;          // letzte Meldung fuer die Webseite
static String voraussetzungen;  // Ergebnis der Pruefungen (HTML)

// Laufende Firmware (alte Tabelle)
static uint32_t laufStart = 0, laufEnde = 0;
static const esp_partition_t *laufPartition = nullptr;

// Ziel fuer die neue Firmware (Bereich der NEUEN Tabelle)
static const Eintrag *ziel = nullptr;

// Upload
static uint32_t geschrieben = 0, geloeschtBis = 0;
static bool uploadFehler = false;
static esp_app_desc_t zielBeschreibung;
static uint32_t abbildLaenge = 0;

static uint32_t neustartUm = 0;

// ---------------------------------------------------------------------------
// Hilfsfunktionen
// ---------------------------------------------------------------------------

static void romMd5(const uint8_t *daten, uint32_t laenge, uint8_t *ergebnis)
{
    md5_context_t ctx;
    esp_rom_md5_init(&ctx);
    esp_rom_md5_update(&ctx, daten, laenge);
    esp_rom_md5_final(ergebnis, &ctx);
}

static String hex(uint32_t v)
{
    char b[12];
    snprintf(b, sizeof(b), "0x%06X", v);
    return String(b);
}

static bool ueberlappt(uint32_t a1, uint32_t a2, uint32_t b1, uint32_t b2)
{
    return a1 < b2 && b1 < a2;
}

static const Eintrag *zielEintrag(uint8_t typ, uint8_t subtyp)
{
    for (int i = 0; i < ZIEL_ANZAHL; i++)
        if (ZIEL[i].typ == typ && ZIEL[i].subtyp == subtyp)
            return &ZIEL[i];
    return nullptr;
}

// Loescht sektorweise mit kurzer Pause (Einkern-ESP32: Idle-Task/Watchdog bedienen)
static bool loescheBereich(uint32_t start, uint32_t laenge)
{
    for (uint32_t a = start; a < start + laenge; a += SEKTOR)
    {
        if (esp_flash_erase_region(NULL, a, SEKTOR) != ESP_OK)
            return false;
        delay(1);
    }
    return true;
}

static String tabelleAlsHtml(const esp_partition_info_t *t)
{
    String s = "<table><tr><th>Name</th><th>Typ</th><th>Subtyp</th><th>Offset</th><th>Gr&ouml;&szlig;e</th></tr>";
    for (uint32_t i = 0; i < ESP_PARTITION_TABLE_MAX_ENTRIES; i++)
    {
        if (t[i].magic != ESP_PARTITION_MAGIC)
            break;
        char name[17] = {0};
        memcpy(name, t[i].label, 16);
        s += "<tr><td>" + String(name) + "</td><td>" + String(t[i].type) + "</td><td>0x" + String(t[i].subtype, HEX) +
             "</td><td>" + hex(t[i].pos.offset) + "</td><td>" + hex(t[i].pos.size) + "</td></tr>";
    }
    return s + "</table>";
}

// ---------------------------------------------------------------------------
// Voraussetzungen
// ---------------------------------------------------------------------------

static void pruefeVoraussetzungen()
{
    bool ok = true;
    String s;
    auto zeile = [&](bool gut, const String &text) {
        s += String(gut ? "&#9989; " : "&#10060; ") + text + "<br>";
        ok = ok && gut;
    };

    uint32_t flash = 0;
    esp_flash_get_size(NULL, &flash);
    zeile(flash == FLASH_SOLL, "Flash-Gr&ouml;&szlig;e " + String(flash / 1024) + " KB (erwartet 4096 KB)");

    // Aktuelle Tabelle lesen und pruefen
    static uint8_t alt[TABELLE_LAENGE];
    bool lesenOk = esp_flash_read(NULL, alt, TABELLE_ADR, TABELLE_LAENGE) == ESP_OK;
    int anzahl = 0;
    bool altGueltig = lesenOk && esp_partition_table_verify((const esp_partition_info_t *)alt, true, &anzahl) == ESP_OK;
    zeile(altGueltig, "Aktuelle Partitionstabelle g&uuml;ltig (" + String(anzahl) + " Eintr&auml;ge)");

    // NVS und otadata muessen gleich bleiben (KNX-Konfiguration, WLAN-Daten)
    if (altGueltig)
    {
        const esp_partition_info_t *t = (const esp_partition_info_t *)alt;
        for (int k = 0; k < 2; k++)
        {
            const Eintrag &z = ZIEL[k]; // nvs, otadata
            bool gefunden = false;
            for (int i = 0; i < anzahl; i++)
                if (t[i].type == z.typ && t[i].subtype == z.subtyp && t[i].pos.offset == z.offset && t[i].pos.size == z.groesse)
                    gefunden = true;
            zeile(gefunden, String(z.name) + " unver&auml;ndert bei " + hex(z.offset));
        }
    }

    // Neue Tabelle erzeugen und mit der Pruefroutine des Bootloaders kontrollieren
    static uint8_t neu[TABELLE_LAENGE];
    baueTabelle(neu, romMd5);
    int anzahlNeu = 0;
    zeile(esp_partition_table_verify((const esp_partition_info_t *)neu, true, &anzahlNeu) == ESP_OK && anzahlNeu == ZIEL_ANZAHL,
          "Neue Partitionstabelle g&uuml;ltig (MD5 gepr&uuml;ft)");

    // Laufende Firmware: Bereich, den die Bruecke tatsaechlich belegt (auf 64 KB aufgerundet)
    laufPartition = esp_ota_get_running_partition();
    laufStart = laufPartition->address;
    laufEnde = laufStart + ((ESP.getSketchSize() + 0xFFFF) & ~0xFFFFu);
    s += "Br&uuml;cke l&auml;uft aus <b>" + String(laufPartition->label) + "</b>, belegt " + hex(laufStart) + " bis " + hex(laufEnde) + "<br>";

    // Zielbereich: erster App-Bereich der neuen Tabelle, der die Bruecke nicht beruehrt
    ziel = nullptr;
    const Eintrag *kandidaten[2] = {zielEintrag(0x00, 0x10), zielEintrag(0x00, 0x11)};
    for (auto *k : kandidaten)
        if (k && !ueberlappt(k->offset, k->offset + k->groesse, laufStart, laufEnde))
        {
            ziel = k;
            break;
        }
    zeile(ziel != nullptr, ziel ? "Zielbereich f&uuml;r Ihre Firmware: <b>" + String(ziel->name) + "</b> (" + hex(ziel->offset) + ", max. " + String(ziel->groesse / 1024) + " KB)"
                                : String("Kein Zielbereich ohne &Uuml;berschneidung mit der Br&uuml;cke"));

    // Der zu loeschende Datenbereich darf die Bruecke ebenfalls nicht beruehren
    const Eintrag *spiffs = zielEintrag(0x01, 0x82);
    zeile(spiffs && !ueberlappt(spiffs->offset, spiffs->offset + spiffs->groesse, laufStart, laufEnde),
          "Datenbereich spiffs (" + hex(spiffs ? spiffs->offset : 0) + ") ber&uuml;hrt die Br&uuml;cke nicht");

    voraussetzungen = s + "<h3>Aktuelle Tabelle</h3>" + (altGueltig ? tabelleAlsHtml((const esp_partition_info_t *)alt) : String("nicht lesbar")) +
                      "<h3>Neue Tabelle</h3>" + tabelleAlsHtml((const esp_partition_info_t *)neu);
    zustand = ok ? Zustand::Bereit : Zustand::Gesperrt;
}

// ---------------------------------------------------------------------------
// Upload und Pruefung der Zielfirmware
// ---------------------------------------------------------------------------

static void pruefeAbbild()
{
    esp_partition_pos_t pos = {ziel->offset, ziel->groesse};
    esp_image_metadata_t md = {};
    if (esp_image_verify(ESP_IMAGE_VERIFY, &pos, &md) != ESP_OK)
    {
        meldung = "Abbild ung&uuml;ltig (Pr&uuml;fsumme/Format). Bitte die firmware.bin Ihrer Zielfirmware hochladen.";
        return;
    }
    abbildLaenge = md.image_len;

    esp_image_header_t kopf;
    esp_flash_read(NULL, &kopf, ziel->offset, sizeof(kopf));
    if (kopf.chip_id != ESP_CHIP_ID_ESP32)
    {
        meldung = "Abbild ist nicht f&uuml;r den ESP32 gebaut.";
        return;
    }

    esp_flash_read(NULL, &zielBeschreibung, ziel->offset + sizeof(esp_image_header_t) + sizeof(esp_image_segment_header_t), sizeof(zielBeschreibung));
    if (zielBeschreibung.magic_word != ESP_APP_DESC_MAGIC_WORD)
    {
        meldung = "Keine Anwendungsbeschreibung im Abbild gefunden.";
        return;
    }
    // Versehentlich die Bruecke selbst hochgeladen? (Arduino-Builds fuellen den Projektnamen nicht,
    // daher Vergleich ueber die angehaengte SHA-256 des Abbilds)
    uint8_t laufSha[32];
    if (esp_partition_get_sha256(laufPartition, laufSha) == ESP_OK && memcmp(laufSha, md.image_digest, 32) == 0)
    {
        meldung = "Das ist die Br&uuml;cke selbst, nicht Ihre Zielfirmware.";
        return;
    }

    zustand = Zustand::Hochgeladen;
    char sha[17];
    for (int i = 0; i < 8; i++)
        snprintf(sha + 2 * i, 3, "%02x", md.image_digest[i]);
    meldung = "Abbild gepr&uuml;ft: <b>" + String(abbildLaenge) + " Byte</b>, SHA-256 beginnt mit <b>" + String(sha) +
              "</b>, ESP-IDF " + String(zielBeschreibung.idf_ver) +
              ".<br>Vergleichen Sie die Gr&ouml;&szlig;e mit Ihrer <code>firmware.bin</code>, bevor Sie umstellen.";
}

static void beiUpload()
{
    HTTPUpload &up = server.upload();
    switch (up.status)
    {
        case UPLOAD_FILE_START:
            uploadFehler = !(zustand == Zustand::Bereit || zustand == Zustand::Hochgeladen) || !ziel;
            if (uploadFehler)
            {
                meldung = "Upload derzeit nicht m&ouml;glich.";
                return;
            }
            zustand = Zustand::Bereit; // ein neuer Upload macht ein frueheres Ergebnis ungueltig
            geschrieben = 0;
            geloeschtBis = ziel->offset;
            meldung = "";
            break;

        case UPLOAD_FILE_WRITE:
        {
            if (uploadFehler)
                return;
            if (geschrieben == 0 && up.buf[0] != ESP_IMAGE_HEADER_MAGIC)
            {
                uploadFehler = true;
                meldung = "Datei ist kein ESP32-Programmabbild (firmware.bin erwartet, nicht factory.bin).";
                return;
            }
            if (geschrieben + up.currentSize > ziel->groesse)
            {
                uploadFehler = true;
                meldung = "Abbild zu gro&szlig; f&uuml;r den Zielbereich.";
                return;
            }
            const uint32_t adr = ziel->offset + geschrieben;
            const uint32_t ende = adr + up.currentSize;
            while (geloeschtBis < ende) // Sektoren erst bei Bedarf loeschen
            {
                if (esp_flash_erase_region(NULL, geloeschtBis, SEKTOR) != ESP_OK)
                {
                    uploadFehler = true;
                    meldung = "Fehler beim L&ouml;schen bei " + hex(geloeschtBis);
                    return;
                }
                geloeschtBis += SEKTOR;
            }
            if (esp_flash_write(NULL, up.buf, adr, up.currentSize) != ESP_OK)
            {
                uploadFehler = true;
                meldung = "Fehler beim Schreiben bei " + hex(adr);
                return;
            }
            geschrieben += up.currentSize;
            break;
        }

        case UPLOAD_FILE_END:
            if (!uploadFehler)
                pruefeAbbild();
            break;

        case UPLOAD_FILE_ABORTED:
            uploadFehler = true;
            meldung = "Upload abgebrochen.";
            break;
    }
}

// ---------------------------------------------------------------------------
// Umstellung
// ---------------------------------------------------------------------------

static bool schreibeUndPruefe(uint32_t adr, const uint8_t *daten, uint32_t laenge)
{
    static uint8_t kontrolle[SEKTOR];
    for (int versuch = 0; versuch < 3; versuch++)
    {
        if (esp_flash_erase_region(NULL, adr, SEKTOR) != ESP_OK)
            continue;
        if (esp_flash_write(NULL, daten, adr, laenge) != ESP_OK)
            continue;
        if (esp_flash_read(NULL, kontrolle, adr, laenge) == ESP_OK && memcmp(kontrolle, daten, laenge) == 0)
            return true;
    }
    return false;
}

static bool umstellen(String &fehler)
{
    // 1. Neuen Datenbereich leeren (enthaelt sonst Reste der alten App-Bereiche)
    const Eintrag *spiffs = zielEintrag(0x01, 0x82);
    if (!loescheBereich(spiffs->offset, spiffs->groesse))
    {
        fehler = "Datenbereich konnte nicht gel&ouml;scht werden (noch nichts ver&auml;ndert).";
        return false;
    }

    // 2. Neue Tabelle erzeugen und nochmals pruefen
    static uint8_t sektor[SEKTOR];
    memset(sektor, 0xFF, SEKTOR);
    baueTabelle(sektor, romMd5);
    int anzahl = 0;
    if (esp_partition_table_verify((const esp_partition_info_t *)sektor, true, &anzahl) != ESP_OK)
    {
        fehler = "Neue Tabelle ung&uuml;ltig (noch nichts ver&auml;ndert).";
        return false;
    }

    // 3. KRITISCH: Tabelle schreiben (ein Sektor)
    if (!schreibeUndPruefe(TABELLE_ADR, sektor, SEKTOR))
    {
        fehler = "SCHREIBEN DER TABELLE FEHLGESCHLAGEN. Ger&auml;t NICHT neu starten und mich kontaktieren!";
        return false;
    }

    // 4. otadata: ohne gueltige Eintraege startet der Bootloader ota_0
    const Eintrag *otadata = zielEintrag(0x01, 0x00);
    if (!loescheBereich(otadata->offset, otadata->groesse))
    {
        fehler = "otadata konnte nicht gel&ouml;scht werden; Bootloader w&auml;hlt trotzdem ein g&uuml;ltiges Abbild.";
        return true;
    }
    if (ziel->subtyp == 0x11) // Ziel ist ota_1: Auswahl ausdruecklich setzen (Sequenz 2 -> ota_1)
    {
        esp_ota_select_entry_t e;
        memset(&e, 0xFF, sizeof(e));
        e.ota_seq = 2;
        e.ota_state = ESP_OTA_IMG_UNDEFINED;
        e.crc = esp_rom_crc32_le(UINT32_MAX, (const uint8_t *)&e.ota_seq, sizeof(e.ota_seq));
        static uint8_t ota[SEKTOR];
        memset(ota, 0xFF, SEKTOR);
        memcpy(ota, &e, sizeof(e));
        if (!schreibeUndPruefe(otadata->offset, ota, SEKTOR))
            fehler = "otadata f&uuml;r ota_1 nicht geschrieben; es startet ota_0 (die Br&uuml;cke), Umstellung bitte wiederholen.";
    }
    return true;
}

// ---------------------------------------------------------------------------
// Webseiten
// ---------------------------------------------------------------------------

static const char *STIL =
    "<style>body{font-family:sans-serif;max-width:800px;margin:1em auto;padding:0 1em}"
    "table{border-collapse:collapse;margin:.5em 0}td,th{border:1px solid #999;padding:2px 8px;font-family:monospace}"
    ".box{border:1px solid #999;padding:1em;margin:1em 0}.warn{background:#fee}button{padding:.5em 1em}</style>";

static void seite()
{
    String h = "<!DOCTYPE html><html><head><meta charset='utf-8'><meta name='viewport' content='width=device-width'>"
               "<title>Partition-Br&uuml;cke</title>" +
               String(STIL) + "</head><body><h1>Partition-Br&uuml;cke</h1>";

    if (meldung.length())
        h += "<div class='box'>" + meldung + "</div>";

    h += "<div class='box'><h2>Voraussetzungen</h2>" + voraussetzungen + "</div>";

    if (zustand == Zustand::Bereit || zustand == Zustand::Hochgeladen)
    {
        h += "<div class='box'><h2>1. Zielfirmware hochladen</h2>"
             "<p>Die <code>firmware.bin</code> Ihrer Zielfirmware (nicht <code>firmware.factory.bin</code>). "
             "Achtung: Damit wird die bisherige Firmware im Zielbereich &uuml;berschrieben.</p>"
             "<input type='file' id='f' accept='.bin'> <button onclick='hoch()'>Hochladen</button> <span id='p'></span></div>"
             "<script>function hoch(){var f=document.getElementById('f').files[0];if(!f)return;"
             "var d=new FormData();d.append('firmware',f);var x=new XMLHttpRequest();"
             "x.upload.onprogress=function(e){document.getElementById('p').textContent=Math.round(e.loaded*100/e.total)+' %';};"
             "x.onload=function(){location.reload();};x.open('POST','/upload');x.send(d);}</script>";
    }

    if (zustand == Zustand::Hochgeladen)
    {
        h += "<div class='box warn'><h2>2. Umstellen</h2>"
             "<p>Schreibt die neue Partitionstabelle und startet Ihre Firmware. W&auml;hrend der wenigen Sekunden "
             "darf die Stromversorgung nicht unterbrochen werden.</p>"
             "<form method='POST' action='/umstellen'><label><input type='checkbox' name='ok' value='JA' required> "
             "Ich habe verstanden, dass ein Stromausfall in diesem Moment einen seriellen Zugriff erfordert.</label><br><br>"
             "<button type='submit'>Partitionstabelle umstellen und neu starten</button></form></div>";
    }

    if (zustand == Zustand::Bereit && laufPartition)
    {
        h += "<div class='box'><h2>Abbrechen</h2><p>Zur&uuml;ck zur bisherigen Firmware, solange noch nichts hochgeladen wurde.</p>"
             "<form method='POST' action='/zurueck'><button type='submit'>Bisherige Firmware starten</button></form></div>";
    }

    if (zustand == Zustand::Umgestellt)
        h += "<div class='box'><h2>Fertig</h2><p>Neustart l&auml;uft. Ihre Firmware ist gleich unter ihrer gewohnten Adresse erreichbar.</p></div>";

    server.send(200, "text/html", h + "</body></html>");
}

static void beiUmstellen()
{
    if (zustand != Zustand::Hochgeladen || server.arg("ok") != "JA")
    {
        meldung = "Umstellung nicht m&ouml;glich (Abbild nicht gepr&uuml;ft oder Best&auml;tigung fehlt).";
        server.sendHeader("Location", "/");
        server.send(303);
        return;
    }
    String fehler;
    if (umstellen(fehler))
    {
        zustand = Zustand::Umgestellt;
        meldung = fehler.length() ? fehler : String("Partitionstabelle umgestellt.");
        neustartUm = millis() + 3000;
    }
    else
    {
        meldung = fehler;
    }
    seite();
}

static void beiZurueck()
{
    // Nur vor einem Upload: anderer App-Bereich der ALTEN Tabelle (die bisherige Firmware) ist noch intakt
    const esp_partition_t *andere = esp_ota_get_next_update_partition(NULL);
    if (zustand == Zustand::Bereit && geschrieben == 0 && andere && esp_ota_set_boot_partition(andere) == ESP_OK)
    {
        meldung = "Bisherige Firmware wird gestartet.";
        neustartUm = millis() + 2000;
        zustand = Zustand::Gesperrt;
    }
    else
    {
        meldung = "Zur&uuml;ckschalten nicht m&ouml;glich.";
    }
    seite();
}

// ---------------------------------------------------------------------------

void setup()
{
    Serial.begin(115200);
    Serial.println("\nPartition-Bruecke startet");

    pruefeVoraussetzungen();

    // WLAN: gespeicherte Daten nutzen, sonst Konfigurationsportal (offener AP, 10 min)
    WiFiManager wm;
    wm.setConfigPortalTimeout(600);
    char apName[32];
    snprintf(apName, sizeof(apName), "Partition-Bruecke-%04X", (uint16_t)(ESP.getEfuseMac() >> 32));
    if (!wm.autoConnect(apName))
        ESP.restart(); // erneuter Versuch; die bisherige Firmware bleibt unangetastet

    MDNS.begin("bruecke");
    Serial.printf("Erreichbar unter http://%s oder http://bruecke.local\n", WiFi.localIP().toString().c_str());

    server.on("/", HTTP_GET, seite);
    server.on("/upload", HTTP_POST, []() { server.send(200, "text/plain", "ok"); }, beiUpload);
    server.on("/umstellen", HTTP_POST, beiUmstellen);
    server.on("/zurueck", HTTP_POST, beiZurueck);
    server.begin();
}

void loop()
{
    server.handleClient();
    if (neustartUm && (int32_t)(millis() - neustartUm) >= 0)
        ESP.restart();
    delay(1);
}
