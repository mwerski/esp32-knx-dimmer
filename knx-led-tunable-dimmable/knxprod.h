#pragma once

#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                            (time & 0x3FFF) * 3600000 ) : 0 )
#define PT_OnOff_Aus 0
#define PT_OnOff_Ein 1
//--------------------Allgemein---------------------------
#define MAIN_OpenKnxId 0xAF
#define MAIN_ApplicationNumber 0x00
#define MAIN_ApplicationVersion 0x01
#define MAIN_OrderNumber "ESP32PWM"
#define MAIN_ParameterSize 184
#define MAIN_MaxKoNumber 109


#define APP_StartUpDelay		0x0000
#define APP_StartUpDelay_Shift	6
#define APP_StartUpDelay_Mask	0x03FF
// Offset: 0, Size: 10 Bit, Text: Einschaltverzögerung
#define ParamAPP_StartUpDelay ((uint)((knx.paramWord(APP_StartUpDelay) >> APP_StartUpDelay_Shift) & APP_StartUpDelay_Mask))
#define APP_Heartbeat		0x0002
#define APP_Heartbeat_Shift	6
#define APP_Heartbeat_Mask	0x03FF
// Offset: 2, Size: 10 Bit, Text: In Betrieb senden alle
#define ParamAPP_Heartbeat ((uint)((knx.paramWord(APP_Heartbeat) >> APP_Heartbeat_Shift) & APP_Heartbeat_Mask))
#define APP_Hostname		0x0004
// Offset: 4, Size: 256 Bit (32 Byte), Text: Hostname
#define ParamAPP_Hostname knx.paramData(APP_Hostname)
#define APP_PWMFrequency		0x0024
// Offset: 36, Size: 16 Bit (2 Byte), Text: PWM Frequenz
#define ParamAPP_PWMFrequency ((uint32_t)((knx.paramWord(APP_PWMFrequency))))
#define APP_DayNight		0x0026
// Offset: 38, Size: 1 Bit, Text: Tag/Nacht
#define ParamAPP_DayNight knx.paramBit(APP_DayNight, 0)
#define APP_ChannelMode		0x0026
#define APP_ChannelMode_Shift	4
#define APP_ChannelMode_Mask	0x0007
// Offset: 38, BitOffset: 1, Size: 3 Bit, Text: Kanalverteilung
#define ParamAPP_ChannelMode ((uint32_t)((knx.paramByte(APP_ChannelMode) >> APP_ChannelMode_Shift) & APP_ChannelMode_Mask))
#define APP_GPIO_PWM1		0x0027
#define APP_GPIO_PWM1_Shift	2
#define APP_GPIO_PWM1_Mask	0x003F
// Offset: 39, Size: 6 Bit, Text: GPIO Kanal 1
#define ParamAPP_GPIO_PWM1 ((uint32_t)((knx.paramByte(APP_GPIO_PWM1) >> APP_GPIO_PWM1_Shift) & APP_GPIO_PWM1_Mask))
#define APP_GPIO_PWM2		0x0028
#define APP_GPIO_PWM2_Shift	2
#define APP_GPIO_PWM2_Mask	0x003F
// Offset: 40, Size: 6 Bit, Text: GPIO Kanal 2
#define ParamAPP_GPIO_PWM2 ((uint32_t)((knx.paramByte(APP_GPIO_PWM2) >> APP_GPIO_PWM2_Shift) & APP_GPIO_PWM2_Mask))
#define APP_GPIO_PWM3		0x0029
#define APP_GPIO_PWM3_Shift	2
#define APP_GPIO_PWM3_Mask	0x003F
// Offset: 41, Size: 6 Bit, Text: GPIO Kanal 3
#define ParamAPP_GPIO_PWM3 ((uint32_t)((knx.paramByte(APP_GPIO_PWM3) >> APP_GPIO_PWM3_Shift) & APP_GPIO_PWM3_Mask))
#define APP_GPIO_PWM4		0x002A
#define APP_GPIO_PWM4_Shift	2
#define APP_GPIO_PWM4_Mask	0x003F
// Offset: 42, Size: 6 Bit, Text: GPIO Kanal 4
#define ParamAPP_GPIO_PWM4 ((uint32_t)((knx.paramByte(APP_GPIO_PWM4) >> APP_GPIO_PWM4_Shift) & APP_GPIO_PWM4_Mask))
#define APP_GPIO_PWM5		0x002B
#define APP_GPIO_PWM5_Shift	2
#define APP_GPIO_PWM5_Mask	0x003F
// Offset: 43, Size: 6 Bit, Text: GPIO Kanal 5
#define ParamAPP_GPIO_PWM5 ((uint32_t)((knx.paramByte(APP_GPIO_PWM5) >> APP_GPIO_PWM5_Shift) & APP_GPIO_PWM5_Mask))
#define APP_CH2active		0x0026
// Offset: 38, BitOffset: 4, Size: 1 Bit, Text: Kanal 2 aktiv
#define ParamAPP_CH2active knx.paramBit(APP_CH2active, 4)
#define APP_CH3active		0x0026
// Offset: 38, BitOffset: 5, Size: 1 Bit, Text: Kanal 3 aktiv
#define ParamAPP_CH3active knx.paramBit(APP_CH3active, 5)
#define APP_CH4active		0x0026
// Offset: 38, BitOffset: 6, Size: 1 Bit, Text: Kanal 4 aktiv
#define ParamAPP_CH4active knx.paramBit(APP_CH4active, 6)
#define APP_CH5active		0x0026
// Offset: 38, BitOffset: 7, Size: 1 Bit, Text: Kanal 5 aktiv
#define ParamAPP_CH5active knx.paramBit(APP_CH5active, 7)
//!< Number: 0, Text: Zentral, Function: Tag/Nacht
#define APP_KoGeneralDayNight 0
#define KoAPP_GeneralDayNight knx.getGroupObject(APP_KoGeneralDayNight)
//!< Number: 1, Text: Zentral, Function: In Betrieb
#define APP_KoHeartbeat 1
#define KoAPP_Heartbeat knx.getGroupObject(APP_KoHeartbeat)

