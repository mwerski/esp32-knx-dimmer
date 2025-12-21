#include "main.h"

KnxLed Light1 = KnxLed();
KnxLed Light2 = KnxLed();
KnxLed Light3 = KnxLed();
KnxLed Light4 = KnxLed();
KnxLed Light5 = KnxLed();

bool knxConfigOk = false;
bool initSent = false;
KnxWebserver knxWebServ = KnxWebserver();
static uint32_t startMs = millis();
static uint32_t startUpDelay = 0;
static uint32_t heartbeatLastMs = 0;


// callback from knx value change
void knxCallback(GroupObject &go) {
	// callbacks are now handled in the class, not per instance,
	// this means, we have to check, which GroupObject is calling back
	#ifdef DEBUGGING
	Serial.print("KNX callback: ");
	Serial.println(go.asap());
	#endif
	switch (go.asap()) {
		case APP_KoGeneralDayNight: {
			bool itsDay;
			(ParamAPP_DayNight) ? (itsDay = go.value(DPT_Switch)) : (itsDay = !go.value(DPT_Switch));
			uint8_t defaultBrightness;
			if (ParamAPP_CH1_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH1_BrightnessDay : ParamAPP_CH1_BrightnessNight;
				Light1.configDefaultBrightness(defaultBrightness);
			} else if (ParamAPP_CH2_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH2_BrightnessDay : ParamAPP_CH2_BrightnessNight;
				Light2.configDefaultBrightness(defaultBrightness);
			} else if (ParamAPP_CH3_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH3_BrightnessDay : ParamAPP_CH3_BrightnessNight;
				Light3.configDefaultBrightness(defaultBrightness);
			} else if (ParamAPP_CH4_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH4_BrightnessDay : ParamAPP_CH4_BrightnessNight;
				Light4.configDefaultBrightness(defaultBrightness);
			} else if (ParamAPP_CH5_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH5_BrightnessDay : ParamAPP_CH5_BrightnessNight;
				Light5.configDefaultBrightness(defaultBrightness);
			}
			break;
		}

		case APP_KoCH1_Schalten: { Light1.switchLight(go.value(DPT_Switch)); break; }
		case APP_KoCH2_Schalten: { Light2.switchLight(go.value(DPT_Switch)); break; }
		case APP_KoCH3_Schalten: { Light3.switchLight(go.value(DPT_Switch)); break; }
		case APP_KoCH4_Schalten: { Light4.switchLight(go.value(DPT_Switch)); break; }
		case APP_KoCH5_Schalten: { Light5.switchLight(go.value(DPT_Switch)); break; }

		case APP_KoCH1_BrightnessAbsolute: { Light1.setBrightness(go.value(DPT_Percent_U8)); break; }
		case APP_KoCH2_BrightnessAbsolute: { Light2.setBrightness(go.value(DPT_Percent_U8)); break; }
		case APP_KoCH3_BrightnessAbsolute: { Light3.setBrightness(go.value(DPT_Percent_U8)); break; }
		case APP_KoCH4_BrightnessAbsolute: { Light4.setBrightness(go.value(DPT_Percent_U8)); break; }
		case APP_KoCH5_BrightnessAbsolute: { Light5.setBrightness(go.value(DPT_Percent_U8)); break; }

		case APP_KoCH1_BrightnessRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light1.setRelDimCmd(dimCmd);
			break;
		}
		case APP_KoCH2_BrightnessRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light2.setRelDimCmd(dimCmd);
			break;
		}
		case APP_KoCH3_BrightnessRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light3.setRelDimCmd(dimCmd);
			break;
		}
		case APP_KoCH4_BrightnessRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light4.setRelDimCmd(dimCmd);
			break;
		}
		case APP_KoCH5_BrightnessRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light5.setRelDimCmd(dimCmd);
			break;
		}

		case APP_KoCH1_ColortempAbsolute: { Light1.setTemperature(go.value(DPT_Value_2_Ucount)); break; }
		case APP_KoCH2_ColortempAbsolute: { Light2.setTemperature(go.value(DPT_Value_2_Ucount)); break; }

		case APP_KoCH1_ColortempRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light1.setRelTemperatureCmd(dimCmd);
			break;
		}
		case APP_KoCH2_ColortempRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light2.setRelTemperatureCmd(dimCmd);
			break;
		}

		case APP_KoCH1_ColorHSV: {
			hsv_t hsv;
			hsv.fromDPT232600(go.value(DPT_Colour_RGB));
			Light1.setHsv(hsv);
		}
		case APP_KoCH1_ColorRGB: {
			rgb_t rgb;
			rgb.fromDPT232600(go.value(DPT_Colour_RGB));
			Light1.setRgb(rgb);
			break;
		}

		case APP_KoCH1_HueAbsolute: {
			hsv_t hsv = Light1.getHsv();
			hsv.h = go.value(DPT_Percent_U8);
			Light1.setHsv(hsv);
			break;
		}
		case APP_KoCH1_HueRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light1.setRelHueCmd(dimCmd);
			break;
		}
		case APP_KoCH1_SaturationAbsolute: {
			hsv_t hsv = Light1.getHsv();
			hsv.s = go.value(DPT_Percent_U8);
			Light1.setHsv(hsv);
			break;
		}
		case APP_KoCH1_SaturationRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light1.setRelSaturationCmd(dimCmd);
			break;
		}
	}
}

