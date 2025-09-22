#ifndef TXpower_H
#define TXpower_H
#include <SPI.h>
#include <LoRa.h>
#include<Arduino.h>     

// Define LoRa pins
#define SS 34 // 5 // 34 
#define RST 20 // 14 //20 
#define DIO0 39  // 26 // 39 

#define SCK 36  // 18  // 36 
#define MISO 37  //19 // 37 
#define MOSI 35  // 23 // 35

// Define button pins
#define BUTTON_INCREASE 9
#define BUTTON_DECREASE 10

// Variable to store the TX power
extern int txPower ;  // Default TX power set to 17 dBm

// Debouncing time
extern unsigned long lastDebounceTimeIncrease  ;
extern unsigned long lastDebounceTimeDecrease  ;
const unsigned long debounceDelay = 800;  // Increased debounce delay in milliseconds

// Variable to hold the button states
extern bool lastButtonStateIncrease ;
extern bool lastButtonStateDecrease ;

void setup_TXpower();
void TXpower_test();
void checkButtons();
void sendPacket();
void increaseTxPower();
void decreaseTxPower();


#endif
