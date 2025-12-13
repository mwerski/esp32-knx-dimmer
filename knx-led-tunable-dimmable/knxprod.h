#pragma once

#define paramDelay(time) (uint32_t)( \
            (time & 0xC000) == 0xC000 ? (time & 0x3FFF) * 100 : \
            (time & 0xC000) == 0x0000 ? (time & 0x3FFF) * 1000 : \
            (time & 0xC000) == 0x4000 ? (time & 0x3FFF) * 60000 : \
            (time & 0xC000) == 0x8000 ? ((time & 0x3FFF) > 1000 ? 3600000 : \
                                            (time & 0x3FFF) * 3600000 ) : 0 )
#define PT_OnOff_Aus 0
#define PT_OnOff_Ein 1
#define PT_ChannelModes_RGBCCT 0
#define PT_ChannelModes_RGBW_D 1
#define PT_ChannelModes_RGB_CCT 2
#define PT_ChannelModes_RGB_D_D 3
#define PT_ChannelModes_CCT_CCT_D 4
#define PT_ChannelModes_CCT_D_D_D 5
#define PT_ChannelModes_D_D_D_D_D 6
#define PT_lightType_none 0
#define PT_lightType_RGBCCT 1
#define PT_lightType_RGBW 2
#define PT_lightType_RGB 3
#define PT_lightType_TUNEABLE 4
#define PT_lightType_DIMMABLE 5
//--------------------Allgemein---------------------------
#define MAIN_OpenKnxId 0xAF
#define MAIN_ApplicationNumber 0x00
#define MAIN_ApplicationVersion 0x02
#define MAIN_OrderNumber "DOM-WLE-ACLE"
#define MAIN_ParameterSize 184
#define MAIN_MaxKoNumber 1


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
//!< Number: 0, Text: Zentral, Function: Tag/Nacht
#define APP_KoGeneralDayNight 0
#define KoAPP_GeneralDayNight knx.getGroupObject(APP_KoGeneralDayNight)
//!< Number: 1, Text: Zentral, Function: In Betrieb
#define APP_KoHeartbeat 1
#define KoAPP_Heartbeat knx.getGroupObject(APP_KoHeartbeat)

//---------------------Modules----------------------------

//-----Module specific starts
#define RGBCCT_ParamBlockOffset 87
#define RGBCCT_ParamBlockSize 13
#define RGBW_ParamBlockOffset 100
#define RGBW_ParamBlockSize 13
#define DIM_ParamBlockOffset 113
#define DIM_ParamBlockSize 4
#define RGB_ParamBlockOffset 117
#define RGB_ParamBlockSize 13
#define CCT_ParamBlockOffset 130
#define CCT_ParamBlockSize 10
#define RGBCCT_KoOffset 20
#define RGBCCT_KoBlockSize 27
#define RGBW_KoOffset 20
#define RGBW_KoBlockSize 27
#define DIM_KoOffset 60
#define DIM_KoBlockSize 22
#define RGB_KoOffset 20
#define RGB_KoBlockSize 27
#define CCT_KoOffset 60
#define CCT_KoBlockSize 23

