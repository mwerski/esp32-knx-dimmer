#pragma once
// Ziel-Partitionstabelle und Erzeugung des Binaerformats (wie gen_esp32part.py).
// Bewusst ohne ESP-Abhaengigkeiten, damit sich die Erzeugung auf dem PC testen laesst.
#include <stdint.h>
#include <string.h>

namespace bruecke
{
    struct Eintrag
    {
        uint8_t typ;      // 0 = app, 1 = data
        uint8_t subtyp;   // app: 0x10 ota_0, 0x11 ota_1; data: 0x00 ota, 0x02 nvs, 0x82 spiffs
        uint32_t offset;
        uint32_t groesse;
        const char *name; // max. 15 Zeichen
        uint32_t flags;
    };

    // MUSS partitions/ziel.csv entsprechen
    static const Eintrag ZIEL[] = {
        {0x01, 0x02, 0x009000, 0x005000, "nvs", 0},
        {0x01, 0x00, 0x00E000, 0x002000, "otadata", 0},
        {0x00, 0x10, 0x010000, 0x1D0000, "app0", 0},
        {0x00, 0x11, 0x1E0000, 0x1D0000, "app1", 0},
        {0x01, 0x82, 0x3B0000, 0x050000, "spiffs", 0},
    };
    static const int ZIEL_ANZAHL = sizeof(ZIEL) / sizeof(ZIEL[0]);

    static const uint32_t TABELLE_LAENGE = 0xC00; // ESP_PARTITION_TABLE_MAX_LEN
    static const uint32_t EINTRAG_LAENGE = 32;

    static inline void schreibeLE32(uint8_t *p, uint32_t v)
    {
        p[0] = v & 0xFF;
        p[1] = (v >> 8) & 0xFF;
        p[2] = (v >> 16) & 0xFF;
        p[3] = (v >> 24) & 0xFF;
    }

    // Erzeugt die Tabelle in out (mindestens TABELLE_LAENGE Byte).
    // md5(daten, laenge, ergebnis16) wird von aussen bereitgestellt (ROM auf dem ESP, OpenSSL im Test).
    template <typename Md5Fn>
    void baueTabelle(uint8_t *out, Md5Fn md5)
    {
        memset(out, 0xFF, TABELLE_LAENGE);
        uint8_t *p = out;
        for (int i = 0; i < ZIEL_ANZAHL; i++, p += EINTRAG_LAENGE)
        {
            p[0] = 0xAA; // ESP_PARTITION_MAGIC 0x50AA, little endian
            p[1] = 0x50;
            p[2] = ZIEL[i].typ;
            p[3] = ZIEL[i].subtyp;
            schreibeLE32(p + 4, ZIEL[i].offset);
            schreibeLE32(p + 8, ZIEL[i].groesse);
            memset(p + 12, 0, 16);
            memcpy(p + 12, ZIEL[i].name, strnlen(ZIEL[i].name, 15));
            schreibeLE32(p + 28, ZIEL[i].flags);
        }
        // MD5-Eintrag: 0xEBEB, 14 x 0xFF, MD5 ueber alle vorherigen Eintraege
        p[0] = 0xEB;
        p[1] = 0xEB;
        memset(p + 2, 0xFF, 14);
        md5(out, (uint32_t)(p - out), p + 16);
    }
} // namespace bruecke
