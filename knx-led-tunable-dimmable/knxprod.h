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
#define MAIN_ApplicationVersion 0x01
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
#define MOD_ParamBlockOffset 44
#define MOD_ParamBlockSize 13
#define MOD_KoOffset 20
#define MOD_KoBlockSize 27

//-----Module: RGBCCT
#define MOD_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_Active knx.paramBit((MOD_ParamBlockOffset + MOD_Active), 0)
#define MOD_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeed ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_DimSpeed)))))
#define MOD_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDay ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_BrightnessDay)))))
#define MOD_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamMOD_BrightnessNight ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_BrightnessNight)))))
#define MOD_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamMOD_DefaultColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_DefaultColorTemp)))))
#define MOD_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamMOD_MinColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_MinColorTemp)))))
#define MOD_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamMOD_MaxColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_MaxColorTemp)))))
#define MOD_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamMOD_DefaultColor knx.paramData((MOD_ParamBlockOffset + MOD_DefaultColor))
#define MOD_Type		0x0000
#define MOD_Type_Shift	4
#define MOD_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_Type ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define MOD_KoSwitch 0
#define KoMOD_SwitchIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSwitch + MOD_KoOffset)
#define KoMOD_Switch knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSwitch + MOD_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define MOD_KoBrightnessAbsolute 1
#define KoMOD_BrightnessAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessAbsolute + MOD_KoOffset)
#define KoMOD_BrightnessAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessAbsolute + MOD_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define MOD_KoBrightnessRelative 2
#define KoMOD_BrightnessRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessRelative + MOD_KoOffset)
#define KoMOD_BrightnessRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessRelative + MOD_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define MOD_KoColorTempAbsolute 3
#define KoMOD_ColorTempAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempAbsolute + MOD_KoOffset)
#define KoMOD_ColorTempAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempAbsolute + MOD_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define MOD_KoColorTempRelative 4
#define KoMOD_ColorTempRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempRelative + MOD_KoOffset)
#define KoMOD_ColorTempRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempRelative + MOD_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define MOD_KoSaturationAbsolute 5
#define KoMOD_SaturationAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSaturationAbsolute + MOD_KoOffset)
#define KoMOD_SaturationAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSaturationAbsolute + MOD_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define MOD_KoSaturationRelative 6
#define KoMOD_SaturationRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSaturationRelative + MOD_KoOffset)
#define KoMOD_SaturationRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSaturationRelative + MOD_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define MOD_KoHueAbsolute 7
#define KoMOD_HueAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoHueAbsolute + MOD_KoOffset)
#define KoMOD_HueAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoHueAbsolute + MOD_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define MOD_KoHueRelative 8
#define KoMOD_HueRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoHueRelative + MOD_KoOffset)
#define KoMOD_HueRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoHueRelative + MOD_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define MOD_KoColorRGB 9
#define KoMOD_ColorRGBIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorRGB + MOD_KoOffset)
#define KoMOD_ColorRGB knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorRGB + MOD_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define MOD_KoColorHSV 10
#define KoMOD_ColorHSVIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorHSV + MOD_KoOffset)
#define KoMOD_ColorHSV knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorHSV + MOD_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define MOD_KoStatus 20
#define KoMOD_StatusIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatus + MOD_KoOffset)
#define KoMOD_Status knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatus + MOD_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define MOD_KoStatusBrightness 21
#define KoMOD_StatusBrightnessIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusBrightness + MOD_KoOffset)
#define KoMOD_StatusBrightness knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusBrightness + MOD_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define MOD_KoStatusColorTemp 22
#define KoMOD_StatusColorTempIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusColorTemp + MOD_KoOffset)
#define KoMOD_StatusColorTemp knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusColorTemp + MOD_KoOffset)
//!< Number: 23, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define MOD_KoStatusSaturation 23
#define KoMOD_StatusSaturationIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusSaturation + MOD_KoOffset)
#define KoMOD_StatusSaturation knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusSaturation + MOD_KoOffset)
//!< Number: 24, Text: Kanal {{argChan}} (Status), Function: Farbton
#define MOD_KoStatusHue 24
#define KoMOD_StatusHueIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusHue + MOD_KoOffset)
#define KoMOD_StatusHue knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusHue + MOD_KoOffset)
//!< Number: 25, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define MOD_KoStatusRGB 25
#define KoMOD_StatusRGBIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusRGB + MOD_KoOffset)
#define KoMOD_StatusRGB knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusRGB + MOD_KoOffset)
//!< Number: 26, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define MOD_KoStatusHSV 26
#define KoMOD_StatusHSVIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusHSV + MOD_KoOffset)
#define KoMOD_StatusHSV knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusHSV + MOD_KoOffset)

