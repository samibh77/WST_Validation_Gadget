#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

extern Adafruit_SSD1306 display; // Declare as extern

// Button pins
#define UP_BUTTON 9
#define DOWN_BUTTON 10
#define ENTER_BUTTON 7
#define QUIT_BUTTON 12

// Menu variables
extern int  currentOption ;
extern const int totalOptions ;
extern String menuOptions[];

// State variables
extern bool inTestMode ;
extern int txPower_OLED ;

void setup_OLED();
void handleMenuMode();
void handleTestMode();
void updateDisplay();
void updatetxPower_OLEDDisplay();
void selectSensorType();

#endif