//---------------------Modules----------------------------

//-----Module specific starts
#define RGBCCT_ParamBlockOffset 44
#define RGBCCT_ParamBlockSize 13
#define RGBW_ParamBlockOffset 57
#define RGBW_ParamBlockSize 13
#define DIM_ParamBlockOffset 70
#define DIM_ParamBlockSize 4
#define RGB_ParamBlockOffset 74
#define RGB_ParamBlockSize 13
#define CCT_ParamBlockOffset 87
#define CCT_ParamBlockSize 10
#define RGBCCT_KoOffset 2
#define RGBCCT_KoBlockSize 107
#define RGBW_KoOffset 20
#define RGBW_KoBlockSize 107
#define DIM_KoOffset 40
#define DIM_KoBlockSize 102
#define RGB_KoOffset 20
#define RGB_KoBlockSize 107
#define CCT_KoOffset 40
#define CCT_KoBlockSize 103

//-----Module: RGBCCT
#define RGBCCT_CH{{argChan}}_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGBCCT_CH{{argChan}}_Active knx.paramBit((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_Active), 0)
#define RGBCCT_CH{{argChan}}_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGBCCT_CH{{argChan}}_DimSpeed ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_DimSpeed)))))
#define RGBCCT_CH{{argChan}}_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGBCCT_CH{{argChan}}_BrightnessDay ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_BrightnessDay)))))
#define RGBCCT_CH{{argChan}}_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGBCCT_CH{{argChan}}_BrightnessNight ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_BrightnessNight)))))
#define RGBCCT_CH{{argChan}}_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGBCCT_CH{{argChan}}_DefaultColorTemp ((uint32_t)((knx.paramWord((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_DefaultColorTemp)))))
#define RGBCCT_CH{{argChan}}_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGBCCT_CH{{argChan}}_MinColorTemp ((uint32_t)((knx.paramWord((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_MinColorTemp)))))
#define RGBCCT_CH{{argChan}}_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGBCCT_CH{{argChan}}_MaxColorTemp ((uint32_t)((knx.paramWord((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_MaxColorTemp)))))
#define RGBCCT_CH{{argChan}}_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGBCCT_CH{{argChan}}_DefaultColor knx.paramData((RGBCCT_ParamBlockOffset + RGBCCT_CH{{argChan}}_DefaultColor))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define RGBCCT_KoCH{{argChan}}_Switch 0
#define KoRGBCCT_CH{{argChan}}_SwitchIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_Switch + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_Switch knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_Switch + RGBCCT_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define RGBCCT_KoCH{{argChan}}_BrightnessAbsolute 1
#define KoRGBCCT_CH{{argChan}}_BrightnessAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_BrightnessAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_BrightnessAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_BrightnessAbsolute + RGBCCT_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define RGBCCT_KoCH{{argChan}}_BrightnessRelative 2
#define KoRGBCCT_CH{{argChan}}_BrightnessRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_BrightnessRelative + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_BrightnessRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_BrightnessRelative + RGBCCT_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define RGBCCT_KoCH{{argChan}}_ColorTempAbsolute 3
#define KoRGBCCT_CH{{argChan}}_ColorTempAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_ColorTempAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_ColorTempAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_ColorTempAbsolute + RGBCCT_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define RGBCCT_KoCH{{argChan}}_ColorTempRelative 4
#define KoRGBCCT_CH{{argChan}}_ColorTempRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_ColorTempRelative + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_ColorTempRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_ColorTempRelative + RGBCCT_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define RGBCCT_KoCH{{argChan}}_SaturationAbsolute 5
#define KoRGBCCT_CH{{argChan}}_SaturationAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_SaturationAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_SaturationAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_SaturationAbsolute + RGBCCT_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define RGBCCT_KoCH{{argChan}}_SaturationRelative 6
#define KoRGBCCT_CH{{argChan}}_SaturationRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_SaturationRelative + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_SaturationRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_SaturationRelative + RGBCCT_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define RGBCCT_KoCH{{argChan}}_HueAbsolute 7
#define KoRGBCCT_CH{{argChan}}_HueAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_HueAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_HueAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_HueAbsolute + RGBCCT_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define RGBCCT_KoCH{{argChan}}_HueRelative 8
#define KoRGBCCT_CH{{argChan}}_HueRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_HueRelative + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_HueRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_HueRelative + RGBCCT_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define RGBCCT_KoCH{{argChan}}_ColorRGB 9
#define KoRGBCCT_CH{{argChan}}_ColorRGBIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_ColorRGB + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_ColorRGB knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_ColorRGB + RGBCCT_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define RGBCCT_KoCH{{argChan}}_ColorHSV 10
#define KoRGBCCT_CH{{argChan}}_ColorHSVIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_ColorHSV + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_ColorHSV knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_ColorHSV + RGBCCT_KoOffset)
//!< Number: 100, Text: Kanal {{argChan}} (Status), Function: Status
#define RGBCCT_KoCH{{argChan}}_Status 100
#define KoRGBCCT_CH{{argChan}}_StatusIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_Status + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_Status knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_Status + RGBCCT_KoOffset)
//!< Number: 101, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define RGBCCT_KoCH{{argChan}}_StatusBrightness 101
#define KoRGBCCT_CH{{argChan}}_StatusBrightnessIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_StatusBrightness + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_StatusBrightness knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_StatusBrightness + RGBCCT_KoOffset)
//!< Number: 102, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define RGBCCT_KoCH{{argChan}}_StatusColorTemp 102
#define KoRGBCCT_CH{{argChan}}_StatusColorTempIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_StatusColorTemp + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_StatusColorTemp knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_StatusColorTemp + RGBCCT_KoOffset)
//!< Number: 103, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define RGBCCT_KoCH{{argChan}}_StatusSaturation 103
#define KoRGBCCT_CH{{argChan}}_StatusSaturationIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_StatusSaturation + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_StatusSaturation knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_StatusSaturation + RGBCCT_KoOffset)
//!< Number: 104, Text: Kanal {{argChan}} (Status), Function: Farbton
#define RGBCCT_KoCH{{argChan}}_StatusHue 104
#define KoRGBCCT_CH{{argChan}}_StatusHueIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_StatusHue + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_StatusHue knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_StatusHue + RGBCCT_KoOffset)
//!< Number: 105, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define RGBCCT_KoCH{{argChan}}_StatusRGB 105
#define KoRGBCCT_CH{{argChan}}_StatusRGBIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_StatusRGB + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_StatusRGB knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_StatusRGB + RGBCCT_KoOffset)
//!< Number: 106, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define RGBCCT_KoCH{{argChan}}_StatusHSV 106
#define KoRGBCCT_CH{{argChan}}_StatusHSVIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoCH{{argChan}}_StatusHSV + RGBCCT_KoOffset)
#define KoRGBCCT_CH{{argChan}}_StatusHSV knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoCH{{argChan}}_StatusHSV + RGBCCT_KoOffset)