void statusCallback_L1(bool state) {
	if (ParamAPP_CH1_Active) KoAPP_CH1_Status.value(state, DPT_Switch);
}

void statusCallback_L2(bool state) {
	if (ParamAPP_CH2_Active) KoAPP_CH2_Status.value(state, DPT_Switch);
}

void statusCallback_L3(bool state) {
	if (ParamAPP_CH3_Active) KoAPP_CH3_Status.value(state, DPT_Switch);
}

void statusCallback_L4(bool state) {
	if (ParamAPP_CH4_Active) KoAPP_CH4_Status.value(state, DPT_Switch);
}

void statusCallback_L5(bool state) {
	if (ParamAPP_CH5_Active) KoAPP_CH5_Status.value(state, DPT_Switch);
}

void responseBrightnessCallback_L1(uint8_t value) {
	if (ParamAPP_CH1_Active) KoAPP_CH1_StatusBrightness.value(value, DPT_Percent_U8);
}

void responseBrightnessCallback_L2(uint8_t value) {
	if (ParamAPP_CH2_Active) KoAPP_CH2_StatusBrightness.value(value, DPT_Percent_U8);
}

void responseBrightnessCallback_L3(uint8_t value) {
	if (ParamAPP_CH3_Active) KoAPP_CH3_StatusBrightness.value(value, DPT_Percent_U8);
}

void responseBrightnessCallback_L4(uint8_t value) {
	if (ParamAPP_CH4_Active) KoAPP_CH4_StatusBrightness.value(value, DPT_Percent_U8);
}

void responseBrightnessCallback_L5(uint8_t value) {
	if (ParamAPP_CH5_Active) KoAPP_CH5_StatusBrightness.value(value, DPT_Percent_U8);
}

void responseTemperatureCallback_L1(uint16_t value) {
	if (ParamAPP_CH1_Active) KoAPP_CH1_StatusColortemp.value(value, DPT_Percent_U8);
}

void responseTemperatureCallback_L2(uint16_t value) {
	if (ParamAPP_CH2_Active) KoAPP_CH2_StatusColortemp.value(value, DPT_Percent_U8);
}

void responseColorHsvCallback_L1(hsv_t value) {
	if (ParamAPP_CH1_Active) {
		KoAPP_CH1_StatusHSV.value(value.toDPT232600(), DPT_Colour_RGB);
		KoAPP_CH1_StatusHue.value(value.h, DPT_Percent_U8);
		KoAPP_CH1_StatusSaturation.value(value.s, DPT_Percent_U8);
	}
}

