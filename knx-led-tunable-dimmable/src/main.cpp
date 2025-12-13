#include "main.h"

// callback from knx value change
void knxCallback(GroupObject &go) {
    // callbacks are now handled in the class, not per instance,
    // this means, we have to check, which GroupObject is calling back
/*		Serial.println("IN");
		Serial.println(go.asap());

		if (&go == &ParamAPP_DayNight) {
			bool itsDay;
			(ParamAPP_DayNight) ? (itsDay = go.value(DPT_Switch)) : (itsDay = !go.value(DPT_Switch));
			uint8_t defaultBrightness = itsDay ? ParamRGBCCT_BrightnessDay : ParamRGBCCT_BrightnessNight;
			Light1.configDefaultBrightness(defaultBrightness);
			defaultBrightness = itsDay ? ParamRGBCCT_BrightnessDay : ParamRGBCCT_BrightnessNight;
			Light2.configDefaultBrightness(defaultBrightness);
			Light3.configDefaultBrightness(defaultBrightness);
			Light4.configDefaultBrightness(defaultBrightness);
			Light5.configDefaultBrightness(defaultBrightness);
			*/

		if (ParamAPP_ChannelMode == PT_ChannelModes_RGBCCT) {
			if (go.asap() == APP_KoGeneralDayNight) {
				bool itsDay;
				(ParamAPP_DayNight) ? (itsDay = go.value(DPT_Switch)) : (itsDay = !go.value(DPT_Switch));
				uint8_t defaultBrightness = itsDay ? ParamRGBCCT_BrightnessDay : ParamRGBCCT_BrightnessNight;
				Light1.configDefaultBrightness(defaultBrightness);
			} else if (&go == &KoRGBCCT_SwitchIndex(0)) {
				Light1.switchLight(go.value(DPT_Switch));
			} else if (&go == &KoRGBCCT_BrightnessAbsoluteIndex(0)) {
				Light1.setBrightness(go.value(DPT_Percent_U8));
			} else if (&go == &KoRGBCCT_BrightnessRelativeIndex(0)) {
				dpt3_t dimCmd;
        dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
        Light1.setRelDimCmd(dimCmd);
			} else if (&go == &KoRGBCCT_ColorTempAbsoluteIndex(0)) {
				Light1.setTemperature(go.value(DPT_Percent_U8));
			} else if (&go == &KoRGBCCT_ColorTempRelativeIndex(0)) {
				dpt3_t dimCmd;
        dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
        Light1.setRelTemperatureCmd(dimCmd);
			} else if (&go == &KoRGBCCT_ColorRGBIndex(0)) {
        rgb_t rgb;
        rgb.fromDPT232600(go.value(DPT_Colour_RGB));
        Light1.setRgb(rgb);
			} else if (&go == &KoRGBCCT_ColorHSVIndex(0)) {
        hsv_t hsv;
        hsv.fromDPT232600(go.value(DPT_Colour_RGB));
        Light1.setHsv(hsv);
			} else if (&go == &KoRGBCCT_HueAbsoluteIndex(0)) {
        hsv_t hsv = Light1.getHsv();
        hsv.h = go.value(DPT_Percent_U8);
        Light1.setHsv(hsv);
			} else if (&go == &KoRGBCCT_HueRelativeIndex(0)) {
        dpt3_t dimCmd;
        dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
        Light1.setRelHueCmd(dimCmd);
			} else if (&go == &KoRGBCCT_SaturationAbsoluteIndex(0)) {
        hsv_t hsv = Light1.getHsv();
        hsv.h = go.value(DPT_Percent_U8);
        Light1.setHsv(hsv);
			} else if (&go == &KoRGBCCT_SaturationRelativeIndex(0)) {
        dpt3_t dimCmd;
        dimCmd.fromDPT3(go.value(DPT_Control_Dimming));
        Light1.setRelSaturationCmd(dimCmd);
			}
		}
	}

void statusCallback_L1(bool state) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGBCCT: {
			if (ParamRGBCCT_Active) KoRGBCCT_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_RGB_CCT:
		case PT_ChannelModes_RGB_D_D: {
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_RGBW_D: {
			if (ParamRGBW_Active) KoRGBW_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D:
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(0)) KoDIM_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
	}
}