//-----Module: RGBW
#define RGBW_CH{{argChan}}_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGBW_CH{{argChan}}_Active knx.paramBit((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_Active), 0)
#define RGBW_CH{{argChan}}_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGBW_CH{{argChan}}_DimSpeed ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_DimSpeed)))))
#define RGBW_CH{{argChan}}_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGBW_CH{{argChan}}_BrightnessDay ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_BrightnessDay)))))
#define RGBW_CH{{argChan}}_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGBW_CH{{argChan}}_BrightnessNight ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_BrightnessNight)))))
#define RGBW_CH{{argChan}}_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGBW_CH{{argChan}}_DefaultColorTemp ((uint32_t)((knx.paramWord((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_DefaultColorTemp)))))
#define RGBW_CH{{argChan}}_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGBW_CH{{argChan}}_MinColorTemp ((uint32_t)((knx.paramWord((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_MinColorTemp)))))
#define RGBW_CH{{argChan}}_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGBW_CH{{argChan}}_MaxColorTemp ((uint32_t)((knx.paramWord((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_MaxColorTemp)))))
#define RGBW_CH{{argChan}}_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGBW_CH{{argChan}}_DefaultColor knx.paramData((RGBW_ParamBlockOffset + RGBW_CH{{argChan}}_DefaultColor))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define RGBW_KoCH{{argChan}}_Switch 0
#define KoRGBW_CH{{argChan}}_SwitchIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_Switch + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_Switch knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_Switch + RGBW_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define RGBW_KoCH{{argChan}}_BrightnessAbsolute 1
#define KoRGBW_CH{{argChan}}_BrightnessAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_BrightnessAbsolute + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_BrightnessAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_BrightnessAbsolute + RGBW_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define RGBW_KoCH{{argChan}}_BrightnessRelative 2
#define KoRGBW_CH{{argChan}}_BrightnessRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_BrightnessRelative + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_BrightnessRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_BrightnessRelative + RGBW_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define RGBW_KoCH{{argChan}}_ColorTempAbsolute 3
#define KoRGBW_CH{{argChan}}_ColorTempAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_ColorTempAbsolute + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_ColorTempAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_ColorTempAbsolute + RGBW_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define RGBW_KoCH{{argChan}}_ColorTempRelative 4
#define KoRGBW_CH{{argChan}}_ColorTempRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_ColorTempRelative + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_ColorTempRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_ColorTempRelative + RGBW_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define RGBW_KoCH{{argChan}}_SaturationAbsolute 5
#define KoRGBW_CH{{argChan}}_SaturationAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_SaturationAbsolute + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_SaturationAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_SaturationAbsolute + RGBW_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define RGBW_KoCH{{argChan}}_SaturationRelative 6
#define KoRGBW_CH{{argChan}}_SaturationRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_SaturationRelative + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_SaturationRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_SaturationRelative + RGBW_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define RGBW_KoCH{{argChan}}_HueAbsolute 7
#define KoRGBW_CH{{argChan}}_HueAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_HueAbsolute + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_HueAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_HueAbsolute + RGBW_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define RGBW_KoCH{{argChan}}_HueRelative 8
#define KoRGBW_CH{{argChan}}_HueRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_HueRelative + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_HueRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_HueRelative + RGBW_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define RGBW_KoCH{{argChan}}_ColorRGB 9
#define KoRGBW_CH{{argChan}}_ColorRGBIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_ColorRGB + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_ColorRGB knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_ColorRGB + RGBW_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define RGBW_KoCH{{argChan}}_ColorHSV 10
#define KoRGBW_CH{{argChan}}_ColorHSVIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_ColorHSV + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_ColorHSV knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_ColorHSV + RGBW_KoOffset)
//!< Number: 100, Text: Kanal {{argChan}} (Status), Function: Status
#define RGBW_KoCH{{argChan}}_Status 100
#define KoRGBW_CH{{argChan}}_StatusIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_Status + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_Status knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_Status + RGBW_KoOffset)
//!< Number: 101, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define RGBW_KoCH{{argChan}}_StatusBrightness 101
#define KoRGBW_CH{{argChan}}_StatusBrightnessIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_StatusBrightness + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_StatusBrightness knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_StatusBrightness + RGBW_KoOffset)
//!< Number: 102, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define RGBW_KoCH{{argChan}}_StatusColorTemp 102
#define KoRGBW_CH{{argChan}}_StatusColorTempIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_StatusColorTemp + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_StatusColorTemp knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_StatusColorTemp + RGBW_KoOffset)
//!< Number: 103, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define RGBW_KoCH{{argChan}}_StatusSaturation 103
#define KoRGBW_CH{{argChan}}_StatusSaturationIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_StatusSaturation + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_StatusSaturation knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_StatusSaturation + RGBW_KoOffset)
//!< Number: 104, Text: Kanal {{argChan}} (Status), Function: Farbton
#define RGBW_KoCH{{argChan}}_StatusHue 104
#define KoRGBW_CH{{argChan}}_StatusHueIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_StatusHue + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_StatusHue knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_StatusHue + RGBW_KoOffset)
//!< Number: 105, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define RGBW_KoCH{{argChan}}_StatusRGB 105
#define KoRGBW_CH{{argChan}}_StatusRGBIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_StatusRGB + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_StatusRGB knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_StatusRGB + RGBW_KoOffset)
//!< Number: 106, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define RGBW_KoCH{{argChan}}_StatusHSV 106
#define KoRGBW_CH{{argChan}}_StatusHSVIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoCH{{argChan}}_StatusHSV + RGBW_KoOffset)
#define KoRGBW_CH{{argChan}}_StatusHSV knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoCH{{argChan}}_StatusHSV + RGBW_KoOffset)

