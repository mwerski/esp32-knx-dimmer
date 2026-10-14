# Partition-Brücke (ESP32-Solo, 4 MB)

Stellt ein ESP32-Gerät **ohne seriellen Zugriff** auf eine neue Partitionstabelle um und
installiert dabei die Zielfirmware. Ablauf: Brücke per OTA einspielen → Zielfirmware im Browser
hochladen → prüfen → umstellen.

Zieltabelle (`partitions/ziel.csv`, identisch in `src/partitionstabelle.h`):

| Name | Typ | Offset | Größe |
|---|---|---|---|
| nvs | data/nvs | 0x9000 | 0x5000 |
| otadata | data/ota | 0xE000 | 0x2000 |
| app0 | app/ota_0 | 0x10000 | 0x1D0000 |
| app1 | app/ota_1 | 0x1E0000 | 0x1D0000 |
| spiffs | data/spiffs | 0x3B0000 | 0x50000 |

## Sicherheitskonzept

- Der **Bootloader wird nie verändert**, `nvs` und `otadata` behalten ihre Lage
  (KNX-Konfiguration und WLAN-Daten bleiben erhalten).
- Die Brücke schreibt die Zielfirmware nur in einen Bereich, der ihren eigenen Code nicht
  berührt. Welcher das ist, erkennt sie selbst:
  - Brücke läuft ab 0x200000 (vorher lief Tasmota/Firmware aus `app0`) → Ziel `app0`
  - Brücke läuft ab 0x10000 (vorher lief die Firmware aus `app1`) → Ziel `app1`
- Die neue Tabelle wird vor dem Schreiben mit der Prüfroutine des Bootloaders kontrolliert
  (inkl. MD5). Die Erzeugung ist byteidentisch mit Espressifs `gen_esp32part.py`.
- **Einziger kritischer Moment:** das Schreiben der Tabelle (ein Sektor, Sekundenbruchteile).
  Ein Stromausfall genau dann erfordert seriellen Zugriff.

| Zeitpunkt eines Stromausfalls | Folge |
|---|---|
| vor dem Upload | bisherige Firmware über „Abbrechen“ oder erneut OTA wiederherstellbar |
| während/nach dem Upload, vor dem Umstellen | Brücke startet wieder, Vorgang wiederholbar |
| beim Schreiben der Tabelle | **serieller Zugriff nötig** |
| danach | unkritisch, Bootloader findet die Zielfirmware |

## Ablauf

1. **Bauen:** `pio run -e bruecke` → `.pio/build/bruecke/firmware.bin`
2. **Brücke einspielen**
   - aus Tasmota: *Firmware-Upgrade → Upgrade durch Datei-Upload* → `firmware.bin` der Brücke
   - aus Ihrer Firmware (ArduinoOTA): IP in `[env:bruecke_espota]` eintragen,
     `pio run -e bruecke_espota -t upload`
3. **WLAN:** Ist kein WLAN gespeichert, öffnet die Brücke den offenen Access Point
   `Partition-Bruecke-XXXX`. Verbinden, im Portal das WLAN wählen (Portal schließt nach 10 min).
   Die Zugangsdaten landen nur im WLAN-Speicher des ESP32.
4. **Webseite öffnen:** `http://bruecke.local` oder die IP aus Ihrem Router.
   Alle Voraussetzungen müssen grün sein.
5. **Zielfirmware hochladen:** die `firmware.bin` Ihrer Zielfirmware (nicht `factory.bin`).
   Die Seite zeigt Größe und den Anfang der im Abbild angehängten SHA-256 – mit Ihrer Datei
   vergleichen: `ls -l firmware.bin` (Größe) und `tail -c 32 firmware.bin | xxd -p | head -c 16`
   (dieselben 16 Hex-Zeichen).
6. **Umstellen:** Bestätigen, Stromversorgung nicht unterbrechen. Nach etwa 3 Sekunden startet
   die Zielfirmware im neuen Layout.

## Hinweise

- Die Webseite der Brücke hat keine Anmeldung; nur kurz und im eigenen Netz betreiben.
- Die Brücke hat bewusst **kein** ArduinoOTA: ein normales OTA-Update würde nach der alten
  Tabelle schreiben.
- Gebaut mit derselben Plattform wie die Zielfirmware (Tasmota-Plattform 2024.05.00,
  Einkern-Framework Arduino 2.0.17 / ESP-IDF 4.4.7).