void responseColorRgbCallback_L1(rgb_t value) {
	if (ParamAPP_CH1_Active) KoAPP_CH1_StatusRGB.value(value.toDPT232600(), DPT_Colour_RGB);
}

void sendHeartbeat() {
	KoAPP_Heartbeat.value(true, DPT_State);
}

static inline void sep() {
	#ifdef DEBUGGING
  Serial.println("--------------------------------------------------");
	#endif
}

static inline void printActive(uint8_t ch, const char* type, uint32_t active) {
	#ifdef DEBUGGING
  Serial.print("Channel "); Serial.print(ch);
  Serial.print(" ("); Serial.print(type); Serial.print(") active: ");
  Serial.println(active);
	#endif
}

// -------- Parameter-Getter pro Kanal (1..5) --------
static inline uint32_t chActive(uint8_t ch) {
  switch (ch) {
    case 1: return ParamAPP_CH1_Active;
    case 2: return ParamAPP_CH2_Active;
    case 3: return ParamAPP_CH3_Active;
    case 4: return ParamAPP_CH4_Active;
    case 5: return ParamAPP_CH5_Active;
    default: return 0;
  }
}

static inline uint8_t chDimSpeed(uint8_t ch) {
  switch (ch) {
    case 1: return (uint8_t)ParamAPP_CH1_DimSpeed;
    case 2: return (uint8_t)ParamAPP_CH2_DimSpeed;
    case 3: return (uint8_t)ParamAPP_CH3_DimSpeed;
    case 4: return (uint8_t)ParamAPP_CH4_DimSpeed;
    case 5: return (uint8_t)ParamAPP_CH5_DimSpeed;
    default: return 0;
  }
}

static inline uint8_t chBrightnessDay(uint8_t ch) {
  switch (ch) {
    case 1: return (uint8_t)ParamAPP_CH1_BrightnessDay;
    case 2: return (uint8_t)ParamAPP_CH2_BrightnessDay;
    case 3: return (uint8_t)ParamAPP_CH3_BrightnessDay;
    case 4: return (uint8_t)ParamAPP_CH4_BrightnessDay;
    case 5: return (uint8_t)ParamAPP_CH5_BrightnessDay;
    default: return 0;
  }
}

static inline uint16_t chMinCT(uint8_t ch) {
  switch (ch) {
    case 1: return (uint16_t)ParamAPP_CH1_MinColorTemp;
    case 2: return (uint16_t)ParamAPP_CH2_MinColorTemp;
    default: return 0;
  }
}

static inline uint16_t chMaxCT(uint8_t ch) {
  switch (ch) {
    case 1: return (uint16_t)ParamAPP_CH1_MaxColorTemp;
    case 2: return (uint16_t)ParamAPP_CH2_MaxColorTemp;
    default: return 0;
  }
}

static inline uint16_t chDefCT(uint8_t ch) {
  switch (ch) {
    case 1: return (uint16_t)ParamAPP_CH1_DefaultColorTemp;
    case 2: return (uint16_t)ParamAPP_CH2_DefaultColorTemp;
    default: return 0;
  }
}

// Wichtig: DefaultColor ist 24 Bit / 3 Byte => paramData liefert Pointer.
static inline uint32_t chDefColorRaw(uint8_t ch) {
  switch (ch) {
    case 1: return (uint32_t)knx.paramInt(APP_CH1_DefaultColor);
    default: return 0;
  }
}

static inline hsv_t chDefHsv(uint8_t ch) {
  hsv_t hsv;
  hsv.fromDPT232600(chDefColorRaw(ch));
  return hsv;
}

