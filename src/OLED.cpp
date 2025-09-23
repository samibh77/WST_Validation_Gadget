#include<OLED.h>
#include<flowmeter.h>
#include<TXpower.h>
#include<bruit.h>



Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Define here


// Menu variables
int  currentOption = 0;
const int totalOptions = 3;
String menuOptions[] = {"Sensor Flow Test", "TX Power Test", "Noise Detection Test"};

// State variables
bool inTestMode = false;
bool initialMessageShown = false;
int sensorType = 1;
//int txPower_OLED = 0; // TX Power value for the "TX Power" test


void setup_OLED() {
  // Initialize buttons
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(QUIT_BUTTON, INPUT_PULLUP);

  // Initialize I2C with custom SDA and SCL pins
  Wire.begin(4, 6); // Set SDA to GPIO 4 and SCL to GPIO 6

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {             
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  updateDisplay();
} 


void handleMenuMode() {
  if(digitalRead(UP_BUTTON) == LOW) {
    currentOption = (currentOption - 1 + totalOptions) % totalOptions;
    updateDisplay();
    delay(200);
  }
  
  if(digitalRead(DOWN_BUTTON) == LOW) {
    currentOption = (currentOption + 1) % totalOptions;
    updateDisplay();
    delay(200);
  }
  
  if(digitalRead(ENTER_BUTTON) == LOW) { 
       inTestMode = true;
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Starting ");
        display.println(menuOptions[currentOption]);
        display.display();
        delay(1000);
        delay(200);
    }
}

// Add a flag  to track the initial display
//bool initialMessageShown = false;


void selectSensorType() {
    int sensorOption = 0; 
    const int totalSensorOptions = 2; 

    while (true) {
        // Update OLED display to show the current selection
        display.clearDisplay();
        display.setCursor(0, 0);
        display.setTextColor(SSD1306_WHITE);
        display.println("Select Sensor Type:");

     for (int i = 0; i < totalSensorOptions; i++) {
            display.setCursor(0, 20 + i * 20); // Position options vertically
            if (sensorOption == i) {
                display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Highlight selected option
            } else {
                display.setTextColor(SSD1306_WHITE); // Normal text for unselected options
            }
            if (i == 0) {
                display.println("Sensor Type 1 (1/2)");
            } else if (i == 1) {
                display.println("Sensor Type 2 (1/4)");
            }
        }

        display.display();
        
        // Check for user input
        if (digitalRead(UP_BUTTON) == LOW) {
            sensorOption = (sensorOption - 1 + totalSensorOptions) % totalSensorOptions; // Scroll up
            delay(200); // Debounce
        }
        if (digitalRead(DOWN_BUTTON) == LOW) {
            sensorOption = (sensorOption + 1) % totalSensorOptions; // Scroll down
            delay(200); // Debounce
        }
        if (digitalRead(ENTER_BUTTON) == LOW) {
            sensorType = (sensorOption == 0) ? 1 : 2; // Set sensor type based on choice
            break; // Exit loop after selection
        }
    }

    // Display confirmation of the selected sensor type
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Sensor Type ");
    display.print(sensorType);
    display.println(" Selected.");
    display.display();
    delay(1000);
}


void handleTestMode() {
    if (digitalRead(QUIT_BUTTON) == LOW) {
        flowRate = 0;
        pulseCountTot = 0;
        totalVolume = 0;
        inTestMode = false;
        initialMessageShown = false; // Reset the flag when exiting test mode
        updateDisplay(); // Return to menu
        delay(200);
        return;
    }

    if (currentOption == 0) { // Sensor Flow Test
        if (!initialMessageShown) {
            // Display the initial message only once
            selectSensorType(); 
            initialMessageShown = true; // Set flag to prevent repeating
        }
        
        flowmeter_test(sensorType);
    }
    else if (currentOption == 1) { // TX Power Test
        if (!initialMessageShown) {
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("Running TX Power Test...");
            display.display();
            delay(1000); // Show the message for 1 second
            initialMessageShown = true;
        }
        TXpower_test(); // Execute the TX Power test function from TXpower.cpp
    }
    else if (currentOption == 2) { // Noise Detection Test
        if (!initialMessageShown) {
            display.clearDisplay();
            display.setCursor(0, 0);
            display.println("Running Noise Detection Test...");
            display.display();
            delay(1000); // Show the message for 1 second
            initialMessageShown = true;
        }
        test_bruit();
    }
}


void updateDisplay() {
    display.clearDisplay();

    for (int i = 0; i < totalOptions; i++) {
        display.setTextSize(1);
        if (i == currentOption) {
            display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }

        int16_t x, y;
        uint16_t w, h;
        display.getTextBounds(menuOptions[i], 0, 0, &x, &y, &w, &h);
        int16_t xPos = (SCREEN_WIDTH - w) / 2;
        int16_t yPos = 10 + i * 20;

        display.setCursor(xPos, yPos);
        display.println(menuOptions[i]);
    }

    display.display();
}