//-----Module: RGB
#define RGB_CH{{argChan}}_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGB_CH{{argChan}}_ActiveIndex(X) knx.paramBit((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGB_CH{{argChan}}_Active knx.paramBit((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_Active), 0)
#define RGB_CH{{argChan}}_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGB_CH{{argChan}}_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGB_CH{{argChan}}_DimSpeed ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_DimSpeed)))))
#define RGB_CH{{argChan}}_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGB_CH{{argChan}}_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGB_CH{{argChan}}_BrightnessDay ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_BrightnessDay)))))
#define RGB_CH{{argChan}}_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGB_CH{{argChan}}_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGB_CH{{argChan}}_BrightnessNight ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_BrightnessNight)))))
#define RGB_CH{{argChan}}_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGB_CH{{argChan}}_DefaultColorTempIndex(X) ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_DefaultColorTemp)))))
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGB_CH{{argChan}}_DefaultColorTemp ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_DefaultColorTemp)))))
#define RGB_CH{{argChan}}_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGB_CH{{argChan}}_MinColorTempIndex(X) ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_MinColorTemp)))))
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGB_CH{{argChan}}_MinColorTemp ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_MinColorTemp)))))
#define RGB_CH{{argChan}}_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGB_CH{{argChan}}_MaxColorTempIndex(X) ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_MaxColorTemp)))))
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGB_CH{{argChan}}_MaxColorTemp ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_MaxColorTemp)))))
#define RGB_CH{{argChan}}_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGB_CH{{argChan}}_DefaultColorIndex(X) knx.paramData((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_CH{{argChan}}_DefaultColor))
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGB_CH{{argChan}}_DefaultColor knx.paramData((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_CH{{argChan}}_DefaultColor))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define RGB_KoCH{{argChan}}_Switch 0
#define KoRGB_CH{{argChan}}_SwitchIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_Switch + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_Switch knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_Switch + RGB_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define RGB_KoCH{{argChan}}_BrightnessAbsolute 1
#define KoRGB_CH{{argChan}}_BrightnessAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_BrightnessAbsolute + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_BrightnessAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_BrightnessAbsolute + RGB_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define RGB_KoCH{{argChan}}_BrightnessRelative 2
#define KoRGB_CH{{argChan}}_BrightnessRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_BrightnessRelative + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_BrightnessRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_BrightnessRelative + RGB_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define RGB_KoCH{{argChan}}_ColorTempAbsolute 3
#define KoRGB_CH{{argChan}}_ColorTempAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_ColorTempAbsolute + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_ColorTempAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_ColorTempAbsolute + RGB_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define RGB_KoCH{{argChan}}_ColorTempRelative 4
#define KoRGB_CH{{argChan}}_ColorTempRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_ColorTempRelative + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_ColorTempRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_ColorTempRelative + RGB_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define RGB_KoCH{{argChan}}_SaturationAbsolute 5
#define KoRGB_CH{{argChan}}_SaturationAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_SaturationAbsolute + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_SaturationAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_SaturationAbsolute + RGB_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define RGB_KoCH{{argChan}}_SaturationRelative 6
#define KoRGB_CH{{argChan}}_SaturationRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_SaturationRelative + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_SaturationRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_SaturationRelative + RGB_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define RGB_KoCH{{argChan}}_HueAbsolute 7
#define KoRGB_CH{{argChan}}_HueAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_HueAbsolute + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_HueAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_HueAbsolute + RGB_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define RGB_KoCH{{argChan}}_HueRelative 8
#define KoRGB_CH{{argChan}}_HueRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_HueRelative + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_HueRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_HueRelative + RGB_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define RGB_KoCH{{argChan}}_ColorRGB 9
#define KoRGB_CH{{argChan}}_ColorRGBIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_ColorRGB + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_ColorRGB knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_ColorRGB + RGB_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define RGB_KoCH{{argChan}}_ColorHSV 10
#define KoRGB_CH{{argChan}}_ColorHSVIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_ColorHSV + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_ColorHSV knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_ColorHSV + RGB_KoOffset)
//!< Number: 100, Text: Kanal {{argChan}} (Status), Function: Status
#define RGB_KoCH{{argChan}}_Status 100
#define KoRGB_CH{{argChan}}_StatusIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_Status + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_Status knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_Status + RGB_KoOffset)
//!< Number: 101, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define RGB_KoCH{{argChan}}_StatusBrightness 101
#define KoRGB_CH{{argChan}}_StatusBrightnessIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_StatusBrightness + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_StatusBrightness knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_StatusBrightness + RGB_KoOffset)
//!< Number: 102, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define RGB_KoCH{{argChan}}_StatusColorTemp 102
#define KoRGB_CH{{argChan}}_StatusColorTempIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_StatusColorTemp + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_StatusColorTemp knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_StatusColorTemp + RGB_KoOffset)
//!< Number: 103, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define RGB_KoCH{{argChan}}_StatusSaturation 103
#define KoRGB_CH{{argChan}}_StatusSaturationIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_StatusSaturation + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_StatusSaturation knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_StatusSaturation + RGB_KoOffset)
//!< Number: 104, Text: Kanal {{argChan}} (Status), Function: Farbton
#define RGB_KoCH{{argChan}}_StatusHue 104
#define KoRGB_CH{{argChan}}_StatusHueIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_StatusHue + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_StatusHue knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_StatusHue + RGB_KoOffset)
//!< Number: 105, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define RGB_KoCH{{argChan}}_StatusRGB 105
#define KoRGB_CH{{argChan}}_StatusRGBIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_StatusRGB + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_StatusRGB knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_StatusRGB + RGB_KoOffset)
//!< Number: 106, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define RGB_KoCH{{argChan}}_StatusHSV 106
#define KoRGB_CH{{argChan}}_StatusHSVIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoCH{{argChan}}_StatusHSV + RGB_KoOffset)
#define KoRGB_CH{{argChan}}_StatusHSV knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoCH{{argChan}}_StatusHSV + RGB_KoOffset)

