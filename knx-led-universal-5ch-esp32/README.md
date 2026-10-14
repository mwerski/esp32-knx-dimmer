# KNX LED Dimmer, universal 5 channel (ESP32)

KNX IP (KNXnet/IP Routing über WLAN) PWM-Dimmer für bis zu 5 Kanäle, wahlweise als RGBCCT, RGBW,
RGB, Tunable White oder einfacher Dimmer kombiniert. Die Konfiguration erfolgt über die ETS.

## Produkte

Die Firmware wird für zwei ETS-Applikationen gebaut. Das Produkt wird über ein Build-Flag gewählt,
dazu gehört jeweils ein eigener Header aus Kaenx Creator.

| Produkt | Build-Flag | Kaenx-Projekt | Header |
|---|---|---|---|
| ESP32 PWM Dimmer (universal) | – | `knx-esp32-pwm-dimmer.ae-manu` | `knxprod_universal.h` |
| Yeelight YLDL01YL (Meteorite) | `-DPRODUCT_YLDL01YL` | `yeelight-yldl01yl.ae-manu` | `knxprod_yldl01yl.h` |

### Yeelight YLDL01YL (Meteorite)

Feste Hardware, die Pins kommen nicht aus der ETS:

| GPIO | Funktion |
|---|---|
| 33, 26, 27 | Uplight (AmbientLight) Rot, Grün, Blau |
| 21, 19 | Downlight Kaltweiß, Warmweiß |
| 23 | Nightlight |
| 22 | Versorgung des LED-Treibers (alle drei Lichter) |

- Das Nightlight folgt dem Downlight (Kanal 2): beide werden mit demselben Wert gedimmt, die
  festen Dimmkurven teilen den Bereich auf (Nightlight unten, Downlight oben, kurze Überblendung).
  Die Kurven erzeugt `tools/gen_yldl01yl_curves.py` (Parameter im Skript) in `src/yldl01yl_curves.h`.
- Die LED-Versorgung ist über die Gruppenobjekte „LED-Versorgung schalten“ / „Status“ schaltbar.

## Funktionen

- **Dim-to-Warm** (Tunable White): die Farbtemperatur folgt der Helligkeit (warm beim Abdimmen),
  ETS-Parameter pro CCT-Kanal. Ein expliziter Farbtemperatur-Befehl beendet es bis zum nächsten Einschalten.
- **Verhalten nach Spannungswiederkehr** (ETS): letzter Zustand, aus, oder ein mit Einschalthelligkeit.
  Der letzte Zustand wird im NVS gespeichert, erst wenn er sich 5 s nicht mehr geändert hat.
- **Einschaltfarbe** (RGB-Kanal 1, ETS): letzter Zustand (Farbe bzw. Weißton) oder feste Farbe.
  Ist zusätzlich eine feste Einschaltfarbtemperatur gesetzt, hat die feste Farbe Vorrang.
- **Dimmkurven** für allgemeine Hardware über `settings.h` (`DIM_CURVE_CHx`, Bibliothek `dimming-curves`).
- **PWM-Frequenz** über die ETS (gilt für alle Kanäle).

## Web-Oberfläche

Erreichbar unter der IP des Geräts (Zugangsdaten `WWW_USER` / `WWW_PASS` in `credentials.h`).

- KNX-Modus (Programmiermodus), OTA, Firmware-Upload, Neustart, Geräte- und WLAN-Informationen.
- **WiFi**: startet das WLAN-Einrichtungsportal (siehe unten).
- **GPIO-Testseite** `/gpiotest` (`GPIO_TEST_PAGE` in `settings.h`): schaltet einzelne GPIOs auf
  LOW, 5 %, 25 % oder HIGH, um die Pinbelegung unbekannter Hardware ohne seriellen Zugang zu ermitteln.
  Die Spalte „Role“ zeigt die aktuelle Belegung. Ein Test übersteuert das Licht am Pin bis zum
  nächsten Neustart.

## WLAN

- Bei mehreren Access Points mit gleicher SSID verbindet sich das Gerät mit dem stärksten.
- **Einrichtungsportal** (WiFiManager): startbar über die Web-Oberfläche, das Gruppenobjekt
  „WLAN-Portal starten“ oder automatisch, wenn das WLAN 10 Minuten weg ist.
  - Die bestehende Verbindung bleibt aktiv, das Portal ist unter der IP des Geräts und über einen
    eigenen Access Point (SSID = Hostname, Passwort `WM_PASS`) erreichbar.
  - Funktionieren die neuen Zugangsdaten nicht, werden die alten wiederhergestellt; ohne Eingabe
    schließt sich das Portal nach 5 Minuten. Zeiten: `WIFI_PORTAL_*` in `settings.h`.
- Für zuverlässiges ETS-Programmieren über KNX IP Routing braucht das Gerät einen guten Empfang
  (Multicast wird im WLAN nicht wiederholt). Hilfreich: „Multicast Enhancement“ (UniFi) bzw.
  Multicast-to-Unicast am Access Point, DTIM 1.

## ETS-Applikation ändern (Kaenx Creator)

1. `.ae-manu` in Kaenx Creator öffnen und ändern, bei Änderungen an Parametern oder Gruppenobjekten
   die Applikationsversion erhöhen.
2. `.knxprod` **und** den Header exportieren und den Header unter dem Namen aus der Tabelle oben
   ablegen. Kaenx legt den Parameterspeicher beim Export selbst an, die Offsets im Header sind
   deshalb nur aus dem Export verlässlich.
3. Die Firmware prüft Applikationsnummer und -version (`MAIN_*` im Header): nach einem
   Versionswechsel Firmware aufspielen und direkt danach die Applikation programmieren.

Hinweis: Parameter, die in der ETS nicht sichtbar sind (nicht in den Dynamics eingehängt), schreibt
die ETS nicht ins Gerät, ihr Speicher bleibt 0. Die Firmware darf solche Parameter nicht auswerten.

## Werkzeuge

- `tools/gen_yldl01yl_curves.py`: Dimmkurven für Downlight und Nightlight des YLDL01YL.
- `tools/Partition-Bruecke`: stellt ein Gerät ohne seriellen Zugang per OTA auf eine neue
  Partitionstabelle um (siehe README dort).
