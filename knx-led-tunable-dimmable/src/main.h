#pragma once

#include <Arduino.h>
#include <knx.h>
#include "../knxprod.h"
#include "settings.h"
#include "credentials.h"

#include <esp-knx-common.h>
#include <esp-knx-webserver.h>
#include <esp-knx-led.h>

#if defined(ESP32)
    #include <WiFi.h>
    #include <mDNS.h>
#elif defined(ESP8266)
    #include <ESP8266WiFi.h>
    #include <ESP8266mDNS.h>
#elif defined(LIBRETINY)
    #include <WiFi.h>
    #include <mDNS.h>
#else
    #error "Wrong hardware. Not ESP32, ESP8266 or LIBRETINY"
#endif

// ----------------------------------------------------
// Global state
// ----------------------------------------------------
extern bool knxConfigOk;
extern bool initSent;
extern unsigned long lastHeartbeat;

// ----------------------------------------------------
// Lights
// ----------------------------------------------------
extern KnxLed Light1;
extern KnxLed Light2;
extern KnxLed Light3;
extern KnxLed Light4;
extern KnxLed Light5;

// ----------------------------------------------------
// KNX Webserver
// ----------------------------------------------------
extern KnxWebserver knxWebServ;

// ----------------------------------------------------
// Arduino
// ----------------------------------------------------
void setup();
void loop();

// ----------------------------------------------------
// KNX callbacks
// ----------------------------------------------------
void knxCallback(GroupObject &go);

// ----------------------------------------------------
// Light status callbacks (MÜSSEN exakt passen)
// ----------------------------------------------------
void statusCallback_L1(bool state);
void statusCallback_L2(bool state);
void statusCallback_L3(bool state);
void statusCallback_L4(bool state);
void statusCallback_L5(bool state);

// ----------------------------------------------------
// Brightness callbacks
// ----------------------------------------------------
void responseBrightnessCallback_L1(uint8_t value);
void responseBrightnessCallback_L2(uint8_t value);
void responseBrightnessCallback_L3(uint8_t value);
void responseBrightnessCallback_L4(uint8_t value);
void responseBrightnessCallback_L5(uint8_t value);

// ----------------------------------------------------
// Temperature callbacks (nur wo CCT/TW existiert)
// ----------------------------------------------------
void responseTemperatureCallback_L1(uint16_t value);
void responseTemperatureCallback_L2(uint16_t value);

// ----------------------------------------------------
// Color callbacks (nur RGB / RGBW / RGBCCT)
// ----------------------------------------------------
void responseColorHsvCallback_L1(hsv_t value);
void responseColorRgbCallback_L1(rgb_t value);

// ----------------------------------------------------
// Helper / Utils
// ----------------------------------------------------
static inline void sep();
static inline void printActive(uint8_t ch, const char* type, uint32_t active);

// ----------------------------------------------------
// Light setup helpers
// ----------------------------------------------------
static void setupDim(KnxLed& L, uint8_t ch, uint8_t pwmPin);
static void setupRgb(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin);
static void setupRgbw(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t wPin);
static void setupCct(KnxLed& L, uint8_t ch, uint8_t cwPin, uint8_t wwPin);
static void setupRgbcct(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t cwPin, uint8_t wwPin);
