#include<bruit.h>
#include<OLED.h>
#include<flowmeter.h>


const char* ssid = "iPhone Sami"; ///TP-Link_7616 /// Ooredoo1F2A0F /// iPhone Sami
const char* password = "samisami"; /// 36466641 /// ZXFX#R65H@$F$ /// samisami
volatile int pulseCountBruit=0 ;   // Variable to store the number of pulses
unsigned long lastImpulseTime = 0;  // Variable to track the time of the last impulse
const unsigned long impulseTimeout = 2000;  // Timeout after which we assume the impulse period has ended (2 seconds)

//volatile int activeTest = 0;

//using fs::File;


/*void IRAM_ATTR pulseCountBruiter() {
  pulseCountBruit++;
  lastImpulseTime = millis();  // Update the last impulse detection time
}*/

void setup_bruit() {
  
  Serial.begin(115200);


  if (!SD.begin(SD_CS)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("SD card initialization failed!");
    display.display();
    while (1);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("SD card initialized.");
  display.display();
  delay(1500);

  // Connect to Wi-Fi
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connecting to Wi-Fi...");
  display.display();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Connecting...");
    display.display();
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Connected to Wi-Fi!");
  display.display();

   
  pinMode(flowMeterPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowMeterPin), sharedInterruptHandler, FALLING);

  // Initialize the time library (NTP setup for accurate time)
  configTime(3600, 3600, "pool.ntp.org"); // NTP for time synchronization
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    
    display.clearDisplay();
    display.setCursor(0, 0);
    Serial.println("Failed to obtain time");
    display.display();
  }
  else {

    display.clearDisplay();
    display.setCursor(0, 0);
    Serial.println("Time synchronized!");
    display.display();

    char buffer[40];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d / %H:%M:%S ", &timeinfo);  // Format: YYYY-MM-DD HH:MM:SS
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Current time: ");
    display.println(buffer);
    display.display();
  }
}

void test_bruit() {

  activeTest = 2;

  if (pulseCountBruit > 0 && millis() - lastImpulseTime >= impulseTimeout) {
    printImpulseData();  
    resetCounter();  
  }
}

void printImpulseData() {
// Get the current time
    time_t now;
    struct tm timeinfo;
    char timeBuffer[40];

    time(&now);
    localtime_r(&now, &timeinfo);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d - %H:%M:%S", &timeinfo);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(timeBuffer);
    display.setCursor(0, 20);
    display.print(pulseCountBruit);
    display.println(" impulsions");
    display.display();

    File dataFile = SD.open("/impulse_data.txt", FILE_APPEND);
    if (dataFile) {
        dataFile.printf("%s , %d impulsions\n", timeBuffer, pulseCountBruit);
        dataFile.close();
    } else {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Error saving data.");
        display.display();
    }
}

// Function to reset the pulse counter and prepare for new impulses
void resetCounter() {
  pulseCountBruit = 0;         // Reset the pulse count to zero
  lastImpulseTime = 0;    // Reset the last impulse time
}
