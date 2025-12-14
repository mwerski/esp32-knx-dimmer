#include "main.h"

KnxLed Light1 = KnxLed();
KnxLed Light2 = KnxLed();
KnxLed Light3 = KnxLed();
KnxLed Light4 = KnxLed();
KnxLed Light5 = KnxLed();

bool knxConfigOk = false;
bool initSent = false;
KnxWebserver knxWebServ = KnxWebserver();

// callback from knx value change
void knxCallback(GroupObject &go) {
	// callbacks are now handled in the class, not per instance,
	// this means, we have to check, which GroupObject is calling back
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

		case APP_KoCH1_ColortempAbsolute: { Light1.setTemperature(go.value(DPT_Percent_U8)); break; }
		case APP_KoCH2_ColortempAbsolute: { Light2.setTemperature(go.value(DPT_Percent_U8)); break; }

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
		}
	
		case APP_KoCH1_HueAbsolute: {
			hsv_t hsv = Light1.getHsv();
			hsv.h = go.value(DPT_Percent_U8);
			Light1.setHsv(hsv);
		}
		case APP_KoCH1_HueRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light1.setRelHueCmd(dimCmd);
		}
		case APP_KoCH1_SaturationAbsolute: {
			hsv_t hsv = Light1.getHsv();
			hsv.h = go.value(DPT_Percent_U8);
			Light1.setHsv(hsv);
		}
		case APP_KoCH1_SaturationRelative: {
			dpt3_t dimCmd;
			dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
			Light1.setRelSaturationCmd(dimCmd);
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

static inline void sep() {
	#ifdef DEBUG
  Serial.println("--------------------------------------------------");
	#endif
}

static inline void printActive(uint8_t ch, const char* type, uint32_t active) {
	#ifdef DEBUG
  Serial.print("Channel "); Serial.print(ch);
  Serial.print(" ("); Serial.print(type); Serial.print(") active: ");
  Serial.println(active);
	#endif
}




void setup() {
	#ifdef ESP8266
	Serial.begin(74880);
	#else
	Serial.begin(115200);
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
		Serial.print("HEARTBEAT: ");
		Serial.println(ParamAPP_Heartbeat);

		GroupObject::classCallback(knxCallback); // callbacks are now handled per class, not per instance

		// read hostname from ETS config
		HOSTNAME = (char *)knx.paramData(APP_Hostname);

		// read channel setup and individual parameters from ETS config
		if (ParamAPP_ChannelMode == PT_ChannelModes_RGBCCT) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: RGBCCT, 1 light");
			// RGBCCT
			Serial.print("Channel 1 (RGBCCT) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_DimSpeed);
				Light1.configDimSpeed(ParamAPP_CH1_DimSpeed);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH1_MinColorTemp);
				Light1.configMinTemperature(ParamAPP_CH1_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH1_MaxColorTemp);
				Light1.configMaxTemperature(ParamAPP_CH1_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH1_DefaultColorTemp);
				Light1.configDefaultTemperature(ParamAPP_CH1_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				hsv_t paraDefaultHSV;
				paraDefaultHSV.fromDPT232600(knx.paramInt(APP_CH1_DefaultColor));
				Light1.configDefaultHsv(paraDefaultHSV);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
				Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
				Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
				Light1.initRgbcctLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, ParamAPP_GPIO_PWM3, ParamAPP_GPIO_PWM4, ParamAPP_GPIO_PWM5, CCT_MODE);
			}
			Serial.println("--------------------------------------------------");
		} else if (ParamAPP_ChannelMode == PT_ChannelModes_RGBW_D) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: RGBW_D, 2 lights");
			// RGBW
			Serial.print("Channel 1 (RGBW) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_DimSpeed);
				Light1.configDimSpeed(ParamAPP_CH1_DimSpeed);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH1_MinColorTemp);
				Light1.configMinTemperature(ParamAPP_CH1_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH1_MaxColorTemp);
				Light1.configMaxTemperature(ParamAPP_CH1_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH1_DefaultColorTemp);
				Light1.configDefaultTemperature(ParamAPP_CH1_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				hsv_t paraDefaultHSV;
				paraDefaultHSV.fromDPT232600(knx.paramInt(APP_CH1_DefaultColor));
				Light1.configDefaultHsv(paraDefaultHSV);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
				Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
				Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
				Light1.initRgbwLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, ParamAPP_GPIO_PWM3, ParamAPP_GPIO_PWM4, WHITE_LED_RGB_EQUIVALENT);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamAPP_CH2_Active);
			if (ParamAPP_CH2_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH2_DimSpeed);
				Light2.configDimSpeed(ParamAPP_CH2_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH2_BrightnessDay);
				Light2.configDefaultBrightness(ParamAPP_CH2_BrightnessDay);
				Light2.registerStatusCallback(statusCallback_L2);
				Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
				Light2.initDimmableLight(ParamAPP_GPIO_PWM5);
			}
			Serial.println("--------------------------------------------------");
		} else if (ParamAPP_ChannelMode == PT_ChannelModes_RGB_CCT) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: RGB_CCT, 2 lights");
			// RGB
			Serial.print("Channel 1 (RGB) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_DimSpeed);
				Light1.configDimSpeed(ParamAPP_CH1_DimSpeed);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH1_MinColorTemp);
				Light1.configMinTemperature(ParamAPP_CH1_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH1_MaxColorTemp);
				Light1.configMaxTemperature(ParamAPP_CH1_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH1_DefaultColorTemp);
				Light1.configDefaultTemperature(ParamAPP_CH1_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				hsv_t paraDefaultHSV;
				paraDefaultHSV.fromDPT232600(knx.paramInt(APP_CH1_DefaultColor));
				Light1.configDefaultHsv(paraDefaultHSV);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
				Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
				Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
				Light1.initRgbLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, ParamAPP_GPIO_PWM3);
			}
			Serial.println("--------------------------------------------------");
			// CCT
			Serial.print("Channel 2 (CCT) active: "); Serial.println(ParamAPP_CH2_Active);
			if (ParamAPP_CH2_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH2_Active);
				Light2.configDimSpeed(ParamAPP_CH2_Active);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH2_MinColorTemp);
				Light2.configMinTemperature(ParamAPP_CH2_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH2_MaxColorTemp);
				Light2.configMaxTemperature(ParamAPP_CH2_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH2_DefaultColorTemp);
				Light2.configDefaultTemperature(ParamAPP_CH2_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH2_BrightnessDay);
				Light2.configDefaultBrightness(ParamAPP_CH2_BrightnessDay);
				Light2.registerStatusCallback(statusCallback_L2);
				Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
				Light2.registerTemperatureCallback(responseTemperatureCallback_L2);
				Light2.initTunableWhiteLight(ParamAPP_GPIO_PWM4, ParamAPP_GPIO_PWM5, CCT_MODE);
			}
			Serial.println("--------------------------------------------------");
		} else if (ParamAPP_ChannelMode == PT_ChannelModes_RGB_D_D) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: RGB_D_D, 3 lights");
			// RGB
			Serial.print("Channel 1 (RGB) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_DimSpeed);
				Light1.configDimSpeed(ParamAPP_CH1_DimSpeed);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH1_MinColorTemp);
				Light1.configMinTemperature(ParamAPP_CH1_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH1_MaxColorTemp);
				Light1.configMaxTemperature(ParamAPP_CH1_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH1_DefaultColorTemp);
				Light1.configDefaultTemperature(ParamAPP_CH1_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				hsv_t paraDefaultHSV;
				paraDefaultHSV.fromDPT232600(knx.paramInt(APP_CH1_DefaultColor));
				Light1.configDefaultHsv(paraDefaultHSV);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
				Light1.registerColorHsvCallback(responseColorHsvCallback_L1);
				Light1.registerColorRgbCallback(responseColorRgbCallback_L1);
				Light1.initRgbLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, ParamAPP_GPIO_PWM3);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamAPP_CH2_Active);
			if (ParamAPP_CH2_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH2_DimSpeed);
				Light2.configDimSpeed(ParamAPP_CH2_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH2_BrightnessDay);
				Light2.configDefaultBrightness(ParamAPP_CH2_BrightnessDay);
				Light2.registerStatusCallback(statusCallback_L2);
				Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
				Light2.initDimmableLight(ParamAPP_GPIO_PWM4);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamAPP_CH3_Active);
			if (ParamAPP_CH3_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH3_DimSpeed);
				Light3.configDimSpeed(ParamAPP_CH3_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH3_BrightnessDay);
				Light3.configDefaultBrightness(ParamAPP_CH3_BrightnessDay);
				Light3.registerStatusCallback(statusCallback_L3);
				Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
				Light3.initDimmableLight(ParamAPP_GPIO_PWM5);
			}
			Serial.println("--------------------------------------------------");
		} else if (ParamAPP_ChannelMode == PT_ChannelModes_CCT_CCT_D) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: CCT_CCT_D, 3 lights");
			// CCT
			Serial.print("Channel 1 (CCT) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_Active);
				Light1.configDimSpeed(ParamAPP_CH1_Active);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH1_MinColorTemp);
				Light1.configMinTemperature(ParamAPP_CH1_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH1_MaxColorTemp);
				Light1.configMaxTemperature(ParamAPP_CH1_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH2_DefaultColorTemp);
				Light1.configDefaultTemperature(ParamAPP_CH1_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
				Light1.initTunableWhiteLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, CCT_MODE);
			}
			Serial.println("--------------------------------------------------");
			// CCT
			Serial.print("Channel 2 (CCT) active: "); Serial.println(ParamAPP_CH2_Active);
			if (ParamAPP_CH2_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH2_Active);
				Light2.configDimSpeed(ParamAPP_CH2_Active);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH2_MinColorTemp);
				Light2.configMinTemperature(ParamAPP_CH2_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH2_MaxColorTemp);
				Light2.configMaxTemperature(ParamAPP_CH2_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH2_DefaultColorTemp);
				Light2.configDefaultTemperature(ParamAPP_CH2_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH2_BrightnessDay);
				Light2.configDefaultBrightness(ParamAPP_CH2_BrightnessDay);
				Light2.registerStatusCallback(statusCallback_L2);
				Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
				Light2.registerTemperatureCallback(responseTemperatureCallback_L2);
				Light2.initTunableWhiteLight(ParamAPP_GPIO_PWM3, ParamAPP_GPIO_PWM4, CCT_MODE);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamAPP_CH3_Active);
			if (ParamAPP_CH3_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH3_DimSpeed);
				Light3.configDimSpeed(ParamAPP_CH3_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH3_BrightnessDay);
				Light3.configDefaultBrightness(ParamAPP_CH3_BrightnessDay);
				Light3.registerStatusCallback(statusCallback_L3);
				Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
				Light3.initDimmableLight(ParamAPP_GPIO_PWM5);
			}
			Serial.println("--------------------------------------------------");
		} else if (ParamAPP_ChannelMode == PT_ChannelModes_CCT_D_D_D) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: CCT_D_D_D, 4 lights");
			// CCT
			Serial.print("Channel 1 (CCT) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_Active);
				Light1.configDimSpeed(ParamAPP_CH1_Active);
				Serial.print("Min CT: "); Serial.println(ParamAPP_CH1_MinColorTemp);
				Light1.configMinTemperature(ParamAPP_CH1_MinColorTemp);
				Serial.print("Max CT: "); Serial.println(ParamAPP_CH1_MaxColorTemp);
				Light1.configMaxTemperature(ParamAPP_CH1_MaxColorTemp);
				Serial.print("Def CT: "); Serial.println(ParamAPP_CH2_DefaultColorTemp);
				Light1.configDefaultTemperature(ParamAPP_CH1_DefaultColorTemp);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
				Light1.initTunableWhiteLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, CCT_MODE);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamAPP_CH2_Active);
			if (ParamAPP_CH2_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH2_DimSpeed);
				Light2.configDimSpeed(ParamAPP_CH2_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH2_BrightnessDay);
				Light2.configDefaultBrightness(ParamAPP_CH2_BrightnessDay);
				Light2.registerStatusCallback(statusCallback_L2);
				Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
				Light2.initDimmableLight(ParamAPP_GPIO_PWM3);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamAPP_CH3_Active);
			if (ParamAPP_CH3_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH3_DimSpeed);
				Light3.configDimSpeed(ParamAPP_CH3_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH3_BrightnessDay);
				Light3.configDefaultBrightness(ParamAPP_CH3_BrightnessDay);
				Light3.registerStatusCallback(statusCallback_L3);
				Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
				Light3.initDimmableLight(ParamAPP_GPIO_PWM4);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 4 (DIM) active: "); Serial.println(ParamAPP_CH4_Active);
			if (ParamAPP_CH4_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH4_DimSpeed);
				Light4.configDimSpeed(ParamAPP_CH4_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH4_BrightnessDay);
				Light4.configDefaultBrightness(ParamAPP_CH4_BrightnessDay);
				Light4.registerStatusCallback(statusCallback_L4);
				Light4.registerBrightnessCallback(responseBrightnessCallback_L4);
				Light4.initDimmableLight(ParamAPP_GPIO_PWM5);
			}
			Serial.println("--------------------------------------------------");
		} else if (ParamAPP_ChannelMode == PT_ChannelModes_D_D_D_D_D) {
			Serial.println("--------------------------------------------------");
			Serial.println("Channel setup: D_D_D_D_D, 5 lights");
			// DIM
			Serial.print("Channel 1 (DIM) active: "); Serial.println(ParamAPP_CH1_Active);
			if (ParamAPP_CH1_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH1_DimSpeed);
				Light1.configDimSpeed(ParamAPP_CH1_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH1_BrightnessDay);
				Light1.configDefaultBrightness(ParamAPP_CH1_BrightnessDay);
				Light1.registerStatusCallback(statusCallback_L1);
				Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
				Light1.initDimmableLight(ParamAPP_GPIO_PWM1);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamAPP_CH2_Active);
			if (ParamAPP_CH2_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH2_DimSpeed);
				Light2.configDimSpeed(ParamAPP_CH2_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH2_BrightnessDay);
				Light2.configDefaultBrightness(ParamAPP_CH2_BrightnessDay);
				Light2.registerStatusCallback(statusCallback_L2);
				Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
				Light2.initDimmableLight(ParamAPP_GPIO_PWM2);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamAPP_CH3_Active);
			if (ParamAPP_CH3_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH3_DimSpeed);
				Light3.configDimSpeed(ParamAPP_CH3_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH3_BrightnessDay);
				Light3.configDefaultBrightness(ParamAPP_CH3_BrightnessDay);
				Light3.registerStatusCallback(statusCallback_L3);
				Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
				Light3.initDimmableLight(ParamAPP_GPIO_PWM3);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 4 (DIM) active: "); Serial.println(ParamAPP_CH4_Active);
			if (ParamAPP_CH4_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH4_DimSpeed);
				Light4.configDimSpeed(ParamAPP_CH4_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH4_BrightnessDay);
				Light4.configDefaultBrightness(ParamAPP_CH4_BrightnessDay);
				Light4.registerStatusCallback(statusCallback_L4);
				Light4.registerBrightnessCallback(responseBrightnessCallback_L4);
				Light4.initDimmableLight(ParamAPP_GPIO_PWM4);
			}
			Serial.println("--------------------------------------------------");
			// DIM
			Serial.print("Channel 5 (DIM) active: "); Serial.println(ParamAPP_CH5_Active);
			if (ParamAPP_CH5_Active == PT_OnOff_Ein) {
				Serial.print("Dim Speed: "); Serial.println(ParamAPP_CH5_DimSpeed);
				Light5.configDimSpeed(ParamAPP_CH5_DimSpeed);
				Serial.print("Def Brightness: "); Serial.println(ParamAPP_CH5_BrightnessDay);
				Light5.configDefaultBrightness(ParamAPP_CH5_BrightnessDay);
				Light5.registerStatusCallback(statusCallback_L5);
				Light5.registerBrightnessCallback(responseBrightnessCallback_L5);
				Light5.initDimmableLight(ParamAPP_GPIO_PWM5);
			}
			Serial.println("--------------------------------------------------");
		}

	}

	Serial.println(HOSTNAME);
	Serial.println(getKnxPhysAddr());

	// Red status led off and green led on after setup
	#ifdef STAT_LED_GN
	digitalWrite(STAT_LED_GN, STAT_LED_ON);
	#endif
	#ifdef STAT_LED_RD
	digitalWrite(STAT_LED_RD, STAT_LED_OFF);
	#endif

	#if defined(ESP8266) || defined(ESP32)
	WiFi.persistent(false); // Solve possible wifi init errors
	WiFi.disconnect(true);  // Delete SDK wifi config
	#endif

	WiFi.mode(WIFI_STA);
	WiFi.hostname(HOSTNAME);
	//WiFi.setAutoConnect(true);
	//WiFi.setAutoReconnect(true);
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	WiFi.hostname(HOSTNAME); // Set hostname twice
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		// Implement AP mode here after timeout if needed
		// however an open AP can be a security issue
		// settingsAP();
	}

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
	if (WiFi.status() == WL_CONNECTED) {
		knxWebServ.loop();
			if(getKnxActive()) {
				knx.loop();
		}
		// only run the application code if the device was configured with ETS
		if (!knxConfigOk) return;

		if (!initSent) {
			Light1.sendStatusUpdate();
			Light2.sendStatusUpdate();
			Light3.sendStatusUpdate();
			Light4.sendStatusUpdate();
			Light5.sendStatusUpdate();
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