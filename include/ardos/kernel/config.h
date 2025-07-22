#pragma once

// Screen configuration
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Menu configuration
#define MENU_HEIGHT 20
#define MENU_WIDTH SCREEN_WIDTH
#define MENU_BG_COLOR ILI9341_DARKCYAN
#define MENU_TEXT_COLOR ILI9341_WHITE

// TFT pins
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define TFT_LED 6

#define SLEEP_TIMEOUT 5 * 60 * 1000  // 5 minutes
#define POWER_SAVE_TIMEOUT 60 * 1000 // 1 minute