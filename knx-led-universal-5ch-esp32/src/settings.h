#include <Arduino.h>

#define CPU_FREQ 160 // 160 should be sufficient, otherwise raise to 240
#define MIN_CYCLE_TIME 5000 //ms

#define ERASE_BTN 0 // GPIO to erase ESP flash

#define STAT_LED_OFF HIGH
#define STAT_LED_ON LOW

// #define STAT_LED_GN 2 //green onboard LED
// #define STAT_LED_RD 5 //red onboard LED

#define CCT_MODE NORMAL
#define WHITE_LED_RGB_EQUIVALENT {255, 198, 175} // About 4200 Kelvin -24 green

#define DEBUGGING true