void statusCallback_L2(bool state) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGB_CCT:
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusIndex(0).value(state, DPT_Switch);
			break;
		case PT_ChannelModes_RGB_D_D: {
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_RGBW_D: {
			if (ParamRGBW_Active) KoRGBW_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D:
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusIndex(0).value(state, DPT_Switch);
			break;
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(0)) KoDIM_StatusIndex(0).value(state, DPT_Switch);
			break;
		}
	}
}

void statusCallback_L3(bool state) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGB_D_D: {
			if (ParamDIM_ActiveIndex(1)) KoDIM_StatusIndex(1).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D:
			if (ParamDIM_ActiveIndex(0)) KoDIM_StatusIndex(0).value(state, DPT_Switch);
			break;
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamDIM_ActiveIndex(1)) KoDIM_StatusIndex(1).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(2)) KoDIM_StatusIndex(2).value(state, DPT_Switch);
			break;
		}
	}
}

void statusCallback_L4(bool state) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamDIM_ActiveIndex(2)) KoDIM_StatusIndex(2).value(state, DPT_Switch);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(3)) KoDIM_StatusIndex(3).value(state, DPT_Switch);
			break;
		}
	}
}

void statusCallback_L5(bool state) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(4)) KoDIM_StatusIndex(4).value(state, DPT_Switch);
			break;
		}
	}
}

