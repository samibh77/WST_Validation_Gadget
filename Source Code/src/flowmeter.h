#ifndef FLOWMETER_H
#define FLOWMETER_H
#include <Arduino.h>

const int flowMeterPin = 11;
extern volatile int pulseCount;
extern int pulseCountTot;
extern float flowRate;
extern float totalVolume;

extern volatile int activeTest;

const float calibrationFactor = 8.91; // 8.91 -->1/2 // 6.6 --> 1/4 // 1 pouces --> 8 - 4 impulses 

extern unsigned long previousMillis;
const unsigned long interval = 1000; // 1 second interval for flow calculation

void flowmeter_test(int sensorType);
void IRAM_ATTR sharedInterruptHandler();
//void pulseCounter();
void setup_flowmeter();
//void setup_bruit_1();

#endif