// light setup functions
static inline void applyFadeSpeed(KnxLed& L, uint8_t ch) {
	uint8_t up = 0, down = 0, color = 0;
	switch (ch) {
		case 1: up = ParamAPP_CH1_FadeUpSpeed; down = ParamAPP_CH1_FadeDownSpeed; color = ParamAPP_CH1_FadeColorSpeed; break;
		case 2: up = ParamAPP_CH2_FadeUpSpeed; down = ParamAPP_CH2_FadeDownSpeed; color = ParamAPP_CH2_FadeColorSpeed; break;
		// kein Colorfade fuer DIM lights, setze ColorFade auf UpFade
		case 3: up = ParamAPP_CH3_FadeUpSpeed; down = ParamAPP_CH3_FadeDownSpeed; color = up; break;
		case 4: up = ParamAPP_CH4_FadeUpSpeed; down = ParamAPP_CH4_FadeDownSpeed; color = up; break;
		case 5: up = ParamAPP_CH5_FadeUpSpeed; down = ParamAPP_CH5_FadeDownSpeed; color = up; break;
		default: return;
	}
	L.configFadeSpeed(up, down, color);
}

static void setupRgbcct(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t cwPin, uint8_t wwPin) {
  printActive(ch, "RGBCCT", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
  L.configDefaultTemperature(chDefCT(ch));
  L.configDefaultBrightness(chBrightnessDay(ch));
  hsv_t hsv = chDefHsv(ch);
  L.configDefaultHsv(hsv);
  L.initRgbcctLight(rPin, gPin, bPin, cwPin, wwPin, CCT_MODE);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
	Serial.print("Def HSV raw: "); Serial.println((uint32_t)hsv.toDPT232600());
	#endif
}

static void setupRgbw(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t wPin) {
  printActive(ch, "RGBW", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
  L.configDefaultTemperature(chDefCT(ch));
  L.configDefaultBrightness(chBrightnessDay(ch));
  hsv_t hsv = chDefHsv(ch);
  L.configDefaultHsv(hsv);
  L.initRgbwLight(rPin, gPin, bPin, wPin, WHITE_LED_RGB_EQUIVALENT);
	#ifdef DEBUGGING
	Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
	Serial.print("Def HSV raw: "); Serial.println((uint32_t)hsv.toDPT232600());
	#endif
}

static void setupRgb(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin) {
  printActive(ch, "RGB", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
  L.configDefaultBrightness(chBrightnessDay(ch));
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
	L.configDefaultTemperature(ch);
  hsv_t hsv = chDefHsv(ch);
  L.configDefaultHsv(hsv);
  L.initRgbLight(rPin, gPin, bPin);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
	Serial.print("Def HSV raw: "); Serial.println((uint32_t)hsv.toDPT232600());
	#endif
}

static void setupCct(KnxLed& L, uint8_t ch, uint8_t cwPin, uint8_t wwPin) {
  printActive(ch, "CCT", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
  L.configDefaultTemperature(chDefCT(ch));
  L.configDefaultBrightness(chBrightnessDay(ch));
  L.initTunableWhiteLight(cwPin, wwPin, CCT_MODE);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
	#endif
}

static void setupDim(KnxLed& L, uint8_t ch, uint8_t pwmPin) {
  printActive(ch, "DIM", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
	L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
  L.configDefaultBrightness(chBrightnessDay(ch));
  L.initDimmableLight(pwmPin);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
	#endif
}

static void setupLightsFromEts() {
  #ifdef DEBUGGING
	sep();
	#endif

  // GPIOs (Param... sind uint32_t-Makros, KnxLed erwartet uint8_t)
  const uint8_t P1 = (uint8_t)ParamAPP_GPIO_PWM1;
  const uint8_t P2 = (uint8_t)ParamAPP_GPIO_PWM2;
  const uint8_t P3 = (uint8_t)ParamAPP_GPIO_PWM3;
  const uint8_t P4 = (uint8_t)ParamAPP_GPIO_PWM4;
  const uint8_t P5 = (uint8_t)ParamAPP_GPIO_PWM5;

  switch (ParamAPP_ChannelMode) {

    case PT_ChannelModes_RGBCCT: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: RGBCCT, 1 light");
			sep();
			#endif
      setupRgbcct(Light1, 1, P1, P2, P3, P4, P5);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
        Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
        Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
        Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif
      break;
    }

    case PT_ChannelModes_RGBW_D: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: RGBW_D, 2 lights");
			sep();
			#endif
      setupRgbw(Light1, 1, P1, P2, P3, P4);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
        Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
        Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
        Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light2, 2, P5);
      if (chActive(2) == PT_OnOff_Ein) {
        Light2.registerStatusCallback(statusCallback_L2);
        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
      }
			#ifdef DEBUGGING
			sep();
			#endif
      break;
    }

    case PT_ChannelModes_RGB_CCT: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: RGB_CCT, 2 lights");
			sep();
			#endif
      setupRgb(Light1, 1, P1, P2, P3);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
        Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
        Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupCct(Light2, 2, P4, P5);
      if (chActive(2) == PT_OnOff_Ein) {
        Light2.registerStatusCallback(statusCallback_L2);
        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
        Light2.registerTemperatureCallback(responseTemperatureCallback_L2);
      }
			#ifdef DEBUGGING
			sep();
			#endif
      break;
    }

    case PT_ChannelModes_RGB_D_D: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: RGB_D_D, 3 lights");
			sep();
			#endif
      setupRgb(Light1, 1, P1, P2, P3);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
        Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
        Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light2, 2, P4);
      if (chActive(2) == PT_OnOff_Ein) {
        Light2.registerStatusCallback(statusCallback_L2);
        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light3, 3, P5);
      if (chActive(3) == PT_OnOff_Ein) {
        Light3.registerStatusCallback(statusCallback_L3);
        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
      }
			#ifdef DEBUGGING
			sep();
			#endif

			break;
    }

    case PT_ChannelModes_CCT_CCT_D: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: CCT_CCT_D, 3 lights");
			sep();
			#endif
      setupCct(Light1, 1, P1, P2);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
        Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupCct(Light2, 2, P3, P4);
      if (chActive(2) == PT_OnOff_Ein) {
        Light2.registerStatusCallback(statusCallback_L2);
        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
        Light2.registerTemperatureCallback(responseTemperatureCallback_L2);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light3, 3, P5);
      if (chActive(3) == PT_OnOff_Ein) {
        Light3.registerStatusCallback(statusCallback_L3);
        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
      }
			#ifdef DEBUGGING
			sep();
			#endif

			break;
    }

    case PT_ChannelModes_CCT_D_D_D: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: CCT_D_D_D, 4 lights");
			sep();
			#endif
      setupCct(Light1, 1, P1, P2);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
        Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light2, 2, P3);
      if (chActive(2) == PT_OnOff_Ein) {
        Light2.registerStatusCallback(statusCallback_L2);
        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light3, 3, P4);
      if (chActive(3) == PT_OnOff_Ein) {
        Light3.registerStatusCallback(statusCallback_L3);
        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light4, 4, P5);
      if (chActive(4) == PT_OnOff_Ein) {
        Light4.registerStatusCallback(statusCallback_L4);
        Light4.registerBrightnessCallback(responseBrightnessCallback_L4);
      }
			#ifdef DEBUGGING
			sep();
			#endif

			break;
    }

    case PT_ChannelModes_D_D_D_D_D: {
			#ifdef DEBUGGING
      Serial.println("Channel setup: D_D_D_D_D, 5 lights");
			sep();
			#endif
      setupDim(Light1, 1, P1);
      if (chActive(1) == PT_OnOff_Ein) {
        Light1.registerStatusCallback(statusCallback_L1);
        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light2, 2, P2);
      if (chActive(2) == PT_OnOff_Ein) {
        Light2.registerStatusCallback(statusCallback_L2);
        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light3, 3, P3);
      if (chActive(3) == PT_OnOff_Ein) {
        Light3.registerStatusCallback(statusCallback_L3);
        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light4, 4, P4);
      if (chActive(4) == PT_OnOff_Ein) {
        Light4.registerStatusCallback(statusCallback_L4);
        Light4.registerBrightnessCallback(responseBrightnessCallback_L4);
      }
			#ifdef DEBUGGING
			sep();
			#endif

      setupDim(Light5, 5, P5);
      if (chActive(5) == PT_OnOff_Ein) {
        Light5.registerStatusCallback(statusCallback_L5);
        Light5.registerBrightnessCallback(responseBrightnessCallback_L5);
      }
			#ifdef DEBUGGING
			sep();
			#endif

			break;
    }

    default:
			#ifdef DEBUGGING
      Serial.println("Unknown ChannelMode. No lights initialized.");
			sep();
			#endif
      break;
  }
}