void responseBrightnessCallback_L1(uint8_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGBCCT: {
			if (ParamRGBCCT_Active) KoRGBCCT_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_RGB_CCT:
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		case PT_ChannelModes_RGB_D_D: {
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_RGBW_D: {
			if (ParamRGBW_Active) KoRGBW_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D:
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(0)) KoDIM_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseBrightnessCallback_L2(uint8_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGB_CCT: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_RGBW_D:
		case PT_ChannelModes_RGB_D_D:
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamDIM_ActiveIndex(0)) KoDIM_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D: {
			if (ParamCCT_ActiveIndex(1)) KoCCT_StatusBrightnessIndex(1).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(1)) KoDIM_StatusBrightnessIndex(1).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseBrightnessCallback_L3(uint8_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGB_D_D:
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamDIM_ActiveIndex(1)) KoDIM_StatusBrightnessIndex(1).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D: {
			if (ParamDIM_ActiveIndex(0)) KoDIM_StatusBrightnessIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(2)) KoDIM_StatusBrightnessIndex(2).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseBrightnessCallback_L4(uint8_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamDIM_ActiveIndex(2)) KoDIM_StatusBrightnessIndex(2).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(3)) KoDIM_StatusBrightnessIndex(3).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseBrightnessCallback_L5(uint8_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_D_D_D_D_D: {
			if (ParamDIM_ActiveIndex(4)) KoDIM_StatusBrightnessIndex(4).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseTemperatureCallback_L1(uint16_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGBCCT: {
			if (ParamRGBCCT_Active) KoRGBCCT_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_RGB_CCT: {
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_RGBW_D: {
			if (ParamRGBW_Active) KoRGBW_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_RGB_D_D: {
			if (ParamRGB_ActiveIndex(0)) KoRGB_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_CCT_D_D_D: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_D_D_D_D_D: {
//			if (ParamDIM_ActiveIndex(0)) KoDIM_ColorTempAbsoluteIndex(0).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseTemperatureCallback_L2(uint16_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGB_CCT: {
			if (ParamCCT_ActiveIndex(0)) KoCCT_StatusColorTempIndex(0).value(value, DPT_Percent_U8);
			break;
		}
		case PT_ChannelModes_CCT_CCT_D: {
			if (ParamCCT_ActiveIndex(1)) KoCCT_StatusColorTempIndex(1).value(value, DPT_Percent_U8);
			break;
		}
	}
}

void responseColorHsvCallback_L1(hsv_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGBCCT: {
			if (ParamRGBCCT_Active) {
				KoRGBCCT_StatusHSVIndex(0).value(value.toDPT232600(), DPT_Colour_RGB);
				KoRGBCCT_StatusHueIndex(0).value(value.h, DPT_Percent_U8);
				KoRGBCCT_StatusSaturationIndex(0).value(value.s, DPT_Percent_U8);
			}
			break;
		}
		case PT_ChannelModes_RGB_CCT:
		case PT_ChannelModes_RGB_D_D: {
			if (ParamRGBCCT_Active) {
				KoRGB_StatusHSVIndex(0).value(value.toDPT232600(), DPT_Colour_RGB);
				KoRGB_StatusHueIndex(0).value(value.h, DPT_Percent_U8);
				KoRGB_StatusSaturationIndex(0).value(value.s, DPT_Percent_U8);
			}
			break;
		}
		case PT_ChannelModes_RGBW_D: {
			if (ParamRGBCCT_Active) {
				KoRGBW_StatusHSVIndex(0).value(value.toDPT232600(), DPT_Colour_RGB);
				KoRGBW_StatusHueIndex(0).value(value.h, DPT_Percent_U8);
				KoRGBW_StatusSaturationIndex(0).value(value.s, DPT_Percent_U8);
			}
			break;
		}
	}
}

void responseColorRgbCallback_L1(rgb_t value) {
	switch (ParamAPP_ChannelMode) {
		case PT_ChannelModes_RGBCCT: {
			if (ParamRGBCCT_Active) KoRGBCCT_StatusRGBIndex(0).value(value.toDPT232600(), DPT_Colour_RGB);
			break;
		}
		case PT_ChannelModes_RGB_CCT:
		case PT_ChannelModes_RGB_D_D: {
			if (ParamRGBCCT_Active) KoRGB_StatusRGBIndex(0).value(value.toDPT232600(), DPT_Colour_RGB);
			break;
		}
		case PT_ChannelModes_RGBW_D: {
			if (ParamRGBCCT_Active) KoRGBW_StatusRGBIndex(0).value(value.toDPT232600(), DPT_Colour_RGB);
			break;
		}
	}
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

	knxConfigOk = knx.configured() && checkKnxApp(); // && knx.bau().groupObjectTable().entryCount() == MAIN_MaxKoNumber; //MAIN_ParameterSize

	// Setup device after device was configured by ETS
	if (knxConfigOk) {
        GroupObject::classCallback(knxCallback); // callbacks are now handled per class, not per instance

        // read hostname from ETS config
        HOSTNAME = (char *)knx.paramData(APP_Hostname);

				for (u_int8_t i=0;i<5;i++) {
					Serial.print("ACTIVE:");
					Serial.println(ParamDIM_ActiveIndex(i));
					Serial.print("DIMSPEED:");
					Serial.println(ParamDIM_DimSpeedIndex(i));
				}

				// read channel setup and individual parameters from ETS config
				if (ParamAPP_ChannelMode == PT_ChannelModes_RGBCCT) {
					Serial.println("--------------------------------------------------");
					Serial.println("Channel setup: RGBCCT, 1 light");
					// RGBCCT
					Serial.print("Channel 1 (RGBCCT) active: "); Serial.println(ParamRGBCCT_Active);
					if (ParamRGBCCT_Active == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamRGBCCT_DimSpeed);
						Light1.configDimSpeed(ParamRGBCCT_DimSpeed);
						Serial.print("Min CT: "); Serial.println(ParamRGBCCT_MinColorTemp);
						Light1.configMinTemperature(ParamRGBCCT_MinColorTemp);
						Serial.print("Max CT: "); Serial.println(ParamRGBCCT_MaxColorTemp);
						Light1.configMinTemperature(ParamRGBCCT_MaxColorTemp);
						Serial.print("Def CT: "); Serial.println(ParamRGBCCT_DefaultColorTemp);
						Light1.configDefaultTemperature(ParamRGBCCT_DefaultColorTemp);
						Serial.print("Def Brightness: "); Serial.println(ParamRGBCCT_BrightnessDay);
						Light1.configDefaultBrightness(ParamRGBCCT_BrightnessDay);
						hsv_t paraDefaultHSV;
						paraDefaultHSV.fromDPT232600(ParamRGBCCT_DefaultColorTemp);
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
					Serial.println("Channel setup: RGBW_D, 2 lights");
					// RGBW
					Serial.print("Channel 1 (RGBW) active: "); Serial.println(ParamRGBW_Active);
					if (ParamRGBW_Active == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamRGBW_DimSpeed);
						Light1.configDimSpeed(ParamRGBW_DimSpeed);
						Serial.print("Min CT: "); Serial.println(ParamRGBW_MinColorTemp);
						Light1.configMinTemperature(ParamRGBW_MinColorTemp);
						Serial.print("Max CT: "); Serial.println(ParamRGBW_MaxColorTemp);
						Light1.configMinTemperature(ParamRGBW_MaxColorTemp);
						Serial.print("Def CT: "); Serial.println(ParamRGBW_DefaultColorTemp);
						Light1.configDefaultTemperature(ParamRGBW_DefaultColorTemp);
						Serial.print("Def Brightness: "); Serial.println(ParamRGBW_BrightnessDay);
						Light1.configDefaultBrightness(ParamRGBW_BrightnessDay);
						hsv_t paraDefaultHSV;
						paraDefaultHSV.fromDPT232600(ParamRGBW_DefaultColorTemp);
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
					Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(0));
					if (ParamDIM_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(0));
						Light2.configDimSpeed(ParamDIM_DimSpeedIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(0));
						Light2.configDefaultBrightness(ParamDIM_BrightnessDayIndex(0));
						Light2.registerStatusCallback(statusCallback_L1);
		        Light2.registerBrightnessCallback(responseBrightnessCallback_L1);
						Light2.initDimmableLight(ParamAPP_GPIO_PWM5);
					}
					Serial.println("--------------------------------------------------");
				} else if (ParamAPP_ChannelMode == PT_ChannelModes_RGB_CCT) {
					Serial.println("Channel setup: RGB_CCT, 2 lights");
					// RGB
					Serial.print("Channel 1 (RGB) active: "); Serial.println(ParamRGB_ActiveIndex(0));
					if (ParamRGB_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamRGB_DimSpeedIndex(0));
						Light1.configDimSpeed(ParamRGB_DimSpeedIndex(0));
						Serial.print("Min CT: "); Serial.println(ParamRGB_MinColorTempIndex(0));
						Light1.configMinTemperature(ParamRGB_MinColorTempIndex(0));
						Serial.print("Max CT: "); Serial.println(ParamRGB_MaxColorTempIndex(0));
						Light1.configMinTemperature(ParamRGB_MaxColorTempIndex(0));
						Serial.print("Def CT: "); Serial.println(ParamRGB_DefaultColorTempIndex(0));
						Light1.configDefaultTemperature(ParamRGB_DefaultColorTempIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamRGB_BrightnessDayIndex(0));
						Light1.configDefaultBrightness(ParamRGB_BrightnessDayIndex(0));
						hsv_t paraDefaultHSV;
						paraDefaultHSV.fromDPT232600(ParamRGB_DefaultColorTempIndex(0));
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
					Serial.print("Channel 2 (CCT) active: "); Serial.println(ParamCCT_ActiveIndex(0));
					if (ParamCCT_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamCCT_DimSpeedIndex(0));
						Light2.configDimSpeed(ParamCCT_DimSpeedIndex(0));
						Serial.print("Min CT: "); Serial.println(ParamCCT_MinColorTempIndex(0));
						Light2.configMinTemperature(ParamCCT_MinColorTempIndex(0));
						Serial.print("Max CT: "); Serial.println(ParamCCT_MaxColorTempIndex(0));
						Light2.configMinTemperature(ParamCCT_MaxColorTempIndex(0));
						Serial.print("Def CT: "); Serial.println(ParamCCT_DefaultColorTempIndex(0));
						Light2.configDefaultTemperature(ParamCCT_DefaultColorTempIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamCCT_BrightnessDayIndex(0));
						Light2.configDefaultBrightness(ParamCCT_BrightnessDayIndex(0));
						Light2.registerStatusCallback(statusCallback_L1);
		        Light2.registerBrightnessCallback(responseBrightnessCallback_L1);
    		    Light2.registerTemperatureCallback(responseTemperatureCallback_L1);
						Light2.initTunableWhiteLight(ParamAPP_GPIO_PWM4, ParamAPP_GPIO_PWM5, CCT_MODE);
					}
					Serial.println("--------------------------------------------------");
				} else if (ParamAPP_ChannelMode == PT_ChannelModes_RGB_D_D) {
					Serial.println("Channel setup: RGB_D_D, 3 lights");
					// RGB
					Serial.print("Channel 1 (RGB) active: "); Serial.println(ParamRGB_ActiveIndex(0));
					if (ParamRGB_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamRGB_DimSpeedIndex(0));
						Light1.configDimSpeed(ParamRGB_DimSpeedIndex(0));
						Serial.print("Min CT: "); Serial.println(ParamRGB_MinColorTempIndex(0));
						Light1.configMinTemperature(ParamRGB_MinColorTempIndex(0));
						Serial.print("Max CT: "); Serial.println(ParamRGB_MaxColorTempIndex(0));
						Light1.configMinTemperature(ParamRGB_MaxColorTempIndex(0));
						Serial.print("Def CT: "); Serial.println(ParamRGB_DefaultColorTempIndex(0));
						Light1.configDefaultTemperature(ParamRGB_DefaultColorTempIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamRGB_BrightnessDayIndex(0));
						Light1.configDefaultBrightness(ParamRGB_BrightnessDayIndex(0));
						hsv_t paraDefaultHSV;
						paraDefaultHSV.fromDPT232600(ParamRGB_DefaultColorTempIndex(0));
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
					Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(0));
					if (ParamDIM_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(0));
						Light2.configDimSpeed(ParamDIM_DimSpeedIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(0));
						Light2.configDefaultBrightness(ParamDIM_BrightnessDayIndex(0));
						Light2.registerStatusCallback(statusCallback_L2);
		        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
						Light2.initDimmableLight(ParamAPP_GPIO_PWM4);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(1));
					if (ParamDIM_ActiveIndex(1) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(1));
						Light3.configDimSpeed(ParamDIM_DimSpeedIndex(1));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(1));
						Light3.configDefaultBrightness(ParamDIM_BrightnessDayIndex(1));
						Light3.registerStatusCallback(statusCallback_L3);
		        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
						Light3.initDimmableLight(ParamAPP_GPIO_PWM5);
					}
					Serial.println("--------------------------------------------------");
				} else if (ParamAPP_ChannelMode == PT_ChannelModes_CCT_CCT_D) {
					Serial.println("Channel setup: CCT_CCT_D, 3 lights");
					// CCT
					Serial.print("Channel 1 (CCT) active: "); Serial.println(ParamCCT_ActiveIndex(0));
					if (ParamCCT_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamCCT_DimSpeedIndex(0));
						Light1.configDimSpeed(ParamCCT_DimSpeedIndex(0));
						Serial.print("Min CT: "); Serial.println(ParamCCT_MinColorTempIndex(0));
						Light1.configMinTemperature(ParamCCT_MinColorTempIndex(0));
						Serial.print("Max CT: "); Serial.println(ParamCCT_MaxColorTempIndex(0));
						Light1.configMinTemperature(ParamCCT_MaxColorTempIndex(0));
						Serial.print("Def CT: "); Serial.println(ParamCCT_DefaultColorTempIndex(0));
						Light1.configDefaultTemperature(ParamCCT_DefaultColorTempIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamCCT_BrightnessDayIndex(0));
						Light1.configDefaultBrightness(ParamCCT_BrightnessDayIndex(0));
						Light1.registerStatusCallback(statusCallback_L1);
		        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
    		    Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
						Light1.initTunableWhiteLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, CCT_MODE);
					}
					Serial.println("--------------------------------------------------");
					// CCT
					Serial.print("Channel 2 (CCT) active: "); Serial.println(ParamCCT_ActiveIndex(1));
					if (ParamCCT_ActiveIndex(1) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamCCT_DimSpeedIndex(1));
						Light2.configDimSpeed(ParamCCT_DimSpeedIndex(1));
						Serial.print("Min CT: "); Serial.println(ParamCCT_MinColorTempIndex(1));
						Light2.configMinTemperature(ParamCCT_MinColorTempIndex(1));
						Serial.print("Max CT: "); Serial.println(ParamCCT_MaxColorTempIndex(1));
						Light2.configMinTemperature(ParamCCT_MaxColorTempIndex(1));
						Serial.print("Def CT: "); Serial.println(ParamCCT_DefaultColorTempIndex(1));
						Light2.configDefaultTemperature(ParamCCT_DefaultColorTempIndex(1));
						Serial.print("Def Brightness: "); Serial.println(ParamCCT_BrightnessDayIndex(1));
						Light2.configDefaultBrightness(ParamCCT_BrightnessDayIndex(1));
						Light2.registerStatusCallback(statusCallback_L2);
		        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
    		    Light2.registerTemperatureCallback(responseTemperatureCallback_L2);
						Light2.initTunableWhiteLight(ParamAPP_GPIO_PWM3, ParamAPP_GPIO_PWM4, CCT_MODE);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(0));
					if (ParamDIM_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(0));
						Light3.configDimSpeed(ParamDIM_DimSpeedIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(0));
						Light3.configDefaultBrightness(ParamDIM_BrightnessDayIndex(0));
						Light3.registerStatusCallback(statusCallback_L2);
		        Light3.registerBrightnessCallback(responseBrightnessCallback_L2);
						Light3.initDimmableLight(ParamAPP_GPIO_PWM5);
					}
					Serial.println("--------------------------------------------------");
				} else if (ParamAPP_ChannelMode == PT_ChannelModes_CCT_D_D_D) {
					Serial.println("Channel setup: CCT_D_D_D, 4 lights");
					// CCT
					Serial.print("Channel 1 (CCT) active: "); Serial.println(ParamCCT_ActiveIndex(0));
					if (ParamCCT_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamCCT_DimSpeedIndex(0));
						Light1.configDimSpeed(ParamCCT_DimSpeedIndex(0));
						Serial.print("Min CT: "); Serial.println(ParamCCT_MinColorTempIndex(0));
						Light1.configMinTemperature(ParamCCT_MinColorTempIndex(0));
						Serial.print("Max CT: "); Serial.println(ParamCCT_MaxColorTempIndex(0));
						Light1.configMinTemperature(ParamCCT_MaxColorTempIndex(0));
						Serial.print("Def CT: "); Serial.println(ParamCCT_DefaultColorTempIndex(0));
						Light1.configDefaultTemperature(ParamCCT_DefaultColorTempIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamCCT_BrightnessDayIndex(0));
						Light1.configDefaultBrightness(ParamCCT_BrightnessDayIndex(0));
						Light1.registerStatusCallback(statusCallback_L1);
		        Light1.registerBrightnessCallback(responseBrightnessCallback_L1);
    		    Light1.registerTemperatureCallback(responseTemperatureCallback_L1);
						Light1.initTunableWhiteLight(ParamAPP_GPIO_PWM1, ParamAPP_GPIO_PWM2, CCT_MODE);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(0));
					if (ParamDIM_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(0));
						Light2.configDimSpeed(ParamDIM_DimSpeedIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(0));
						Light2.configDefaultBrightness(ParamDIM_BrightnessDayIndex(0));
						Light2.registerStatusCallback(statusCallback_L2);
		        Light2.registerBrightnessCallback(responseBrightnessCallback_L2);
						Light2.initDimmableLight(ParamAPP_GPIO_PWM3);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(1));
					if (ParamDIM_ActiveIndex(1) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(1));
						Light3.configDimSpeed(ParamDIM_DimSpeedIndex(1));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(1));
						Light3.configDefaultBrightness(ParamDIM_BrightnessDayIndex(1));
						Light3.registerStatusCallback(statusCallback_L3);
		        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
						Light3.initDimmableLight(ParamAPP_GPIO_PWM4);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 4 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(2));
					if (ParamDIM_ActiveIndex(2) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(2));
						Light4.configDimSpeed(ParamDIM_DimSpeedIndex(2));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(2));
						Light4.configDefaultBrightness(ParamDIM_BrightnessDayIndex(2));
						Light4.registerStatusCallback(statusCallback_L3);
		        Light4.registerBrightnessCallback(responseBrightnessCallback_L3);
						Light4.initDimmableLight(ParamAPP_GPIO_PWM5);
					}
					Serial.println("--------------------------------------------------");
				} else if (ParamAPP_ChannelMode == PT_ChannelModes_D_D_D_D_D) {
					Serial.println("Channel setup: D_D_D_D_D, 5 lights");
					// DIM
					Serial.print("Channel 1 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(0));
					if (ParamDIM_ActiveIndex(0) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(0));
						Light1.configDimSpeed(ParamDIM_DimSpeedIndex(0));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(0));
						Light1.configDefaultBrightness(ParamDIM_BrightnessDayIndex(0));
						Light1.registerStatusCallback(statusCallback_L2);
		        Light1.registerBrightnessCallback(responseBrightnessCallback_L2);
						Light1.initDimmableLight(ParamAPP_GPIO_PWM1);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 2 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(1));
					if (ParamDIM_ActiveIndex(1) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(1));
						Light2.configDimSpeed(ParamDIM_DimSpeedIndex(1));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(1));
						Light2.configDefaultBrightness(ParamDIM_BrightnessDayIndex(1));
						Light2.registerStatusCallback(statusCallback_L3);
		        Light2.registerBrightnessCallback(responseBrightnessCallback_L3);
						Light2.initDimmableLight(ParamAPP_GPIO_PWM2);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 3 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(2));
					if (ParamDIM_ActiveIndex(2) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(2));
						Light3.configDimSpeed(ParamDIM_DimSpeedIndex(2));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(2));
						Light3.configDefaultBrightness(ParamDIM_BrightnessDayIndex(2));
						Light3.registerStatusCallback(statusCallback_L3);
		        Light3.registerBrightnessCallback(responseBrightnessCallback_L3);
						Light3.initDimmableLight(ParamAPP_GPIO_PWM3);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 4 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(3));
					if (ParamDIM_ActiveIndex(3) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(3));
						Light4.configDimSpeed(ParamDIM_DimSpeedIndex(3));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(3));
						Light4.configDefaultBrightness(ParamDIM_BrightnessDayIndex(3));
						Light4.registerStatusCallback(statusCallback_L4);
		        Light4.registerBrightnessCallback(responseBrightnessCallback_L4);
						Light4.initDimmableLight(ParamAPP_GPIO_PWM4);
					}
					Serial.println("--------------------------------------------------");
					// DIM
					Serial.print("Channel 5 (DIM) active: "); Serial.println(ParamDIM_ActiveIndex(4));
					if (ParamDIM_ActiveIndex(4) == PT_OnOff_Ein) {
						Serial.print("Dim Speed: "); Serial.println(ParamDIM_DimSpeedIndex(4));
						Light5.configDimSpeed(ParamDIM_DimSpeedIndex(4));
						Serial.print("Def Brightness: "); Serial.println(ParamDIM_BrightnessDayIndex(4));
						Light5.configDefaultBrightness(ParamDIM_BrightnessDayIndex(4));
						Light5.registerStatusCallback(statusCallback_L5);
		        Light5.registerBrightnessCallback(responseBrightnessCallback_L5);
						Light5.initDimmableLight(ParamAPP_GPIO_PWM5);
					}
					Serial.println("--------------------------------------------------");
				}
			
        // read parameters from ETS config
