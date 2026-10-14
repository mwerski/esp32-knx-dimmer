#include "main.h"

KnxLed Light1 = KnxLed();
KnxLed Light2 = KnxLed();
KnxLed Light3 = KnxLed();
KnxLed Light4 = KnxLed();
KnxLed Light5 = KnxLed();

bool knxConfigOk = false;
static volatile bool wifiPortalRequested = false;	// set by web UI or KNX, handled in loop()
static bool wifiPortalActive = false;
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
		case APP_KoGeneralWifiPortal: { if (go.value(DPT_Start)) wifiPortalRequested = true; break; }

		case APP_KoGeneralDayNight: {
			bool itsDay;
			(ParamAPP_DayNight) ? (itsDay = go.value(DPT_Switch)) : (itsDay = !go.value(DPT_Switch));
			uint8_t defaultBrightness;
			if (ParamAPP_CH1_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH1_BrightnessDay : ParamAPP_CH1_BrightnessNight;
				Light1.configDefaultBrightness(defaultBrightness);
			}
			if (ParamAPP_CH2_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH2_BrightnessDay : ParamAPP_CH2_BrightnessNight;
				Light2.configDefaultBrightness(defaultBrightness);
				#ifdef PRODUCT_YLDL01YL
				Light3.configDefaultBrightness(defaultBrightness);	// NightLight follows DownLight
				#endif
			}
			#ifndef PRODUCT_YLDL01YL
			if (ParamAPP_CH3_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH3_BrightnessDay : ParamAPP_CH3_BrightnessNight;
				Light3.configDefaultBrightness(defaultBrightness);
			}
			#endif
			if (ParamAPP_CH4_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH4_BrightnessDay : ParamAPP_CH4_BrightnessNight;
				Light4.configDefaultBrightness(defaultBrightness);
			}
			if (ParamAPP_CH5_Active) {
				defaultBrightness = itsDay ? ParamAPP_CH5_BrightnessDay : ParamAPP_CH5_BrightnessNight;
				Light5.configDefaultBrightness(defaultBrightness);
			}
			break;
		}

		case APP_KoCH1_Schalten: { Light1.switchLight(go.value(DPT_Switch)); break; }
		#ifdef PRODUCT_YLDL01YL
		// NightLight (Light3) follows the DownLight (CH2), CH3 objects are ignored
		case APP_KoCH2_Schalten: { Light2.switchLight(go.value(DPT_Switch)); Light3.switchLight(go.value(DPT_Switch)); break; }
		#else
		case APP_KoCH2_Schalten: { Light2.switchLight(go.value(DPT_Switch)); break; }
		case APP_KoCH3_Schalten: { Light3.switchLight(go.value(DPT_Switch)); break; }
		#endif
		case APP_KoCH4_Schalten: { Light4.switchLight(go.value(DPT_Switch)); break; }
		case APP_KoCH5_Schalten: { Light5.switchLight(go.value(DPT_Switch)); break; }

		case APP_KoCH1_BrightnessAbsolute: { Light1.setBrightness(go.value(DPT_Percent_U8)); break; }
		#ifdef PRODUCT_YLDL01YL
		case APP_KoCH2_BrightnessAbsolute: { Light2.setBrightness(go.value(DPT_Percent_U8)); Light3.setBrightness(go.value(DPT_Percent_U8)); break; }
		#else
		case APP_KoCH2_BrightnessAbsolute: { Light2.setBrightness(go.value(DPT_Percent_U8)); break; }
		case APP_KoCH3_BrightnessAbsolute: { Light3.setBrightness(go.value(DPT_Percent_U8)); break; }
		#endif
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
			#ifdef PRODUCT_YLDL01YL
			Light3.setRelDimCmd(dimCmd);
			#endif
			break;
		}
		#ifndef PRODUCT_YLDL01YL
		case APP_KoCH3_BrightnessRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light3.setRelDimCmd(dimCmd);
			break;
		}
		#endif
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
			break;
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
	if (ParamAPP_CH1_Active) KoAPP_CH1_StatusColortemp.value(value, DPT_Value_2_Ucount);
}