//-----Module: CCT
#define CCT_CH{{argChan}}_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamCCT_CH{{argChan}}_ActiveIndex(X) knx.paramBit((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamCCT_CH{{argChan}}_Active knx.paramBit((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_Active), 0)
#define CCT_CH{{argChan}}_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamCCT_CH{{argChan}}_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamCCT_CH{{argChan}}_DimSpeed ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_DimSpeed)))))
#define CCT_CH{{argChan}}_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamCCT_CH{{argChan}}_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamCCT_CH{{argChan}}_BrightnessDay ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_BrightnessDay)))))
#define CCT_CH{{argChan}}_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamCCT_CH{{argChan}}_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamCCT_CH{{argChan}}_BrightnessNight ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_BrightnessNight)))))
#define CCT_CH{{argChan}}_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamCCT_CH{{argChan}}_DefaultColorTempIndex(X) ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_DefaultColorTemp)))))
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamCCT_CH{{argChan}}_DefaultColorTemp ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_DefaultColorTemp)))))
#define CCT_CH{{argChan}}_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamCCT_CH{{argChan}}_MinColorTempIndex(X) ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_MinColorTemp)))))
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamCCT_CH{{argChan}}_MinColorTemp ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_MinColorTemp)))))
#define CCT_CH{{argChan}}_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamCCT_CH{{argChan}}_MaxColorTempIndex(X) ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_CH{{argChan}}_MaxColorTemp)))))
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamCCT_CH{{argChan}}_MaxColorTemp ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_CH{{argChan}}_MaxColorTemp)))))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define CCT_KoCH{{argChan}}_Switch 0
#define KoCCT_CH{{argChan}}_SwitchIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_Switch + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_Switch knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_Switch + CCT_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define CCT_KoCH{{argChan}}_BrightnessAbsolute 1
#define KoCCT_CH{{argChan}}_BrightnessAbsoluteIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_BrightnessAbsolute + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_BrightnessAbsolute knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_BrightnessAbsolute + CCT_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define CCT_KoCH{{argChan}}_BrightnessRelative 2
#define KoCCT_CH{{argChan}}_BrightnessRelativeIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_BrightnessRelative + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_BrightnessRelative knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_BrightnessRelative + CCT_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define CCT_KoCH{{argChan}}_ColorTempAbsolute 3
#define KoCCT_CH{{argChan}}_ColorTempAbsoluteIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_ColorTempAbsolute + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_ColorTempAbsolute knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_ColorTempAbsolute + CCT_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (relative)
#define CCT_KoCH{{argChan}}_ColorTempRelative 3
#define KoCCT_CH{{argChan}}_ColorTempRelativeIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_ColorTempRelative + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_ColorTempRelative knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_ColorTempRelative + CCT_KoOffset)
//!< Number: 100, Text: Kanal {{argChan}} (Status), Function: Status
#define CCT_KoCH{{argChan}}_Status 100
#define KoCCT_CH{{argChan}}_StatusIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_Status + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_Status knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_Status + CCT_KoOffset)
//!< Number: 101, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define CCT_KoCH{{argChan}}_StatusBrightness 101
#define KoCCT_CH{{argChan}}_StatusBrightnessIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_StatusBrightness + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_StatusBrightness knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_StatusBrightness + CCT_KoOffset)
//!< Number: 102, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define CCT_KoCH{{argChan}}_StatusColorTemp 102
#define KoCCT_CH{{argChan}}_StatusColorTempIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoCH{{argChan}}_StatusColorTemp + CCT_KoOffset)
#define KoCCT_CH{{argChan}}_StatusColorTemp knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoCH{{argChan}}_StatusColorTemp + CCT_KoOffset)

