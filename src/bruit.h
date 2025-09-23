#ifndef bruit_H
#define bruit_H
#include<Arduino.h>
#include <time.h>
#include <WiFi.h>  
#include <SPI.h>
#include <SD.h>  
#include <FS.h>


#define SD_CS 33
#define SD_CLK 36
#define SD_MISO 37
#define SD_MOSI 35

extern const char *ssid;
extern const char *password;

//extern volatile int pulseCount ;   // Variable to store the number of pulses
extern unsigned long lastImpulseTime ;  // Variable to track the time of the last impulse
extern const unsigned long impulseTimeout ;  // Timeout after which we assume the impulse period has ended (2 seconds)
extern volatile int pulseCountBruit;

//void IRAM_ATTR pulseCountBruiter();
void setup_bruit();
void printImpulseData();
void resetCounter();
void test_bruit();
    

#endif