/*        Light.configDimSpeed(ParamAPP_DimSpeed);
        Light.configDefaultBrightness(ParamAPP_LightBrightnessDay);
        Light.configDefaultTemperature(ParamAPP_LightDefaultColorTemp);
        hsv_t paraDefaultHsv;
        paraDefaultHsv.fromDPT232600(knx.paramInt(48));
        Light.configDefaultHsv(paraDefaultHsv);

        // register callbacks from LED controllers
        Light.registerStatusCallback(statusCallback);
        Light.registerBrightnessCallback(responseBrightnessCallback);
        Light.registerTemperatureCallback(responseTemperatureCallback);
        Light.registerColorHsvCallback(responseColorHsvCallback);
        Light.registerColorRgbCallback(responseColorRgbCallback);
				*/
    }
//    Light.initRgbcctLight(LED_PIN_R, LED_PIN_G, LED_PIN_B, LED_PIN_CW, LED_PIN_WW, CCT_MODE);

    Serial.println(HOSTNAME);
    Serial.println(getKnxPhysAddr());
		Serial.print("MAX KO#:"); Serial.println(MAIN_MaxKoNumber);
		Serial.print("Channel mode: "); Serial.println(ParamAPP_ChannelMode);

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
    while (WiFi.status() != WL_CONNECTED)
    {
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

void loop()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        knxWebServ.loop();
        if(getKnxActive())
        {
            knx.loop();
        }

        // only run the application code if the device was configured with ETS
        if (!knxConfigOk)
            return;

        if (!initSent)
        {
            Light1.sendStatusUpdate();
            initSent = true;
        }

        Light1.loop();
    }
    else
    {
        static unsigned int reconnectCounter = 0;
        if(reconnectCounter > 1000)
        {
            WiFi.reconnect();
            reconnectCounter=0;
        }
        reconnectCounter++;
    }
    keepCycleTime(MIN_CYCLE_TIME);
}