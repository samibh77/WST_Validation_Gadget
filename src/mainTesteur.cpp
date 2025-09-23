#include<flowmeter.h>
#include<TXpower.h>
#include<bruit.h>
#include<OLED.h>

void setup(){
    setup_OLED();
    
    setup_flowmeter();
    setup_TXpower();
    setup_bruit();
    
}

void loop (){

     if (inTestMode) {
    handleTestMode();
  } else {
    handleMenuMode();
  }
}