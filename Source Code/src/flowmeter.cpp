#include<flowmeter.h>
#include<OLED.h>
#include<bruit.h>

volatile int pulseCount = 0;
//volatile int pulseCountBruit = 0;
int pulseCountTot = 0;
float flowRate = 0;
float totalVolume = 0;
unsigned long previousMillis = 0;

volatile int activeTest = 0;


void IRAM_ATTR sharedInterruptHandler() {
    if (activeTest == 1) {
        pulseCount++;
    } else if (activeTest == 2) {
          pulseCountBruit++;
          lastImpulseTime = millis();
    }
}

void setup_flowmeter() {
  Serial.begin(115200);  
  pinMode(flowMeterPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowMeterPin), sharedInterruptHandler, FALLING);  
}

/*void setup_bruit_1() {
  Serial.begin(115200);  
  pinMode(flowMeterPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowMeterPin), sharedInterruptHandler, FALLING);  
}*/

/*void countPulses() {
  pulseCount++;
}*/

/*void IRAM_ATTR pulseCounter() {
    pulseCount++;
}*/



void flowmeter_test(int sensorType) {

    activeTest = 1;
    float calibrationFactor = (sensorType == 1) ? 8.91 : 6.6; // Set calibration factor based on sensor type
    unsigned long currentMillis = millis();

    
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

      
        flowRate = (pulseCount / calibrationFactor);
        totalVolume += (flowRate / 60.0);
        pulseCountTot += pulseCount;
        pulseCount = 0;

        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE); 
        display.setCursor(0, 0);
        display.println("Pulses Counted:");
        display.setCursor(0, 10);
        display.print(pulseCountTot);
        display.println("  Pulse");

        display.setCursor(0, 20);
        display.println("Flow Rate:");
        display.setCursor(0, 30);
        display.print(flowRate);
        display.println(" L/Min");

        display.setCursor(0, 40);
        display.print("Total Volume:");
        display.setCursor(0, 50);
        display.print(totalVolume);
        display.println(" L");
        display.display(); 
    }
}



/*void flowmeter_test(){

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    flowRate = (pulseCount / calibrationFactor);

    totalVolume += (flowRate / 60.0);

    // Reset pulse count for the next 
    pulseCountTot += pulseCount ;
    pulseCount = 0;

    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");

    Serial.print("Total Volume: ");
    Serial.print(totalVolume);
    Serial.println(" L");

    Serial.print("Total pulse count ");
    Serial.println(pulseCountTot);
}
}*/