void responseTemperatureCallback_L2(uint16_t value) {
	if (ParamAPP_CH2_Active) KoAPP_CH2_StatusColortemp.value(value, DPT_Value_2_Ucount);
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

static inline uint8_t chBrightnessMin(uint8_t ch) {
  switch (ch) {
    case 1: return (uint8_t)ParamAPP_CH1_BrightnessMin;
    case 2: return (uint8_t)ParamAPP_CH2_BrightnessMin;
    case 3: return (uint8_t)ParamAPP_CH3_BrightnessMin;
    case 4: return (uint8_t)ParamAPP_CH4_BrightnessMin;
    case 5: return (uint8_t)ParamAPP_CH5_BrightnessMin;
    default: return 0;
  }
}

static inline uint8_t chBrightnessMax(uint8_t ch) {
  switch (ch) {
    case 1: return (uint8_t)ParamAPP_CH1_BrightnessMax;
    case 2: return (uint8_t)ParamAPP_CH2_BrightnessMax;
    case 3: return (uint8_t)ParamAPP_CH3_BrightnessMax;
    case 4: return (uint8_t)ParamAPP_CH4_BrightnessMax;
    case 5: return (uint8_t)ParamAPP_CH5_BrightnessMax;
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

// colour temperature follows brightness (only available for the DownLight)
static inline bool chDim2Warm(uint8_t ch) {
  switch (ch) {
    case 2: return ParamAPP_CH2_Dim2Warm;
    default: return false;
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
	#ifdef DEBUGGING
  Serial.print("FadeUp Speed: "); Serial.println(up);
  Serial.print("FadeDown Speed: "); Serial.println(down);
  Serial.print("FadeColor Speed: "); Serial.println(color);
	#endif
	L.configFadeSpeed(up, down, color);
}

static inline DimCurveType chDimCurve(uint8_t ch) {
	switch (ch) {
		case 1: return DIM_CURVE_CH1;
		case 2: return DIM_CURVE_CH2;
		case 3: return DIM_CURVE_CH3;
		case 4: return DIM_CURVE_CH4;
		case 5: return DIM_CURVE_CH5;
		default: return DIMCURVE_DEFAULT;
	}
}

static inline void applyDimCurve(KnxLed& L, uint8_t ch) {
	#ifdef PRODUCT_YLDL01YL
	// fixed curves: RGB UpLight (CH1) keeps default, DownLight (CH2) and NightLight (CH3) share the dimming range
	switch (ch) {
		case 2: L.configDimCurve(yldl01ylDownLightCurve, DimCurve::TABLE_SIZE); break;
		case 3: L.configDimCurve(yldl01ylNightLightCurve, DimCurve::TABLE_SIZE); break;
	}
	#ifdef DEBUGGING
	Serial.print("Dim Curve: "); Serial.println(ch == 2 ? "YLDL01YL DownLight" : ch == 3 ? "YLDL01YL NightLight" : "default");
	#endif
	#else
	DimCurveType type = chDimCurve(ch);
	#ifdef DEBUGGING
	Serial.print("Dim Curve: "); Serial.println(type);
	#endif
	if (type == DIMCURVE_DEFAULT) return;
	uint16_t curve[DimCurve::TABLE_SIZE];
	switch (type) {
		case DIMCURVE_LINEAR: DimCurve::linear(curve); break;
		case DIMCURVE_GAMMA: DimCurve::gamma(curve, DIM_CURVE_GAMMA); break;
		case DIMCURVE_EXPONENTIAL: DimCurve::exponential(curve, DIM_CURVE_EXP_K); break;
		case DIMCURVE_DALI: DimCurve::daliLog(curve); break;
		case DIMCURVE_LED_LOW_END_BOOST: DimCurve::ledLowEndBoost(curve, DIM_CURVE_GAMMA, DIM_CURVE_PWM_MIN); break;
		case DIMCURVE_LED_HYBRID: DimCurve::ledHybrid(curve, DIM_CURVE_HYBRID_T, DIM_CURVE_HYBRID_GAMMA_LOW, DIM_CURVE_HYBRID_GAMMA_HIGH); break;
		case DIMCURVE_LED_S_CURVE: DimCurve::ledSCurve(curve, DIM_CURVE_GAMMA); break;
		default: return;
	}
	// invalid curve -> esp-knx-led keeps its default lookupTable
	if (DimCurve::validate(curve)) {
		L.configDimCurve(curve, DimCurve::TABLE_SIZE);
	}
	#ifdef DEBUGGING
	else {
		Serial.println("Dim Curve invalid, using default");
	}
	#endif
	#endif
}

static void setupRgbcct(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t cwPin, uint8_t wwPin) {
  printActive(ch, "RGBCCT", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
	applyDimCurve(L, ch);
	L.configPwmFrequency(ParamAPP_PWMFrequency);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
  L.configDefaultTemperature(chDefCT(ch));
  hsv_t hsv = chDefHsv(ch);
  L.configDefaultHsv(hsv);
	L.configMinBrightness(chBrightnessMin(ch));
	L.configMaxBrightness(chBrightnessMax(ch));
	L.configDefaultBrightness(chBrightnessDay(ch));	// after configMaxBrightness(), which overwrites the default
  L.initRgbcctLight(rPin, gPin, bPin, cwPin, wwPin, CCT_MODE);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
  Serial.print("Min Brightness: "); Serial.println(chBrightnessMin(ch));
  Serial.print("Max Brightness: "); Serial.println(chBrightnessMax(ch));
  Serial.print("PWM Frequency: "); Serial.println(ParamAPP_PWMFrequency);
	Serial.print("Def HSV raw: "); Serial.println((uint32_t)hsv.toDPT232600());
	#endif
}

static void setupRgbw(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin, uint8_t wPin) {
  printActive(ch, "RGBW", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
	applyDimCurve(L, ch);
	L.configPwmFrequency(ParamAPP_PWMFrequency);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
  L.configDefaultTemperature(chDefCT(ch));
  hsv_t hsv = chDefHsv(ch);
  L.configDefaultHsv(hsv);
	L.configMinBrightness(chBrightnessMin(ch));
	L.configMaxBrightness(chBrightnessMax(ch));
	L.configDefaultBrightness(chBrightnessDay(ch));	// after configMaxBrightness(), which overwrites the default
  L.initRgbwLight(rPin, gPin, bPin, wPin, WHITE_LED_RGB_EQUIVALENT);
	#ifdef DEBUGGING
	Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
  Serial.print("Min Brightness: "); Serial.println(chBrightnessMin(ch));
  Serial.print("Max Brightness: "); Serial.println(chBrightnessMax(ch));
  Serial.print("PWM Frequency: "); Serial.println(ParamAPP_PWMFrequency);
	Serial.print("Def HSV raw: "); Serial.println((uint32_t)hsv.toDPT232600());
	#endif
}

static void setupRgb(KnxLed& L, uint8_t ch, uint8_t rPin, uint8_t gPin, uint8_t bPin) {
  printActive(ch, "RGB", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
	applyDimCurve(L, ch);
	L.configPwmFrequency(ParamAPP_PWMFrequency);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
	L.configDefaultTemperature(chDefCT(ch));
  hsv_t hsv = chDefHsv(ch);
  L.configDefaultHsv(hsv);
	L.configMinBrightness(chBrightnessMin(ch));
	L.configMaxBrightness(chBrightnessMax(ch));
	L.configDefaultBrightness(chBrightnessDay(ch));	// after configMaxBrightness(), which overwrites the default
  L.initRgbLight(rPin, gPin, bPin);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
  Serial.print("Min Brightness: "); Serial.println(chBrightnessMin(ch));
  Serial.print("Max Brightness: "); Serial.println(chBrightnessMax(ch));
  Serial.print("PWM Frequency: "); Serial.println(ParamAPP_PWMFrequency);
	Serial.print("Def HSV raw: "); Serial.println((uint32_t)hsv.toDPT232600());
	#endif
}

static void setupCct(KnxLed& L, uint8_t ch, uint8_t cwPin, uint8_t wwPin) {
  printActive(ch, "CCT", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
  L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
	applyDimCurve(L, ch);
	L.configPwmFrequency(ParamAPP_PWMFrequency);
  L.configMinTemperature(chMinCT(ch));
  L.configMaxTemperature(chMaxCT(ch));
  L.configDefaultTemperature(chDefCT(ch));
	L.configMinBrightness(chBrightnessMin(ch));
	L.configMaxBrightness(chBrightnessMax(ch));
	L.configDefaultBrightness(chBrightnessDay(ch));	// after configMaxBrightness(), which overwrites the default
	L.configDim2Warm(chDim2Warm(ch));
  L.initTunableWhiteLight(cwPin, wwPin, CCT_MODE);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Min CT: "); Serial.println(chMinCT(ch));
  Serial.print("Max CT: "); Serial.println(chMaxCT(ch));
  Serial.print("Def CT: "); Serial.println(chDefCT(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
  Serial.print("Min Brightness: "); Serial.println(chBrightnessMin(ch));
  Serial.print("Max Brightness: "); Serial.println(chBrightnessMax(ch));
  Serial.print("PWM Frequency: "); Serial.println(ParamAPP_PWMFrequency);
  Serial.print("Dim to warm: "); Serial.println(chDim2Warm(ch));
	#endif
}

static void setupDim(KnxLed& L, uint8_t ch, uint8_t pwmPin) {
  printActive(ch, "DIM", chActive(ch));
  if (chActive(ch) != PT_OnOff_Ein) return;
	L.configDimSpeed(chDimSpeed(ch));
	applyFadeSpeed(L, ch);
	applyDimCurve(L, ch);
	L.configPwmFrequency(ParamAPP_PWMFrequency);
	L.configMinBrightness(chBrightnessMin(ch));
	L.configMaxBrightness(chBrightnessMax(ch));
	L.configDefaultBrightness(chBrightnessDay(ch));	// after configMaxBrightness(), which overwrites the default
  L.initDimmableLight(pwmPin);
	#ifdef DEBUGGING
  Serial.print("Dim Speed: "); Serial.println(chDimSpeed(ch));
  Serial.print("Def Brightness: "); Serial.println(chBrightnessDay(ch));
  Serial.print("Min Brightness: "); Serial.println(chBrightnessMin(ch));
  Serial.print("Max Brightness: "); Serial.println(chBrightnessMax(ch));
  Serial.print("PWM Frequency: "); Serial.println(ParamAPP_PWMFrequency);
	#endif
}

#ifdef PRODUCT_YLDL01YL
// NightLight follows the DownLight (CH2): same parameters, so both lights dim in sync,
// but its own dimming curve (CH3), which covers the low end of the range
static void setupNightLight(KnxLed& L, uint8_t pwmPin) {
	printActive(3, "NightLight, follows CH2", chActive(2));
	if (chActive(2) != PT_OnOff_Ein) return;
	L.configDimSpeed(chDimSpeed(2));
	applyFadeSpeed(L, 2);
	applyDimCurve(L, 3);
	L.configPwmFrequency(ParamAPP_PWMFrequency);
	L.configMinBrightness(chBrightnessMin(2));
	L.configMaxBrightness(chBrightnessMax(2));
	L.configDefaultBrightness(chBrightnessDay(2));
	L.initDimmableLight(pwmPin);
}
#endif

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
        Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
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

	#if defined(ESP32)
	// default is WIFI_FAST_SCAN, which connects to the first AP found with matching SSID (lowest channel),
	// not the strongest one. Scan all channels and connect to the AP with the best signal instead.
	WiFi.setScanMethod(WIFI_ALL_CHANNEL_SCAN);
	WiFi.setSortMethod(WIFI_CONNECT_AP_BY_SIGNAL);
	// WiFiManager / WiFi.begin() without arguments reuse the stored config, so patch it as well
	wifi_config_t conf;
	if (esp_wifi_get_config(WIFI_IF_STA, &conf) == ESP_OK) {
		conf.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
		conf.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
		conf.sta.bssid_set = false;
		esp_wifi_set_config(WIFI_IF_STA, &conf);
	}
	#endif

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

// Light state persistence (restore after restart / power loss)
#if RESTORE_LIGHT_STATE && defined(ESP32)
#include <Preferences.h>

static KnxLed* const lights[] = { &Light1, &Light2, &Light3, &Light4, &Light5 };
static const uint8_t lightCount = sizeof(lights) / sizeof(lights[0]);
static knxLedState_t savedStates[lightCount];

static void readLightStates(knxLedState_t* states) {
	for (uint8_t i = 0; i < lightCount; i++) states[i] = lights[i]->getState();
}

static void restoreLightStates() {
	Preferences prefs;
	if (!prefs.begin("lightstate", true)) return;	// read only, namespace does not exist yet
	if (prefs.getBytesLength("states") == sizeof(savedStates)) {
		prefs.getBytes("states", savedStates, sizeof(savedStates));
		for (uint8_t i = 0; i < lightCount; i++) lights[i]->restoreState(savedStates[i]);
		#ifdef DEBUGGING
		Serial.println("Light states restored");
		#endif
	}
	prefs.end();
	// what is restored now is the reference for saving, avoids an unnecessary write after startup
	readLightStates(savedStates);
}

// save the light states, but only after they did not change for STATE_SAVE_DELAY_MS
static void handleLightStatePersistence() {
	static uint32_t lastCheckMs = 0;
	static uint32_t changedMs = 0;
	static knxLedState_t lastStates[lightCount];
	uint32_t now = millis();
	if ((uint32_t)(now - lastCheckMs) < 1000) return;
	lastCheckMs = now;

	knxLedState_t states[lightCount];
	readLightStates(states);
	if (memcmp(states, lastStates, sizeof(states)) != 0) {
		memcpy(lastStates, states, sizeof(states));
		changedMs = now;
		return;
	}
	if (memcmp(states, savedStates, sizeof(states)) == 0) return;
	if ((uint32_t)(now - changedMs) < STATE_SAVE_DELAY_MS) return;
	// states are only needed for "last state", avoid flash writes otherwise
	if (ParamAPP_PowerOnBehavior != PT_PowerOnBehavior_LastState) return;

	Preferences prefs;
	if (prefs.begin("lightstate", false)) {
		prefs.putBytes("states", states, sizeof(states));
		prefs.end();
		memcpy(savedStates, states, sizeof(states));
		#ifdef DEBUGGING
		Serial.println("Light states saved");
		#endif
	}
}
#endif

// switch on all active lights with their default (day) brightness
static void switchOnActiveLights() {
	if (ParamAPP_CH1_Active) Light1.switchLight(true);
	if (ParamAPP_CH2_Active) Light2.switchLight(true);
	#ifdef PRODUCT_YLDL01YL
	if (ParamAPP_CH2_Active) Light3.switchLight(true);	// NightLight follows DownLight
	#else
	if (ParamAPP_CH3_Active) Light3.switchLight(true);
	#endif
	if (ParamAPP_CH4_Active) Light4.switchLight(true);
	if (ParamAPP_CH5_Active) Light5.switchLight(true);
}

// behavior after power on / restart, ETS parameter
static void applyPowerOnBehavior() {
	#ifdef DEBUGGING
	Serial.print("Power on behavior: "); Serial.println(ParamAPP_PowerOnBehavior);
	#endif
	switch (ParamAPP_PowerOnBehavior) {
		case PT_PowerOnBehavior_LastState:
			#if RESTORE_LIGHT_STATE && defined(ESP32)
			restoreLightStates();
			#endif
			break;
		case PT_PowerOnBehavior_On:
			switchOnActiveLights();
			break;
		case PT_PowerOnBehavior_Off:
		default:
			break;	// lights stay off
	}
}

// WiFi setup portal
#if USE_WIFIMANAGER && defined(ESP32)
static String wifiOldSsid;
static String wifiOldPass;

// web UI callback, the portal is started in loop() (the web UI has to release port 80 first)
void requestWifiPortal() {
	wifiPortalRequested = true;
}

// stored station credentials, also available if not connected
static void readStoredWifi(String& ssid, String& pass) {
	wifi_config_t conf;
	if (esp_wifi_get_config(WIFI_IF_STA, &conf) != ESP_OK) return;
	char buf[65];
	memcpy(buf, conf.sta.ssid, 32); buf[32] = 0;
	ssid = buf;
	memcpy(buf, conf.sta.password, 64); buf[64] = 0;
	pass = buf;
}

static void startWifiPortal() {
	readStoredWifi(wifiOldSsid, wifiOldPass);	// to restore them if the new credentials do not work
	knxWebServ.stopWeb();	// portal uses port 80
	wm.setConfigPortalBlocking(false);
	wm.setConfigPortalTimeout(WIFI_PORTAL_TIMEOUT_S);
	wm.startConfigPortal(HOSTNAME, WM_PASS);
	wifiPortalActive = true;
	#ifdef DEBUGGING
	Serial.println("WiFi portal started");
	#endif
}

// start the portal on request or if WiFi is lost for a long time, restore old credentials if the new ones fail
static void handleWifiPortal() {
	static uint32_t wifiLostMs = 0;
	static uint32_t portalStartMs = 0;
	static uint32_t portalClosedMs = 0;
	static bool checkPending = false;
	uint32_t now = millis();

	if (!wifiPortalActive && !checkPending) {
		if (WiFi.status() == WL_CONNECTED) wifiLostMs = 0;
		else if (wifiLostMs == 0) wifiLostMs = now;
		bool lostTooLong = wifiLostMs != 0 && (uint32_t)(now - wifiLostMs) >= WIFI_PORTAL_AFTER_LOST_MS;
		if (wifiPortalRequested || lostTooLong) {
			wifiPortalRequested = false;
			wifiLostMs = 0;
			startWifiPortal();
			portalStartMs = now;
		}
		return;
	}
	wifiPortalRequested = false;

	if (wifiPortalActive) {
		wm.process();
		// own timeout as well, the WiFiManager timeout is not reliable in non blocking mode
		if (wm.getConfigPortalActive() && (uint32_t)(now - portalStartMs) >= WIFI_PORTAL_TIMEOUT_S * 1000UL) {
			wm.stopConfigPortal();
		}
		if (wm.getConfigPortalActive()) return;
		// portal closed: new credentials saved and connected, or timeout
		wifiPortalActive = false;
		checkPending = true;
		portalClosedMs = now;
		#ifdef DEBUGGING
		Serial.println("WiFi portal closed");
		#endif
	}

	// portal closed, wait for a connection
	if (WiFi.status() == WL_CONNECTED) {
		checkPending = false;
		if (WiFi.SSID() != wifiOldSsid) {
			// new network: restart, so KNX/IP and all services start cleanly with the new connection
			#ifdef DEBUGGING
			Serial.println("Connected to new WiFi, restarting");
			#endif
			delay(500);
			ESP.restart();
		}
		knxWebServ.resumeWeb();
	} else if ((uint32_t)(now - portalClosedMs) >= WIFI_PORTAL_CHECK_MS) {
		// no connection with the new credentials: restore the old ones
		checkPending = false;
		if (wifiOldSsid.length() > 0) {
			#ifdef DEBUGGING
			Serial.print("No WiFi connection, restoring credentials for "); Serial.println(wifiOldSsid);
			#endif
			WiFi.begin(wifiOldSsid.c_str(), wifiOldPass.c_str());
		}
		knxWebServ.resumeWeb();
	}
}
#endif

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
	#ifdef PRODUCT_YLDL01YL
	Serial.println("YLDL01YL mode, holding power GPIO high");
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
		// read hostname from ETS config
		HOSTNAME = (char *)knx.paramData(APP_Hostname);
		GroupObject::classCallback(knxCallback); // callbacks are now handled per class, not per instance
		// read channel setup and individual parameters from ETS config
		setupLightsFromEts();
		#ifdef PRODUCT_YLDL01YL
		// static configuration of NightLight (l3), only in RGB_CCT mode, other modes already use Light3
		// no status callbacks, the DownLight (CH2) reports the common brightness
		if (ParamAPP_ChannelMode == PT_ChannelModes_RGB_CCT) {
			setupNightLight(Light3, 23);	// GPIO23, NightLight PWM
		}
		#ifdef DEBUGGING
		else {
			Serial.println("NightLight not initialized, ChannelMode is not RGB_CCT");
		}
		sep();
		#endif
		#endif
		applyPowerOnBehavior();

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
	// disable WiFi modem sleep: while sleeping, multicast (KNX IP routing) is only received
	// at DTIM beacons or gets lost, which breaks ETS programming
	#if defined(ESP32)
	WiFi.setSleep(false);
	#elif defined(ESP8266)
	WiFi.setSleepMode(WIFI_NONE_SLEEP);
	#endif

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
	#if USE_WIFIMANAGER && defined(ESP32)
	knxWebServ.registerWifiPortalCallback(requestWifiPortal);
	#endif
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

	#if USE_WIFIMANAGER && defined(ESP32)
	handleWifiPortal();
	#endif

	if (WiFi.status() == WL_CONNECTED) {
		knxWebServ.loop();
		if(getKnxActive()) {
			// the IP data link layer reads only one UDP packet per call and the UDP receive buffer
			// is small, so process several packets per cycle to avoid lost telegrams (ETS download)
			for (uint8_t i = 0; i < KNX_LOOPS_PER_CYCLE; i++) knx.loop();
		}
		// only run the application code if the device was configured with ETS
		// and no ETS download is running (group object tables are rewritten, access would crash)
		if (!knxConfigOk || !knx.configured()) return;

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
		#ifdef PRODUCT_YLDL01YL
		if (ParamAPP_CH2_Active) Light3.loop();	// NightLight follows DownLight
		#else
		if (ParamAPP_CH3_Active) Light3.loop();
		#endif
		if (ParamAPP_CH4_Active) Light4.loop();
		if (ParamAPP_CH5_Active) Light5.loop();

		#if RESTORE_LIGHT_STATE && defined(ESP32)
		handleLightStatePersistence();
		#endif

	} else {
		static unsigned int reconnectCounter = 0;
		// no reconnect while the setup portal runs, it handles the station itself
		if(reconnectCounter > 1000 && !wifiPortalActive) {
			WiFi.reconnect();
			reconnectCounter=0;
		}
		reconnectCounter++;
	}

	keepCycleTime(MIN_CYCLE_TIME);
}