//-----Module: DIM
#define DIM_CH{{argChan}}_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamDIM_CH{{argChan}}_ActiveIndex(X) knx.paramBit((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_CH{{argChan}}_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamDIM_CH{{argChan}}_Active knx.paramBit((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_CH{{argChan}}_Active), 0)
#define DIM_CH{{argChan}}_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamDIM_CH{{argChan}}_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_CH{{argChan}}_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamDIM_CH{{argChan}}_DimSpeed ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_CH{{argChan}}_DimSpeed)))))
#define DIM_CH{{argChan}}_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamDIM_CH{{argChan}}_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_CH{{argChan}}_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamDIM_CH{{argChan}}_BrightnessDay ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_CH{{argChan}}_BrightnessDay)))))
#define DIM_CH{{argChan}}_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Night
#define ParamDIM_CH{{argChan}}_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_CH{{argChan}}_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Night
#define ParamDIM_CH{{argChan}}_BrightnessNight ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_CH{{argChan}}_BrightnessNight)))))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define DIM_KoCH{{argChan}}_Switch 0
#define KoDIM_CH{{argChan}}_SwitchIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoCH{{argChan}}_Switch + DIM_KoOffset)
#define KoDIM_CH{{argChan}}_Switch knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoCH{{argChan}}_Switch + DIM_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define DIM_KoCH{{argChan}}_BrightnessAbsolute 1
#define KoDIM_CH{{argChan}}_BrightnessAbsoluteIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoCH{{argChan}}_BrightnessAbsolute + DIM_KoOffset)
#define KoDIM_CH{{argChan}}_BrightnessAbsolute knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoCH{{argChan}}_BrightnessAbsolute + DIM_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define DIM_KoCH{{argChan}}_BrightnessRelative 2
#define KoDIM_CH{{argChan}}_BrightnessRelativeIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoCH{{argChan}}_BrightnessRelative + DIM_KoOffset)
#define KoDIM_CH{{argChan}}_BrightnessRelative knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoCH{{argChan}}_BrightnessRelative + DIM_KoOffset)
//!< Number: 100, Text: Kanal {{argChan}} (Status), Function: Status
#define DIM_KoCH{{argChan}}_Status 100
#define KoDIM_CH{{argChan}}_StatusIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoCH{{argChan}}_Status + DIM_KoOffset)
#define KoDIM_CH{{argChan}}_Status knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoCH{{argChan}}_Status + DIM_KoOffset)
//!< Number: 101, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define DIM_KoCH{{argChan}}_StatusBrightness 101
#define KoDIM_CH{{argChan}}_StatusBrightnessIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoCH{{argChan}}_StatusBrightness + DIM_KoOffset)
#define KoDIM_CH{{argChan}}_StatusBrightness knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoCH{{argChan}}_StatusBrightness + DIM_KoOffset)