//-----Module: RGBW
#define MOD_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_Active knx.paramBit((MOD_ParamBlockOffset + MOD_Active), 0)
#define MOD_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeed ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_DimSpeed)))))
#define MOD_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDay ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_BrightnessDay)))))
#define MOD_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamMOD_BrightnessNight ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_BrightnessNight)))))
#define MOD_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamMOD_DefaultColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_DefaultColorTemp)))))
#define MOD_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamMOD_MinColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_MinColorTemp)))))
#define MOD_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamMOD_MaxColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_MaxColorTemp)))))
#define MOD_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamMOD_DefaultColor knx.paramData((MOD_ParamBlockOffset + MOD_DefaultColor))
#define MOD_Type		0x0000
#define MOD_Type_Shift	4
#define MOD_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_Type ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define MOD_KoSwitch 0
#define KoMOD_SwitchIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSwitch + MOD_KoOffset)
#define KoMOD_Switch knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSwitch + MOD_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define MOD_KoBrightnessAbsolute 1
#define KoMOD_BrightnessAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessAbsolute + MOD_KoOffset)
#define KoMOD_BrightnessAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessAbsolute + MOD_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define MOD_KoBrightnessRelative 2
#define KoMOD_BrightnessRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessRelative + MOD_KoOffset)
#define KoMOD_BrightnessRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessRelative + MOD_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define MOD_KoColorTempAbsolute 3
#define KoMOD_ColorTempAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempAbsolute + MOD_KoOffset)
#define KoMOD_ColorTempAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempAbsolute + MOD_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define MOD_KoColorTempRelative 4
#define KoMOD_ColorTempRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempRelative + MOD_KoOffset)
#define KoMOD_ColorTempRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempRelative + MOD_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define MOD_KoSaturationAbsolute 5
#define KoMOD_SaturationAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSaturationAbsolute + MOD_KoOffset)
#define KoMOD_SaturationAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSaturationAbsolute + MOD_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define MOD_KoSaturationRelative 6
#define KoMOD_SaturationRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSaturationRelative + MOD_KoOffset)
#define KoMOD_SaturationRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSaturationRelative + MOD_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define MOD_KoHueAbsolute 7
#define KoMOD_HueAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoHueAbsolute + MOD_KoOffset)
#define KoMOD_HueAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoHueAbsolute + MOD_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define MOD_KoHueRelative 8
#define KoMOD_HueRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoHueRelative + MOD_KoOffset)
#define KoMOD_HueRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoHueRelative + MOD_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define MOD_KoColorRGB 9
#define KoMOD_ColorRGBIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorRGB + MOD_KoOffset)
#define KoMOD_ColorRGB knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorRGB + MOD_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define MOD_KoColorHSV 10
#define KoMOD_ColorHSVIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorHSV + MOD_KoOffset)
#define KoMOD_ColorHSV knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorHSV + MOD_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define MOD_KoStatus 20
#define KoMOD_StatusIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatus + MOD_KoOffset)
#define KoMOD_Status knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatus + MOD_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define MOD_KoStatusBrightness 21
#define KoMOD_StatusBrightnessIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusBrightness + MOD_KoOffset)
#define KoMOD_StatusBrightness knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusBrightness + MOD_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define MOD_KoStatusColorTemp 22
#define KoMOD_StatusColorTempIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusColorTemp + MOD_KoOffset)
#define KoMOD_StatusColorTemp knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusColorTemp + MOD_KoOffset)
//!< Number: 23, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define MOD_KoStatusSaturation 23
#define KoMOD_StatusSaturationIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusSaturation + MOD_KoOffset)
#define KoMOD_StatusSaturation knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusSaturation + MOD_KoOffset)
//!< Number: 24, Text: Kanal {{argChan}} (Status), Function: Farbton
#define MOD_KoStatusHue 24
#define KoMOD_StatusHueIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusHue + MOD_KoOffset)
#define KoMOD_StatusHue knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusHue + MOD_KoOffset)
//!< Number: 25, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define MOD_KoStatusRGB 25
#define KoMOD_StatusRGBIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusRGB + MOD_KoOffset)
#define KoMOD_StatusRGB knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusRGB + MOD_KoOffset)
//!< Number: 26, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define MOD_KoStatusHSV 26
#define KoMOD_StatusHSVIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusHSV + MOD_KoOffset)
#define KoMOD_StatusHSV knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusHSV + MOD_KoOffset)