// WiFi helper
static inline bool connectWifi(const char* hostname, const char* ssid, const char* pass, uint32_t portalTimeoutSec = 180) {
	WiFi.persistent(true);
	WiFi.mode(WIFI_STA);
	WiFi.hostname(hostname);

	#if USE_WIFIMANAGER
	//WiFiManager wm;
	wm.setConfigPortalTimeout(portalTimeoutSec); // Sekunden
	// wm.setHostname(hostname); // nur aktivieren, wenn dein Build das unterstützt
	bool ok = wm.autoConnect(hostname, WM_PASS);
	// if (!ok) ESP.restart();
	return ok;
	#else
	#if defined(ESP8266) || defined(ESP32)
	WiFi.disconnect(true);
	#endif
	//WiFi.setAutoConnect(true);
	//WiFi.setAutoReconnect(true);
	WiFi.begin(ssid, pass);
	const uint32_t start = millis();
	const uint32_t timeoutMs = 20000;
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		// if ((uint32_t)(millis() - start) >= timeoutMs) ESP.restart();
		// Implement AP mode here after timeout if needed
		// however an open AP can be a security issue
		// settingsAP();
	}
	return true;
	#endif
}

// GPIO helper
static inline bool gpioLowForMs(uint8_t pin, uint32_t holdMs) {
	static uint32_t lowStartMs = 0;
	static bool triggered = false;
	if (digitalRead(pin) == LOW) {
		if (lowStartMs == 0) lowStartMs = millis();
		if (!triggered && (uint32_t)(millis() - lowStartMs) >= holdMs) {
			triggered = true;
			return true;   // ✅ Aktion auslösen
		}
	} else {
		// Reset sobald Pin wieder HIGH
		lowStartMs = 0;
		triggered = false;
	}
	return false;
}

