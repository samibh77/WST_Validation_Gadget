#include<TXpower.h>
#include<OLED.h>

int txPower = 20;
unsigned long lastDebounceTimeIncrease = 0;
unsigned long lastDebounceTimeDecrease = 0;
bool lastButtonStateIncrease = LOW;
bool lastButtonStateDecrease = LOW;


void setup_TXpower() {
    Serial.begin(115200);
  while (!Serial);

  pinMode(BUTTON_INCREASE, INPUT_PULLUP);
  pinMode(BUTTON_DECREASE, INPUT_PULLUP);


  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {  
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Starting LoRa failed!");
    display.display();
    while (1);
  }

  LoRa.setTxPower(txPower);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LoRa Transmitter initialized");
  display.display();
}

void TXpower_test() {
  // Check the time for sending a packet 
  static unsigned long lastPacketTime = 0;
  const unsigned long packetInterval = 3000;  // 3 seconds between packets

  if (millis() - lastPacketTime >= packetInterval) {
    sendPacket(); 
    lastPacketTime = millis();  // Update the last packet time
  }

  // Check for button presses continuously 
  checkButtons();
}




void checkButtons() {
  // Check the state of the increase button
  bool currentButtonStateIncrease = digitalRead(BUTTON_INCREASE);
  if (currentButtonStateIncrease == HIGH && lastButtonStateIncrease == LOW) {
    if (millis() - lastDebounceTimeIncrease > debounceDelay) {
      increaseTxPower();  
      lastDebounceTimeIncrease = millis();
    }
  }
  lastButtonStateIncrease = currentButtonStateIncrease;  // Store the button state

  // Check the state of the decrease button
  bool currentButtonStateDecrease = digitalRead(BUTTON_DECREASE);
  if (currentButtonStateDecrease == HIGH && lastButtonStateDecrease == LOW) {
    if (millis() - lastDebounceTimeDecrease > debounceDelay) {
      decreaseTxPower();  
      lastDebounceTimeDecrease = millis();
    }
  }
  lastButtonStateDecrease = currentButtonStateDecrease;  // Store the button state
}


void sendPacket() {

  LoRa.beginPacket();
  LoRa.print("TX Power Test");
  LoRa.endPacket();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Packet sent with TX power: ");
  display.setCursor(1, 30);
  display.println(txPower);
  display.display();
}

// Function to increase TX power
void increaseTxPower() {
  if (txPower < 20) {  // Maximum allowed is 20 dBm with PA boost
    txPower++;
    LoRa.setTxPower(txPower);
  
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("TX power increased to: ");
    display.setCursor(0, 20);
    display.print(txPower);
    display.display();

  } else {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("TX power is already at maximum.");
    display.display();
  }
}

// Function to decrease TX power
void decreaseTxPower() {
  if (txPower > 2) {  // Minimum allowed is 2 dBm
    txPower--;
    LoRa.setTxPower(txPower);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("TX power decreased to: ");
    display.setCursor(0, 20);
    display.print(txPower);
    display.display();

  } else {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("TX power is already at minimum.");
    display.display();
  }
}




///The closer the RSSI value is to 0, the stronger the signal. Typical values might range from around -30 dBm (strong signal) to -120 dBm (weak signal).