//-----Module: RGBCCT
#define RGBCCT_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGBCCT_Active knx.paramBit((RGBCCT_ParamBlockOffset + RGBCCT_Active), 0)
#define RGBCCT_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGBCCT_DimSpeed ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_DimSpeed)))))
#define RGBCCT_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGBCCT_BrightnessDay ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_BrightnessDay)))))
#define RGBCCT_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGBCCT_BrightnessNight ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_BrightnessNight)))))
#define RGBCCT_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGBCCT_DefaultColorTemp ((uint32_t)((knx.paramWord((RGBCCT_ParamBlockOffset + RGBCCT_DefaultColorTemp)))))
#define RGBCCT_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGBCCT_MinColorTemp ((uint32_t)((knx.paramWord((RGBCCT_ParamBlockOffset + RGBCCT_MinColorTemp)))))
#define RGBCCT_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGBCCT_MaxColorTemp ((uint32_t)((knx.paramWord((RGBCCT_ParamBlockOffset + RGBCCT_MaxColorTemp)))))
#define RGBCCT_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGBCCT_DefaultColor knx.paramData((RGBCCT_ParamBlockOffset + RGBCCT_DefaultColor))
#define RGBCCT_Type		0x0000
#define RGBCCT_Type_Shift	4
#define RGBCCT_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamRGBCCT_Type ((uint32_t)((knx.paramByte((RGBCCT_ParamBlockOffset + RGBCCT_Type)) >> RGBCCT_Type_Shift) & RGBCCT_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define RGBCCT_KoSwitch 0
#define KoRGBCCT_SwitchIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoSwitch + RGBCCT_KoOffset)
#define KoRGBCCT_Switch knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoSwitch + RGBCCT_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define RGBCCT_KoBrightnessAbsolute 1
#define KoRGBCCT_BrightnessAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoBrightnessAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_BrightnessAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoBrightnessAbsolute + RGBCCT_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define RGBCCT_KoBrightnessRelative 2
#define KoRGBCCT_BrightnessRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoBrightnessRelative + RGBCCT_KoOffset)
#define KoRGBCCT_BrightnessRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoBrightnessRelative + RGBCCT_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define RGBCCT_KoColorTempAbsolute 3
#define KoRGBCCT_ColorTempAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoColorTempAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_ColorTempAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoColorTempAbsolute + RGBCCT_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define RGBCCT_KoColorTempRelative 4
#define KoRGBCCT_ColorTempRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoColorTempRelative + RGBCCT_KoOffset)
#define KoRGBCCT_ColorTempRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoColorTempRelative + RGBCCT_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define RGBCCT_KoSaturationAbsolute 5
#define KoRGBCCT_SaturationAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoSaturationAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_SaturationAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoSaturationAbsolute + RGBCCT_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define RGBCCT_KoSaturationRelative 6
#define KoRGBCCT_SaturationRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoSaturationRelative + RGBCCT_KoOffset)
#define KoRGBCCT_SaturationRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoSaturationRelative + RGBCCT_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define RGBCCT_KoHueAbsolute 7
#define KoRGBCCT_HueAbsoluteIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoHueAbsolute + RGBCCT_KoOffset)
#define KoRGBCCT_HueAbsolute knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoHueAbsolute + RGBCCT_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define RGBCCT_KoHueRelative 8
#define KoRGBCCT_HueRelativeIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoHueRelative + RGBCCT_KoOffset)
#define KoRGBCCT_HueRelative knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoHueRelative + RGBCCT_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define RGBCCT_KoColorRGB 9
#define KoRGBCCT_ColorRGBIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoColorRGB + RGBCCT_KoOffset)
#define KoRGBCCT_ColorRGB knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoColorRGB + RGBCCT_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define RGBCCT_KoColorHSV 10
#define KoRGBCCT_ColorHSVIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoColorHSV + RGBCCT_KoOffset)
#define KoRGBCCT_ColorHSV knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoColorHSV + RGBCCT_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define RGBCCT_KoStatus 20
#define KoRGBCCT_StatusIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatus + RGBCCT_KoOffset)
#define KoRGBCCT_Status knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatus + RGBCCT_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define RGBCCT_KoStatusBrightness 21
#define KoRGBCCT_StatusBrightnessIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatusBrightness + RGBCCT_KoOffset)
#define KoRGBCCT_StatusBrightness knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatusBrightness + RGBCCT_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define RGBCCT_KoStatusColorTemp 22
#define KoRGBCCT_StatusColorTempIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatusColorTemp + RGBCCT_KoOffset)
#define KoRGBCCT_StatusColorTemp knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatusColorTemp + RGBCCT_KoOffset)
//!< Number: 23, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define RGBCCT_KoStatusSaturation 23
#define KoRGBCCT_StatusSaturationIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatusSaturation + RGBCCT_KoOffset)
#define KoRGBCCT_StatusSaturation knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatusSaturation + RGBCCT_KoOffset)
//!< Number: 24, Text: Kanal {{argChan}} (Status), Function: Farbton
#define RGBCCT_KoStatusHue 24
#define KoRGBCCT_StatusHueIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatusHue + RGBCCT_KoOffset)
#define KoRGBCCT_StatusHue knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatusHue + RGBCCT_KoOffset)
//!< Number: 25, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define RGBCCT_KoStatusRGB 25
#define KoRGBCCT_StatusRGBIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatusRGB + RGBCCT_KoOffset)
#define KoRGBCCT_StatusRGB knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatusRGB + RGBCCT_KoOffset)
//!< Number: 26, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define RGBCCT_KoStatusHSV 26
#define KoRGBCCT_StatusHSVIndex(X) knx.getGroupObject(RGBCCT_KoBlockSize * X + RGBCCT_KoStatusHSV + RGBCCT_KoOffset)
#define KoRGBCCT_StatusHSV knx.getGroupObject(RGBCCT_KoBlockSize * channelIndex() + RGBCCT_KoStatusHSV + RGBCCT_KoOffset)