// Erase Flash helper
void factoryReset() {
	#if USE_WIFIMANAGER
	wm.resetSettings();
	#endif
	#if defined(ESP32)
	nvs_flash_erase();
	nvs_flash_init();
	ESP.restart();
	#elif defined(ESP8266)
	ESP.eraseFlash();
	ESP.restart();
	#endif
}

// Heartbeat helper
static inline void handleHeartbeat() {
	uint32_t intervalSec = ParamAPP_Heartbeat;
	if (intervalSec == 0) return;   // Heartbeat deaktiviert
	uint32_t intervalMs = intervalSec * 1000UL;
	uint32_t now = millis();
	if ( ((uint32_t)(now - heartbeatLastMs) >= intervalMs) || (heartbeatLastMs == 0) ) {
		heartbeatLastMs = now;
		sendHeartbeat();
	}
}

void setup() {
	setCpuFrequencyMhz(CPU_FREQ);
	startMs = millis();
	#ifdef ESP8266
	Serial.begin(74880);
	#else
	Serial.begin(115200);
	#endif
	#ifdef ERASE_BTN
	pinMode(ERASE_BTN, INPUT_PULLUP); // LOW = pressed
	#endif
	#if PRODUCT == YLDL01YL
	pinMode(22, OUTPUT);
	digitalWrite(22,HIGH);	// should be changed later, so that power gets only applied if a light is active
	#endif
	
	// set correct hardware type for flash compatibility check
	setFirmwareVersion(MAIN_OpenKnxId, MAIN_ApplicationNumber, MAIN_ApplicationVersion);

	// Red status led on at start
	#ifdef STAT_LED_GN
	pinMode(STAT_LED_GN, OUTPUT);
	digitalWrite(STAT_LED_GN, STAT_LED_OFF);
	#endif
	#ifdef STAT_LED_RD
	pinMode(STAT_LED_RD, OUTPUT);
	digitalWrite(STAT_LED_RD, STAT_LED_ON);
	#endif

	// read adress table, association table, groupobject table and parameters from eeprom
	knx.readMemory();

	knxConfigOk = knx.configured() && checkKnxApp() && knx.bau().groupObjectTable().entryCount() == MAIN_MaxKoNumber; //MAIN_ParameterSize

	// Setup device after device was configured by ETS
	if (knxConfigOk) {
		GroupObject::classCallback(knxCallback); // callbacks are now handled per class, not per instance
		// read hostname from ETS config
		HOSTNAME = (char *)knx.paramData(APP_Hostname);
		// read channel setup and individual parameters from ETS config
		setupLightsFromEts();

		startUpDelay = ParamAPP_StartUpDelay * 1000;

	}
	Serial.println(HOSTNAME);
	Serial.println(getKnxPhysAddr());
	#ifdef DEBUGGING
	Serial.print("StartUp Delay: "); Serial.print(startUpDelay); Serial.println("ms");
	#endif

	// Red status led off and green led on after setup
	#ifdef STAT_LED_GN
	digitalWrite(STAT_LED_GN, STAT_LED_ON);
	#endif
	#ifdef STAT_LED_RD
	digitalWrite(STAT_LED_RD, STAT_LED_OFF);
	#endif

	connectWifi(HOSTNAME, WIFI_SSID, WIFI_PASS, 300);

	// Setup and start KNX stack
	setKnxHostname(HOSTNAME);
	knx.start();

	// Setup and start webserver and OTA
	knxWebServ.setHostname(HOSTNAME);
	knxWebServ.setBuildDetails("Compiled: " __DATE__ ", " __TIME__ );
	knxWebServ.setKnxDetail(getKnxPhysAddr(), getKnxAppDetails(), knxConfigOk);
	knxWebServ.registerGetKnxModeCallback(getKnxMode);
	knxWebServ.registerSetKnxModeCallback(setKnxMode);
	knxWebServ.registerRestartDeviceCallback(restartDeviceCallback);
	knxWebServ.startOta();
	knxWebServ.startWeb(WWW_USER, WWW_PASS);

	// Both status LEDs off after WIFI connect
	#ifdef STAT_LED_GN
	digitalWrite(STAT_LED_GN, STAT_LED_OFF);
	#endif
	#ifdef STAT_LED_RD
	digitalWrite(STAT_LED_RD, STAT_LED_OFF);
	#endif
}