//-----Module: RGB
#define MOD_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_ActiveIndex(X) knx.paramBit((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_Active knx.paramBit((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_Active), 0)
#define MOD_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeed ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_DimSpeed)))))
#define MOD_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDay ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_BrightnessDay)))))
#define MOD_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamMOD_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamMOD_BrightnessNight ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_BrightnessNight)))))
#define MOD_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamMOD_DefaultColorTempIndex(X) ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_DefaultColorTemp)))))
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamMOD_DefaultColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_DefaultColorTemp)))))
#define MOD_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamMOD_MinColorTempIndex(X) ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_MinColorTemp)))))
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamMOD_MinColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_MinColorTemp)))))
#define MOD_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamMOD_MaxColorTempIndex(X) ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_MaxColorTemp)))))
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamMOD_MaxColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_MaxColorTemp)))))
#define MOD_DefaultColor		0x000A
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamMOD_DefaultColorIndex(X) knx.paramData((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_DefaultColor))
// Offset: 10, Size: 24 Bit (3 Byte), Text: Kanal {{argChan}} Einschaltfarbe
#define ParamMOD_DefaultColor knx.paramData((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_DefaultColor))
#define MOD_Type		0x0000
#define MOD_Type_Shift	4
#define MOD_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_TypeIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_Type ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define MOD_KoSwitch 0
#define KoMOD_SwitchIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSwitch + MOD_KoOffset)
#define KoMOD_Switch knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSwitch + MOD_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define MOD_KoBrightnessAbsolute 1
#define KoMOD_BrightnessAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessAbsolute + MOD_KoOffset)
#define KoMOD_BrightnessAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessAbsolute + MOD_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define MOD_KoBrightnessRelative 2
#define KoMOD_BrightnessRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessRelative + MOD_KoOffset)
#define KoMOD_BrightnessRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessRelative + MOD_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define MOD_KoColorTempAbsolute 3
#define KoMOD_ColorTempAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempAbsolute + MOD_KoOffset)
#define KoMOD_ColorTempAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempAbsolute + MOD_KoOffset)
//!< Number: 4, Text: Kanal {{argChan}}, Function: Farbtemperatur (relativ)
#define MOD_KoColorTempRelative 4
#define KoMOD_ColorTempRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempRelative + MOD_KoOffset)
#define KoMOD_ColorTempRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempRelative + MOD_KoOffset)
//!< Number: 5, Text: Kanal {{argChan}}, Function: Sättigung (absolut)
#define MOD_KoSaturationAbsolute 5
#define KoMOD_SaturationAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSaturationAbsolute + MOD_KoOffset)
#define KoMOD_SaturationAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSaturationAbsolute + MOD_KoOffset)
//!< Number: 6, Text: Kanal {{argChan}}, Function: Sättigung (relativ)
#define MOD_KoSaturationRelative 6
#define KoMOD_SaturationRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSaturationRelative + MOD_KoOffset)
#define KoMOD_SaturationRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSaturationRelative + MOD_KoOffset)
//!< Number: 7, Text: Kanal {{argChan}}, Function: Farbton (absolut)
#define MOD_KoHueAbsolute 7
#define KoMOD_HueAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoHueAbsolute + MOD_KoOffset)
#define KoMOD_HueAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoHueAbsolute + MOD_KoOffset)
//!< Number: 8, Text: Kanal {{argChan}}, Function: Farbton (relativ)
#define MOD_KoHueRelative 8
#define KoMOD_HueRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoHueRelative + MOD_KoOffset)
#define KoMOD_HueRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoHueRelative + MOD_KoOffset)
//!< Number: 9, Text: Kanal {{argChan}}, Function: Farbe (RGB)
#define MOD_KoColorRGB 9
#define KoMOD_ColorRGBIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorRGB + MOD_KoOffset)
#define KoMOD_ColorRGB knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorRGB + MOD_KoOffset)
//!< Number: 10, Text: Kanal {{argChan}}, Function: Farbe (HSV)
#define MOD_KoColorHSV 10
#define KoMOD_ColorHSVIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorHSV + MOD_KoOffset)
#define KoMOD_ColorHSV knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorHSV + MOD_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define MOD_KoStatus 20
#define KoMOD_StatusIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatus + MOD_KoOffset)
#define KoMOD_Status knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatus + MOD_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define MOD_KoStatusBrightness 21
#define KoMOD_StatusBrightnessIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusBrightness + MOD_KoOffset)
#define KoMOD_StatusBrightness knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusBrightness + MOD_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define MOD_KoStatusColorTemp 22
#define KoMOD_StatusColorTempIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusColorTemp + MOD_KoOffset)
#define KoMOD_StatusColorTemp knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusColorTemp + MOD_KoOffset)
//!< Number: 23, Text: Kanal {{argChan}} (Status), Function: Sättigung
#define MOD_KoStatusSaturation 23
#define KoMOD_StatusSaturationIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusSaturation + MOD_KoOffset)
#define KoMOD_StatusSaturation knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusSaturation + MOD_KoOffset)
//!< Number: 24, Text: Kanal {{argChan}} (Status), Function: Farbton
#define MOD_KoStatusHue 24
#define KoMOD_StatusHueIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusHue + MOD_KoOffset)
#define KoMOD_StatusHue knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusHue + MOD_KoOffset)
//!< Number: 25, Text: Kanal {{argChan}} (Status), Function: Farbe (RGB)
#define MOD_KoStatusRGB 25
#define KoMOD_StatusRGBIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusRGB + MOD_KoOffset)
#define KoMOD_StatusRGB knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusRGB + MOD_KoOffset)
//!< Number: 26, Text: Kanal {{argChan}} (Status), Function: Farbe (HSV)
#define MOD_KoStatusHSV 26
#define KoMOD_StatusHSVIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusHSV + MOD_KoOffset)
#define KoMOD_StatusHSV knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusHSV + MOD_KoOffset)

