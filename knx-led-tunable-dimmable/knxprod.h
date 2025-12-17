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
#define MAIN_ParameterSize 74
#define MAIN_MaxKoNumber 201


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
#define APP_CH1_Active		0x0026
// Offset: 38, BitOffset: 4, Size: 1 Bit, Text: Kanal 1 aktiv
#define ParamAPP_CH1_Active knx.paramBit(APP_CH1_Active, 4)
#define APP_CH1_DimSpeed		0x002C
// Offset: 44, Size: 8 Bit (1 Byte), Text: Kanal 1 Dimmgeschwindigkeit
#define ParamAPP_CH1_DimSpeed ((uint32_t)((knx.paramByte(APP_CH1_DimSpeed))))
#define APP_CH1_BrightnessDay		0x002D
// Offset: 45, Size: 8 Bit (1 Byte), Text: Kanal 1 Einschalthelligkeit Tag
#define ParamAPP_CH1_BrightnessDay ((uint32_t)((knx.paramByte(APP_CH1_BrightnessDay))))
#define APP_CH1_BrightnessNight		0x002E
// Offset: 46, Size: 8 Bit (1 Byte), Text: Kanal 1 Einschalthelligkeit Nacht
#define ParamAPP_CH1_BrightnessNight ((uint32_t)((knx.paramByte(APP_CH1_BrightnessNight))))
#define APP_CH1_DefaultColorTemp		0x002F
// Offset: 47, Size: 16 Bit (2 Byte), Text: Kanal 1 Einschaltfarbtemperatur
#define ParamAPP_CH1_DefaultColorTemp ((uint32_t)((knx.paramWord(APP_CH1_DefaultColorTemp))))
#define APP_CH1_MinColorTemp		0x0031
// Offset: 49, Size: 16 Bit (2 Byte), Text: Kanal 1 Minimale Farbtemperatur
#define ParamAPP_CH1_MinColorTemp ((uint32_t)((knx.paramWord(APP_CH1_MinColorTemp))))
#define APP_CH1_MaxColorTemp		0x0033
// Offset: 51, Size: 16 Bit (2 Byte), Text: Kanal 1 Maximale Farbtemperatur
#define ParamAPP_CH1_MaxColorTemp ((uint32_t)((knx.paramWord(APP_CH1_MaxColorTemp))))
#define APP_CH1_DefaultColor		0x0035
// Offset: 53, Size: 24 Bit (3 Byte), Text: Kanal 1 Einschaltfarbe
#define ParamAPP_CH1_DefaultColor knx.paramData(APP_CH1_DefaultColor)
#define APP_CH2_Active		0x0026
// Offset: 38, BitOffset: 5, Size: 1 Bit, Text: Kanal 2 aktiv
#define ParamAPP_CH2_Active knx.paramBit(APP_CH2_Active, 5)
#define APP_CH2_DimSpeed		0x0038
// Offset: 56, Size: 8 Bit (1 Byte), Text: Kanal 2 Dimmgeschwindigkeit
#define ParamAPP_CH2_DimSpeed ((uint32_t)((knx.paramByte(APP_CH2_DimSpeed))))
#define APP_CH2_BrightnessDay		0x0039
// Offset: 57, Size: 8 Bit (1 Byte), Text: Kanal 2 Einschalthelligkeit Tag
#define ParamAPP_CH2_BrightnessDay ((uint32_t)((knx.paramByte(APP_CH2_BrightnessDay))))
#define APP_CH2_BrightnessNight		0x003A
// Offset: 58, Size: 8 Bit (1 Byte), Text: Kanal 2 Einschalthelligkeit Nacht
#define ParamAPP_CH2_BrightnessNight ((uint32_t)((knx.paramByte(APP_CH2_BrightnessNight))))
#define APP_CH2_DefaultColorTemp		0x003B
// Offset: 59, Size: 16 Bit (2 Byte), Text: Kanal 2 Einschaltfarbtemperatur
#define ParamAPP_CH2_DefaultColorTemp ((uint32_t)((knx.paramWord(APP_CH2_DefaultColorTemp))))
#define APP_CH2_MinColorTemp		0x003D
// Offset: 61, Size: 16 Bit (2 Byte), Text: Kanal 2 Minimale Farbtemperatur
#define ParamAPP_CH2_MinColorTemp ((uint32_t)((knx.paramWord(APP_CH2_MinColorTemp))))
#define APP_CH2_MaxColorTemp		0x003F
// Offset: 63, Size: 16 Bit (2 Byte), Text: Kanal 2 Maximale Farbtemperatur
#define ParamAPP_CH2_MaxColorTemp ((uint32_t)((knx.paramWord(APP_CH2_MaxColorTemp))))
#define APP_CH3_Active		0x0026
// Offset: 38, BitOffset: 6, Size: 1 Bit, Text: Kanal 3 aktiv
#define ParamAPP_CH3_Active knx.paramBit(APP_CH3_Active, 6)
#define APP_CH3_DimSpeed		0x0041
// Offset: 65, Size: 8 Bit (1 Byte), Text: Kanal 3 Dimmgeschwindigkeit
#define ParamAPP_CH3_DimSpeed ((uint32_t)((knx.paramByte(APP_CH3_DimSpeed))))
#define APP_CH3_BrightnessDay		0x0042
// Offset: 66, Size: 8 Bit (1 Byte), Text: Kanal 3 Einschalthelligkeit Tag
#define ParamAPP_CH3_BrightnessDay ((uint32_t)((knx.paramByte(APP_CH3_BrightnessDay))))
#define APP_CH3_BrightnessNight		0x0043
// Offset: 67, Size: 8 Bit (1 Byte), Text: Kanal 3 Einschalthelligkeit Nacht
#define ParamAPP_CH3_BrightnessNight ((uint32_t)((knx.paramByte(APP_CH3_BrightnessNight))))
#define APP_CH4_Active		0x0026
// Offset: 38, BitOffset: 7, Size: 1 Bit, Text: Kanal 4 aktiv
#define ParamAPP_CH4_Active knx.paramBit(APP_CH4_Active, 7)
#define APP_CH4_DimSpeed		0x0044
// Offset: 68, Size: 8 Bit (1 Byte), Text: Kanal 4 Dimmgeschwindigkeit
#define ParamAPP_CH4_DimSpeed ((uint32_t)((knx.paramByte(APP_CH4_DimSpeed))))
#define APP_CH4_BrightnessDay		0x0045
// Offset: 69, Size: 8 Bit (1 Byte), Text: Kanal 4 Einschalthelligkeit Tag
#define ParamAPP_CH4_BrightnessDay ((uint32_t)((knx.paramByte(APP_CH4_BrightnessDay))))
#define APP_CH4_BrightnessNight		0x0046
// Offset: 70, Size: 8 Bit (1 Byte), Text: Kanal 4 Einschalthelligkeit Nacht
#define ParamAPP_CH4_BrightnessNight ((uint32_t)((knx.paramByte(APP_CH4_BrightnessNight))))
#define APP_CH5_Active		0x0027
// Offset: 39, BitOffset: 6, Size: 1 Bit, Text: Kanal 5 aktiv
#define ParamAPP_CH5_Active knx.paramBit(APP_CH5_Active, 6)
#define APP_CH5_DimSpeed		0x0047
// Offset: 71, Size: 8 Bit (1 Byte), Text: Kanal 5 Dimmgeschwindigkeit
#define ParamAPP_CH5_DimSpeed ((uint32_t)((knx.paramByte(APP_CH5_DimSpeed))))
#define APP_CH5_BrightnessDay		0x0048
// Offset: 72, Size: 8 Bit (1 Byte), Text: Kanal 5 Einschalthelligkeit Tag
#define ParamAPP_CH5_BrightnessDay ((uint32_t)((knx.paramByte(APP_CH5_BrightnessDay))))
#define APP_CH5_BrightnessNight		0x0049
// Offset: 73, Size: 8 Bit (1 Byte), Text: Kanal 5 Einschalthelligkeit Nacht
#define ParamAPP_CH5_BrightnessNight ((uint32_t)((knx.paramByte(APP_CH5_BrightnessNight))))
//!< Number: 1, Text: Zentral, Function: In Betrieb
#define APP_KoHeartbeat 1
#define KoAPP_Heartbeat knx.getGroupObject(APP_KoHeartbeat)
//!< Number: 2, Text: Zentral, Function: Tag/Nacht
#define APP_KoGeneralDayNight 2
#define KoAPP_GeneralDayNight knx.getGroupObject(APP_KoGeneralDayNight)
//!< Number: 20, Text: Kanal 1, Function: Schalten
#define APP_KoCH1_Schalten 20
#define KoAPP_CH1_Schalten knx.getGroupObject(APP_KoCH1_Schalten)
//!< Number: 21, Text: Kanal 1, Function: Helligkeit (absolut)
#define APP_KoCH1_BrightnessAbsolute 21
#define KoAPP_CH1_BrightnessAbsolute knx.getGroupObject(APP_KoCH1_BrightnessAbsolute)
//!< Number: 22, Text: Kanal 1, Function: Helligkeit (relativ)
#define APP_KoCH1_BrightnessRelative 22
#define KoAPP_CH1_BrightnessRelative knx.getGroupObject(APP_KoCH1_BrightnessRelative)
//!< Number: 23, Text: Kanal 1, Function: Farbtemperatur (absolut)
#define APP_KoCH1_ColortempAbsolute 23
#define KoAPP_CH1_ColortempAbsolute knx.getGroupObject(APP_KoCH1_ColortempAbsolute)
//!< Number: 24, Text: Kanal 1, Function: Farbtemperatur (relativ)
#define APP_KoCH1_ColortempRelative 24
#define KoAPP_CH1_ColortempRelative knx.getGroupObject(APP_KoCH1_ColortempRelative)
//!< Number: 25, Text: Kanal 1, Function: Sättigung (absolut)
#define APP_KoCH1_SaturationAbsolute 25
#define KoAPP_CH1_SaturationAbsolute knx.getGroupObject(APP_KoCH1_SaturationAbsolute)
//!< Number: 26, Text: Kanal 1, Function: Sättigung (relativ)
#define APP_KoCH1_SaturationRelative 26
#define KoAPP_CH1_SaturationRelative knx.getGroupObject(APP_KoCH1_SaturationRelative)
//!< Number: 27, Text: Kanal 1, Function: Farbton (absolut)
#define APP_KoCH1_HueAbsolute 27
#define KoAPP_CH1_HueAbsolute knx.getGroupObject(APP_KoCH1_HueAbsolute)
//!< Number: 28, Text: Kanal 1, Function: Farbton (relativ)
#define APP_KoCH1_HueRelative 28
#define KoAPP_CH1_HueRelative knx.getGroupObject(APP_KoCH1_HueRelative)
//!< Number: 29, Text: Kanal 1, Function: Farbe (RGB)
#define APP_KoCH1_ColorRGB 29
#define KoAPP_CH1_ColorRGB knx.getGroupObject(APP_KoCH1_ColorRGB)
//!< Number: 30, Text: Kanal 1, Function: Farbe (HSV)
#define APP_KoCH1_ColorHSV 30
#define KoAPP_CH1_ColorHSV knx.getGroupObject(APP_KoCH1_ColorHSV)
//!< Number: 40, Text: Kanal 1 (Status), Function: Status
#define APP_KoCH1_Status 40
#define KoAPP_CH1_Status knx.getGroupObject(APP_KoCH1_Status)
//!< Number: 41, Text: Kanal 1 (Status), Function: Helligkeit
#define APP_KoCH1_StatusBrightness 41
#define KoAPP_CH1_StatusBrightness knx.getGroupObject(APP_KoCH1_StatusBrightness)
//!< Number: 42, Text: Kanal 1 (Status), Function: Farbtemperatur
#define APP_KoCH1_StatusColortemp 42
#define KoAPP_CH1_StatusColortemp knx.getGroupObject(APP_KoCH1_StatusColortemp)
//!< Number: 43, Text: Kanal 1 (Status), Function: Sättigung
#define APP_KoCH1_StatusSaturation 43
#define KoAPP_CH1_StatusSaturation knx.getGroupObject(APP_KoCH1_StatusSaturation)
//!< Number: 44, Text: Kanal 1 (Status), Function: Farbton
#define APP_KoCH1_StatusHue 44
#define KoAPP_CH1_StatusHue knx.getGroupObject(APP_KoCH1_StatusHue)
//!< Number: 45, Text: Kanal 1 (Status), Function: Farbe (RGB)
#define APP_KoCH1_StatusRGB 45
#define KoAPP_CH1_StatusRGB knx.getGroupObject(APP_KoCH1_StatusRGB)
//!< Number: 46, Text: Kanal 1 (Status), Function: Farbe (HSV)
#define APP_KoCH1_StatusHSV 46
#define KoAPP_CH1_StatusHSV knx.getGroupObject(APP_KoCH1_StatusHSV)
//!< Number: 60, Text: Kanal 2, Function: Schalten
#define APP_KoCH2_Schalten 60
#define KoAPP_CH2_Schalten knx.getGroupObject(APP_KoCH2_Schalten)
//!< Number: 61, Text: Kanal 2, Function: Helligkeit (absolut)
#define APP_KoCH2_BrightnessAbsolute 61
#define KoAPP_CH2_BrightnessAbsolute knx.getGroupObject(APP_KoCH2_BrightnessAbsolute)
//!< Number: 62, Text: Kanal 2, Function: Helligkeit (relativ)
#define APP_KoCH2_BrightnessRelative 62
#define KoAPP_CH2_BrightnessRelative knx.getGroupObject(APP_KoCH2_BrightnessRelative)
//!< Number: 63, Text: Kanal 2, Function: Farbtemperatur (absolut)
#define APP_KoCH2_ColortempAbsolute 63
#define KoAPP_CH2_ColortempAbsolute knx.getGroupObject(APP_KoCH2_ColortempAbsolute)
//!< Number: 64, Text: Kanal 2, Function: Farbtemperatur (relativ)
#define APP_KoCH2_ColortempRelative 64
#define KoAPP_CH2_ColortempRelative knx.getGroupObject(APP_KoCH2_ColortempRelative)
//!< Number: 80, Text: Kanal 2 (Status), Function: Status
#define APP_KoCH2_Status 80
#define KoAPP_CH2_Status knx.getGroupObject(APP_KoCH2_Status)
//!< Number: 81, Text: Kanal 2 (Status), Function: Helligkeit
#define APP_KoCH2_StatusBrightness 81
#define KoAPP_CH2_StatusBrightness knx.getGroupObject(APP_KoCH2_StatusBrightness)
//!< Number: 82, Text: Kanal 2 (Status), Function: Farbtemperatur
#define APP_KoCH2_StatusColortemp 82
#define KoAPP_CH2_StatusColortemp knx.getGroupObject(APP_KoCH2_StatusColortemp)
//!< Number: 100, Text: Kanal 3, Function: Schalten
#define APP_KoCH3_Schalten 100
#define KoAPP_CH3_Schalten knx.getGroupObject(APP_KoCH3_Schalten)
//!< Number: 101, Text: Kanal 3, Function: Helligkeit (absolut)
#define APP_KoCH3_BrightnessAbsolute 101
#define KoAPP_CH3_BrightnessAbsolute knx.getGroupObject(APP_KoCH3_BrightnessAbsolute)
//!< Number: 102, Text: Kanal 3, Function: Helligkeit (relativ)
#define APP_KoCH3_BrightnessRelative 102
#define KoAPP_CH3_BrightnessRelative knx.getGroupObject(APP_KoCH3_BrightnessRelative)
//!< Number: 120, Text: Kanal 3 (Status), Function: Status
#define APP_KoCH3_Status 120
#define KoAPP_CH3_Status knx.getGroupObject(APP_KoCH3_Status)
//!< Number: 121, Text: Kanal 3 (Status), Function: Helligkeit
#define APP_KoCH3_StatusBrightness 121
#define KoAPP_CH3_StatusBrightness knx.getGroupObject(APP_KoCH3_StatusBrightness)
//!< Number: 140, Text: Kanal 4, Function: Schalten
#define APP_KoCH4_Schalten 140
#define KoAPP_CH4_Schalten knx.getGroupObject(APP_KoCH4_Schalten)
//!< Number: 141, Text: Kanal 4, Function: Helligkeit (absolut)
#define APP_KoCH4_BrightnessAbsolute 141
#define KoAPP_CH4_BrightnessAbsolute knx.getGroupObject(APP_KoCH4_BrightnessAbsolute)
//!< Number: 142, Text: Kanal 4, Function: Helligkeit (relativ)
#define APP_KoCH4_BrightnessRelative 142
#define KoAPP_CH4_BrightnessRelative knx.getGroupObject(APP_KoCH4_BrightnessRelative)
//!< Number: 160, Text: Kanal 4 (Status), Function: Status
#define APP_KoCH4_Status 160
#define KoAPP_CH4_Status knx.getGroupObject(APP_KoCH4_Status)
//!< Number: 161, Text: Kanal 4 (Status), Function: Helligkeit
#define APP_KoCH4_StatusBrightness 161
#define KoAPP_CH4_StatusBrightness knx.getGroupObject(APP_KoCH4_StatusBrightness)
//!< Number: 180, Text: Kanal 5, Function: Schalten
#define APP_KoCH5_Schalten 180
#define KoAPP_CH5_Schalten knx.getGroupObject(APP_KoCH5_Schalten)
//!< Number: 161, Text: Kanal 5, Function: Helligkeit (absolut)
#define APP_KoCH5_BrightnessAbsolute 161
#define KoAPP_CH5_BrightnessAbsolute knx.getGroupObject(APP_KoCH5_BrightnessAbsolute)
//!< Number: 162, Text: Kanal 5, Function: Helligkeit (relativ)
#define APP_KoCH5_BrightnessRelative 162
#define KoAPP_CH5_BrightnessRelative knx.getGroupObject(APP_KoCH5_BrightnessRelative)
//!< Number: 200, Text: Kanal 5 (Status), Function: Status
#define APP_KoCH5_Status 200
#define KoAPP_CH5_Status knx.getGroupObject(APP_KoCH5_Status)
//!< Number: 201, Text: Kanal 5 (Status), Function: Helligkeit
#define APP_KoCH5_StatusBrightness 201
#define KoAPP_CH5_StatusBrightness knx.getGroupObject(APP_KoCH5_StatusBrightness)