void loop() {
	uint32_t currentMillis = millis();

	#ifdef ERASE_BTN
	if (gpioLowForMs(ERASE_BTN, 5000)) factoryReset();
	#endif

	if (WiFi.status() == WL_CONNECTED) {
		knxWebServ.loop();
			if(getKnxActive()) {
				knx.loop();
		}
		// only run the application code if the device was configured with ETS
		if (!knxConfigOk) return;

		// startup delay
		if ( (currentMillis - startMs) < startUpDelay) return;

		handleHeartbeat();

		if (!initSent) {
			if (ParamAPP_CH1_Active) Light1.sendStatusUpdate();
			if (ParamAPP_CH2_Active) Light2.sendStatusUpdate();
			if (ParamAPP_CH3_Active) Light3.sendStatusUpdate();
			if (ParamAPP_CH4_Active) Light4.sendStatusUpdate();
			if (ParamAPP_CH5_Active) Light5.sendStatusUpdate();
			initSent = true;
		}

		if (ParamAPP_CH1_Active) Light1.loop();
		if (ParamAPP_CH2_Active) Light2.loop();
		if (ParamAPP_CH3_Active) Light3.loop();
		if (ParamAPP_CH4_Active) Light4.loop();
		if (ParamAPP_CH5_Active) Light5.loop();

	} else {
		static unsigned int reconnectCounter = 0;
		if(reconnectCounter > 1000) {
			WiFi.reconnect();
			reconnectCounter=0;
		}
		reconnectCounter++;
	}

	keepCycleTime(MIN_CYCLE_TIME);
}