//-----Module: CCT
#define MOD_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_ActiveIndex(X) knx.paramBit((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_Active knx.paramBit((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_Active), 0)
#define MOD_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeed ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_DimSpeed)))))
#define MOD_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDay ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_BrightnessDay)))))
#define MOD_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamMOD_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Nacht
#define ParamMOD_BrightnessNight ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_BrightnessNight)))))
#define MOD_DefaultColorTemp		0x0004
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamMOD_DefaultColorTempIndex(X) ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_DefaultColorTemp)))))
// Offset: 4, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Einschaltfarbtemperatur
#define ParamMOD_DefaultColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_DefaultColorTemp)))))
#define MOD_MinColorTemp		0x0006
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamMOD_MinColorTempIndex(X) ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_MinColorTemp)))))
// Offset: 6, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Minimale Farbtemperatur
#define ParamMOD_MinColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_MinColorTemp)))))
#define MOD_MaxColorTemp		0x0008
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamMOD_MaxColorTempIndex(X) ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_MaxColorTemp)))))
// Offset: 8, Size: 16 Bit (2 Byte), Text: Kanal {{argChan}} Maximale Farbtemperatur
#define ParamMOD_MaxColorTemp ((uint32_t)((knx.paramWord((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_MaxColorTemp)))))
#define MOD_Type		0x0000
#define MOD_Type_Shift	4
#define MOD_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_TypeIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_Type ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define MOD_KoSwitch 0
#define KoMOD_SwitchIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSwitch + MOD_KoOffset)
#define KoMOD_Switch knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSwitch + MOD_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define MOD_KoBrightnessAbsolute 1
#define KoMOD_BrightnessAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessAbsolute + MOD_KoOffset)
#define KoMOD_BrightnessAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessAbsolute + MOD_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define MOD_KoBrightnessRelative 2
#define KoMOD_BrightnessRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessRelative + MOD_KoOffset)
#define KoMOD_BrightnessRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessRelative + MOD_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (absolut)
#define MOD_KoColorTempAbsolute 3
#define KoMOD_ColorTempAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempAbsolute + MOD_KoOffset)
#define KoMOD_ColorTempAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempAbsolute + MOD_KoOffset)
//!< Number: 3, Text: Kanal {{argChan}}, Function: Farbtemperatur (relative)
#define MOD_KoColorTempRelative 3
#define KoMOD_ColorTempRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoColorTempRelative + MOD_KoOffset)
#define KoMOD_ColorTempRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoColorTempRelative + MOD_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define MOD_KoStatus 20
#define KoMOD_StatusIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatus + MOD_KoOffset)
#define KoMOD_Status knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatus + MOD_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define MOD_KoStatusBrightness 21
#define KoMOD_StatusBrightnessIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusBrightness + MOD_KoOffset)
#define KoMOD_StatusBrightness knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusBrightness + MOD_KoOffset)
//!< Number: 22, Text: Kanal {{argChan}} (Status), Function: Farbtemperatur
#define MOD_KoStatusColorTemp 22
#define KoMOD_StatusColorTempIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusColorTemp + MOD_KoOffset)
#define KoMOD_StatusColorTemp knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusColorTemp + MOD_KoOffset)