//-----Module: RGBW
#define RGBW_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGBW_Active knx.paramBit((RGBW_ParamBlockOffset + RGBW_Active), 0)
#define RGBW_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGBW_DimSpeed ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_DimSpeed)))))
#define RGBW_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGBW_BrightnessDay ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_BrightnessDay)))))
#define RGBW_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGBW_BrightnessNight ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_BrightnessNight)))))
#define RGBW_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGBW_DefaultColorTemp ((uint32_t)((knx.paramWord((RGBW_ParamBlockOffset + RGBW_DefaultColorTemp)))))
#define RGBW_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGBW_MinColorTemp ((uint32_t)((knx.paramWord((RGBW_ParamBlockOffset + RGBW_MinColorTemp)))))
#define RGBW_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGBW_MaxColorTemp ((uint32_t)((knx.paramWord((RGBW_ParamBlockOffset + RGBW_MaxColorTemp)))))
#define RGBW_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGBW_DefaultColor knx.paramData((RGBW_ParamBlockOffset + RGBW_DefaultColor))
#define RGBW_Type		0x0000
#define RGBW_Type_Shift	4
#define RGBW_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamRGBW_Type ((uint32_t)((knx.paramByte((RGBW_ParamBlockOffset + RGBW_Type)) >> RGBW_Type_Shift) & RGBW_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define RGBW_KoSwitch 0
#define KoRGBW_SwitchIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoSwitch + RGBW_KoOffset)
#define KoRGBW_Switch knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoSwitch + RGBW_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define RGBW_KoBrightnessAbsolute 1
#define KoRGBW_BrightnessAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoBrightnessAbsolute + RGBW_KoOffset)
#define KoRGBW_BrightnessAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoBrightnessAbsolute + RGBW_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define RGBW_KoBrightnessRelative 2
#define KoRGBW_BrightnessRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoBrightnessRelative + RGBW_KoOffset)
#define KoRGBW_BrightnessRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoBrightnessRelative + RGBW_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define RGBW_KoColorTempAbsolute 3
#define KoRGBW_ColorTempAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoColorTempAbsolute + RGBW_KoOffset)
#define KoRGBW_ColorTempAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoColorTempAbsolute + RGBW_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define RGBW_KoColorTempRelative 4
#define KoRGBW_ColorTempRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoColorTempRelative + RGBW_KoOffset)
#define KoRGBW_ColorTempRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoColorTempRelative + RGBW_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define RGBW_KoSaturationAbsolute 5
#define KoRGBW_SaturationAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoSaturationAbsolute + RGBW_KoOffset)
#define KoRGBW_SaturationAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoSaturationAbsolute + RGBW_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define RGBW_KoSaturationRelative 6
#define KoRGBW_SaturationRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoSaturationRelative + RGBW_KoOffset)
#define KoRGBW_SaturationRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoSaturationRelative + RGBW_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define RGBW_KoHueAbsolute 7
#define KoRGBW_HueAbsoluteIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoHueAbsolute + RGBW_KoOffset)
#define KoRGBW_HueAbsolute knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoHueAbsolute + RGBW_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define RGBW_KoHueRelative 8
#define KoRGBW_HueRelativeIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoHueRelative + RGBW_KoOffset)
#define KoRGBW_HueRelative knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoHueRelative + RGBW_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define RGBW_KoColorRGB 9
#define KoRGBW_ColorRGBIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoColorRGB + RGBW_KoOffset)
#define KoRGBW_ColorRGB knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoColorRGB + RGBW_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define RGBW_KoColorHSV 10
#define KoRGBW_ColorHSVIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoColorHSV + RGBW_KoOffset)
#define KoRGBW_ColorHSV knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoColorHSV + RGBW_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define RGBW_KoStatus 20
#define KoRGBW_StatusIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatus + RGBW_KoOffset)
#define KoRGBW_Status knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatus + RGBW_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define RGBW_KoStatusBrightness 21
#define KoRGBW_StatusBrightnessIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatusBrightness + RGBW_KoOffset)
#define KoRGBW_StatusBrightness knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatusBrightness + RGBW_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define RGBW_KoStatusColorTemp 22
#define KoRGBW_StatusColorTempIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatusColorTemp + RGBW_KoOffset)
#define KoRGBW_StatusColorTemp knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatusColorTemp + RGBW_KoOffset)
//!< Number: 23, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define RGBW_KoStatusSaturation 23
#define KoRGBW_StatusSaturationIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatusSaturation + RGBW_KoOffset)
#define KoRGBW_StatusSaturation knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatusSaturation + RGBW_KoOffset)
//!< Number: 24, Text: Kanal {{argChan}} (Status), Function: Farbton
#define RGBW_KoStatusHue 24
#define KoRGBW_StatusHueIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatusHue + RGBW_KoOffset)
#define KoRGBW_StatusHue knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatusHue + RGBW_KoOffset)
//!< Number: 25, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define RGBW_KoStatusRGB 25
#define KoRGBW_StatusRGBIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatusRGB + RGBW_KoOffset)
#define KoRGBW_StatusRGB knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatusRGB + RGBW_KoOffset)
//!< Number: 26, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define RGBW_KoStatusHSV 26
#define KoRGBW_StatusHSVIndex(X) knx.getGroupObject(RGBW_KoBlockSize * X + RGBW_KoStatusHSV + RGBW_KoOffset)
#define KoRGBW_StatusHSV knx.getGroupObject(RGBW_KoBlockSize * channelIndex() + RGBW_KoStatusHSV + RGBW_KoOffset)

