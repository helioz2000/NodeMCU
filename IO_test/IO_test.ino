/*
 *  NodeMCU IO_test
 *  
 */

#include <ESP8266WiFi.h>

ADC_MODE(ADC_VCC);    // switch analog input to read VCC

#define BUTTON_PIN D3

#define UPDATE_TIME 3000
int led_pin = 2; 
bool show_info = false;
bool last_buttonState = 1;
unsigned long time_expired = 0;

void setup() {
  Serial.begin(9600);
  delay(10); 
  mylog("\n-- ESP8266 Test --\n");

  pinMode(BUTTON_PIN, INPUT);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  delay(2000);
  digitalWrite(led_pin, HIGH);
  
  mylog("----\n");
  
  esp_info();
  delay(1000);
  wifi_info();
  mylog("\n--> press Flash button to toggle display update\n");
}

void esp_info() {
  mylog("\nChip info:\n");
  mylog("Reset reason: %s\n", ESP.getResetReason().c_str() );
  mylog("Chip ID: %u\n", ESP.getChipId() );
  mylog("Core Version: %s\n", ESP.getCoreVersion().c_str() );
  mylog("SDK Version: %s\n", ESP.getSdkVersion() );
  mylog("CPU Frequency: %uMHz\n", ESP.getCpuFreqMHz() );
  mylog("Sketch size: %u\n", ESP.getSketchSize() );
  mylog("Free Sketch space: %u\n", ESP.getFreeSketchSpace() );
  mylog("Flash Chip ID: %u\n", ESP.getFlashChipId() );
  mylog("Flash Chip size: %u (as seen by SDK)\n", ESP.getFlashChipSize() );
  mylog("Flash Chip size: %u (physical)\n", ESP.getFlashChipRealSize() );
  mylog("Flash Chip speed: %uHz\n", ESP.getFlashChipSpeed() );
  mylog("VCC: %.2f\n", (float)ESP.getVcc() / 896 );

}

void wifi_info() {
  mylog("\nWiFi Diagnostic:\n");
  WiFi.printDiag(Serial);
  if (WiFi.status() == WL_CONNECTED) {
    mylog("\nWiFi status: Connected\n");
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    mylog("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
    IPAddress ip = WiFi.localIP();
    mylog("IP address: %s\n", ip.toString().c_str() );
    ip = WiFi.subnetMask();
    mylog("Subnet mask: %s\n", ip.toString().c_str() );
    mylog("Hostname: %s\n", WiFi.hostname().c_str() );
    mylog("RSSI: %d dBm\n", WiFi.RSSI() );
  } else {
    mylog("\nWiFi status: Not Connected\n");
  }
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  if (buttonState != last_buttonState) {
    if (!buttonState) {   // button pressed
      show_info = !show_info;
      if (show_info) {
        mylog("Display update is ON\n");
      } else {
        mylog("Display update is OFF\n");
      }
    }
    delay(100);
    last_buttonState = buttonState;
  }

  if ((show_info) && (time_expired < millis()) ) {
    mylog("VCC: %.2f (%d)\n", (float)ESP.getVcc() / 900.0, ESP.getVcc() );
    time_expired = millis() + UPDATE_TIME;
  }
}

// print debug output on console interface
void mylog(const char *sFmt, ...)
{
  char acTmp[128];       // place holder for sprintf output
  va_list args;          // args variable to hold the list of parameters
  va_start(args, sFmt);  // mandatory call to initilase args 

  vsprintf(acTmp, sFmt, args);
  Serial.print(acTmp);
  // mandatory tidy up
  va_end(args);
  return;
}