//-----Module: DIM
#define MOD_Active		0x0000
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_ActiveIndex(X) knx.paramBit((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_Active), 0)
// Offset: 0, Size: 1 Bit, Text: Kanal {{argChan}} aktiv
#define ParamMOD_Active knx.paramBit((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_Active), 0)
#define MOD_DimSpeed		0x0001
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeedIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_DimSpeed)))))
// Offset: 1, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Dimmgeschwindigkeit
#define ParamMOD_DimSpeed ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_DimSpeed)))))
#define MOD_BrightnessDay		0x0002
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDayIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_BrightnessDay)))))
// Offset: 2, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Tag
#define ParamMOD_BrightnessDay ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_BrightnessDay)))))
#define MOD_BrightnessNight		0x0003
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Night
#define ParamMOD_BrightnessNightIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_BrightnessNight)))))
// Offset: 3, Size: 8 Bit (1 Byte), Text: Kanal {{argChan}} Einschalthelligkeit Night
#define ParamMOD_BrightnessNight ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_BrightnessNight)))))
#define MOD_Type		0x0000
#define MOD_Type_Shift	4
#define MOD_Type_Mask	0x0007
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_TypeIndex(X) ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * X + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
// Offset: 0, BitOffset: 1, Size: 3 Bit, Text: Dummy
#define ParamMOD_Type ((uint32_t)((knx.paramByte((MOD_ParamBlockOffset + MOD_ParamBlockSize * channelIndex() + MOD_Type)) >> MOD_Type_Shift) & MOD_Type_Mask))
//!< Number: 0, Text: Kanal {{argChan}}, Function: Schalten
#define MOD_KoSwitch 0
#define KoMOD_SwitchIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoSwitch + MOD_KoOffset)
#define KoMOD_Switch knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoSwitch + MOD_KoOffset)
//!< Number: 1, Text: Kanal {{argChan}}, Function: Helligkeit (absolut)
#define MOD_KoBrightnessAbsolute 1
#define KoMOD_BrightnessAbsoluteIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessAbsolute + MOD_KoOffset)
#define KoMOD_BrightnessAbsolute knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessAbsolute + MOD_KoOffset)
//!< Number: 2, Text: Kanal {{argChan}}, Function: Helligkeit (relativ)
#define MOD_KoBrightnessRelative 2
#define KoMOD_BrightnessRelativeIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoBrightnessRelative + MOD_KoOffset)
#define KoMOD_BrightnessRelative knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoBrightnessRelative + MOD_KoOffset)
//!< Number: 20, Text: Kanal {{argChan}} (Status), Function: Status
#define MOD_KoStatus 20
#define KoMOD_StatusIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatus + MOD_KoOffset)
#define KoMOD_Status knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatus + MOD_KoOffset)
//!< Number: 21, Text: Kanal {{argChan}} (Status), Function: Helligkeit
#define MOD_KoStatusBrightness 21
#define KoMOD_StatusBrightnessIndex(X) knx.getGroupObject(MOD_KoBlockSize * X + MOD_KoStatusBrightness + MOD_KoOffset)
#define KoMOD_StatusBrightness knx.getGroupObject(MOD_KoBlockSize * channelIndex() + MOD_KoStatusBrightness + MOD_KoOffset)