//-----Module: RGB
#define RGB_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGB_ActiveIndex(X) knx.paramBit((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamRGB_Active knx.paramBit((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_Active), 0)
#define RGB_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGB_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamRGB_DimSpeed ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_DimSpeed)))))
#define RGB_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGB_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamRGB_BrightnessDay ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_BrightnessDay)))))
#define RGB_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGB_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamRGB_BrightnessNight ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_BrightnessNight)))))
#define RGB_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGB_DefaultColorTempIndex(X) ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_DefaultColorTemp)))))
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamRGB_DefaultColorTemp ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_DefaultColorTemp)))))
#define RGB_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGB_MinColorTempIndex(X) ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_MinColorTemp)))))
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamRGB_MinColorTemp ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_MinColorTemp)))))
#define RGB_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGB_MaxColorTempIndex(X) ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_MaxColorTemp)))))
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamRGB_MaxColorTemp ((uint32_t)((knx.paramWord((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_MaxColorTemp)))))
#define RGB_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGB_DefaultColorIndex(X) knx.paramData((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_DefaultColor))
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamRGB_DefaultColor knx.paramData((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_DefaultColor))
#define RGB_Type		0x0000
#define RGB_Type_Shift	4
#define RGB_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamRGB_TypeIndex(X) ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * X + RGB_Type)) >> RGB_Type_Shift) & RGB_Type_Mask))
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamRGB_Type ((uint32_t)((knx.paramByte((RGB_ParamBlockOffset + RGB_ParamBlockSize * channelIndex() + RGB_Type)) >> RGB_Type_Shift) & RGB_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define RGB_KoSwitch 0
#define KoRGB_SwitchIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoSwitch + RGB_KoOffset)
#define KoRGB_Switch knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoSwitch + RGB_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define RGB_KoBrightnessAbsolute 1
#define KoRGB_BrightnessAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoBrightnessAbsolute + RGB_KoOffset)
#define KoRGB_BrightnessAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoBrightnessAbsolute + RGB_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define RGB_KoBrightnessRelative 2
#define KoRGB_BrightnessRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoBrightnessRelative + RGB_KoOffset)
#define KoRGB_BrightnessRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoBrightnessRelative + RGB_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define RGB_KoColorTempAbsolute 3
#define KoRGB_ColorTempAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoColorTempAbsolute + RGB_KoOffset)
#define KoRGB_ColorTempAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoColorTempAbsolute + RGB_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define RGB_KoColorTempRelative 4
#define KoRGB_ColorTempRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoColorTempRelative + RGB_KoOffset)
#define KoRGB_ColorTempRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoColorTempRelative + RGB_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define RGB_KoSaturationAbsolute 5
#define KoRGB_SaturationAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoSaturationAbsolute + RGB_KoOffset)
#define KoRGB_SaturationAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoSaturationAbsolute + RGB_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define RGB_KoSaturationRelative 6
#define KoRGB_SaturationRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoSaturationRelative + RGB_KoOffset)
#define KoRGB_SaturationRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoSaturationRelative + RGB_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define RGB_KoHueAbsolute 7
#define KoRGB_HueAbsoluteIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoHueAbsolute + RGB_KoOffset)
#define KoRGB_HueAbsolute knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoHueAbsolute + RGB_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define RGB_KoHueRelative 8
#define KoRGB_HueRelativeIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoHueRelative + RGB_KoOffset)
#define KoRGB_HueRelative knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoHueRelative + RGB_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define RGB_KoColorRGB 9
#define KoRGB_ColorRGBIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoColorRGB + RGB_KoOffset)
#define KoRGB_ColorRGB knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoColorRGB + RGB_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define RGB_KoColorHSV 10
#define KoRGB_ColorHSVIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoColorHSV + RGB_KoOffset)
#define KoRGB_ColorHSV knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoColorHSV + RGB_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define RGB_KoStatus 20
#define KoRGB_StatusIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatus + RGB_KoOffset)
#define KoRGB_Status knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatus + RGB_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define RGB_KoStatusBrightness 21
#define KoRGB_StatusBrightnessIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatusBrightness + RGB_KoOffset)
#define KoRGB_StatusBrightness knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatusBrightness + RGB_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define RGB_KoStatusColorTemp 22
#define KoRGB_StatusColorTempIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatusColorTemp + RGB_KoOffset)
#define KoRGB_StatusColorTemp knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatusColorTemp + RGB_KoOffset)
//!< Number: 23, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define RGB_KoStatusSaturation 23
#define KoRGB_StatusSaturationIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatusSaturation + RGB_KoOffset)
#define KoRGB_StatusSaturation knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatusSaturation + RGB_KoOffset)
//!< Number: 24, Text: Kanal {{argChan}} (Status), Function: Farbton
#define RGB_KoStatusHue 24
#define KoRGB_StatusHueIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatusHue + RGB_KoOffset)
#define KoRGB_StatusHue knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatusHue + RGB_KoOffset)
//!< Number: 25, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define RGB_KoStatusRGB 25
#define KoRGB_StatusRGBIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatusRGB + RGB_KoOffset)
#define KoRGB_StatusRGB knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatusRGB + RGB_KoOffset)
//!< Number: 26, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define RGB_KoStatusHSV 26
#define KoRGB_StatusHSVIndex(X) knx.getGroupObject(RGB_KoBlockSize * X + RGB_KoStatusHSV + RGB_KoOffset)
#define KoRGB_StatusHSV knx.getGroupObject(RGB_KoBlockSize * channelIndex() + RGB_KoStatusHSV + RGB_KoOffset)

//-----Module: CCT
#define CCT_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamCCT_ActiveIndex(X) knx.paramBit((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamCCT_Active knx.paramBit((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_Active), 0)
#define CCT_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamCCT_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamCCT_DimSpeed ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_DimSpeed)))))
#define CCT_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamCCT_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamCCT_BrightnessDay ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_BrightnessDay)))))
#define CCT_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamCCT_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamCCT_BrightnessNight ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_BrightnessNight)))))
#define CCT_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamCCT_DefaultColorTempIndex(X) ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_DefaultColorTemp)))))
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamCCT_DefaultColorTemp ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_DefaultColorTemp)))))
#define CCT_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamCCT_MinColorTempIndex(X) ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_MinColorTemp)))))
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamCCT_MinColorTemp ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_MinColorTemp)))))
#define CCT_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamCCT_MaxColorTempIndex(X) ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_MaxColorTemp)))))
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamCCT_MaxColorTemp ((uint32_t)((knx.paramWord((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_MaxColorTemp)))))
#define CCT_Type		0x0000
#define CCT_Type_Shift	4
#define CCT_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamCCT_TypeIndex(X) ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * X + CCT_Type)) >> CCT_Type_Shift) & CCT_Type_Mask))
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamCCT_Type ((uint32_t)((knx.paramByte((CCT_ParamBlockOffset + CCT_ParamBlockSize * channelIndex() + CCT_Type)) >> CCT_Type_Shift) & CCT_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define CCT_KoSwitch 0
#define KoCCT_SwitchIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoSwitch + CCT_KoOffset)
#define KoCCT_Switch knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoSwitch + CCT_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define CCT_KoBrightnessAbsolute 1
#define KoCCT_BrightnessAbsoluteIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoBrightnessAbsolute + CCT_KoOffset)
#define KoCCT_BrightnessAbsolute knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoBrightnessAbsolute + CCT_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define CCT_KoBrightnessRelative 2
#define KoCCT_BrightnessRelativeIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoBrightnessRelative + CCT_KoOffset)
#define KoCCT_BrightnessRelative knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoBrightnessRelative + CCT_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define CCT_KoColorTempAbsolute 3
#define KoCCT_ColorTempAbsoluteIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoColorTempAbsolute + CCT_KoOffset)
#define KoCCT_ColorTempAbsolute knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoColorTempAbsolute + CCT_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (relative)
#define CCT_KoColorTempRelative 3
#define KoCCT_ColorTempRelativeIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoColorTempRelative + CCT_KoOffset)
#define KoCCT_ColorTempRelative knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoColorTempRelative + CCT_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define CCT_KoStatus 20
#define KoCCT_StatusIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoStatus + CCT_KoOffset)
#define KoCCT_Status knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoStatus + CCT_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define CCT_KoStatusBrightness 21
#define KoCCT_StatusBrightnessIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoStatusBrightness + CCT_KoOffset)
#define KoCCT_StatusBrightness knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoStatusBrightness + CCT_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define CCT_KoStatusColorTemp 22
#define KoCCT_StatusColorTempIndex(X) knx.getGroupObject(CCT_KoBlockSize * X + CCT_KoStatusColorTemp + CCT_KoOffset)
#define KoCCT_StatusColorTemp knx.getGroupObject(CCT_KoBlockSize * channelIndex() + CCT_KoStatusColorTemp + CCT_KoOffset)

//-----Module: DIM
#define DIM_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamDIM_ActiveIndex(X) knx.paramBit((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamDIM_Active knx.paramBit((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_Active), 0)
#define DIM_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamDIM_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamDIM_DimSpeed ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_DimSpeed)))))
#define DIM_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamDIM_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamDIM_BrightnessDay ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_BrightnessDay)))))
#define DIM_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Night
#define ParamDIM_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Night
#define ParamDIM_BrightnessNight ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_BrightnessNight)))))
#define DIM_Type		0x0000
#define DIM_Type_Shift	4
#define DIM_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamDIM_TypeIndex(X) ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * X + DIM_Type)) >> DIM_Type_Shift) & DIM_Type_Mask))
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamDIM_Type ((uint32_t)((knx.paramByte((DIM_ParamBlockOffset + DIM_ParamBlockSize * channelIndex() + DIM_Type)) >> DIM_Type_Shift) & DIM_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define DIM_KoSwitch 0
#define KoDIM_SwitchIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoSwitch + DIM_KoOffset)
#define KoDIM_Switch knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoSwitch + DIM_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define DIM_KoBrightnessAbsolute 1
#define KoDIM_BrightnessAbsoluteIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoBrightnessAbsolute + DIM_KoOffset)
#define KoDIM_BrightnessAbsolute knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoBrightnessAbsolute + DIM_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define DIM_KoBrightnessRelative 2
#define KoDIM_BrightnessRelativeIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoBrightnessRelative + DIM_KoOffset)
#define KoDIM_BrightnessRelative knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoBrightnessRelative + DIM_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define DIM_KoStatus 20
#define KoDIM_StatusIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoStatus + DIM_KoOffset)
#define KoDIM_Status knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoStatus + DIM_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define DIM_KoStatusBrightness 21
#define KoDIM_StatusBrightnessIndex(X) knx.getGroupObject(DIM_KoBlockSize * X + DIM_KoStatusBrightness + DIM_KoOffset)
#define KoDIM_StatusBrightness knx.getGroupObject(DIM_KoBlockSize * channelIndex() + DIM_KoStatusBrightness + DIM_KoOffset)

