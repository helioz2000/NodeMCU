/*
 *  NodeMCU Blink test
 *  
 */

//#define LED_BUILTIN D4
#define LED_ON LOW
#define LED_OFF HIGH
#define DELAY 2000

void setup() {
  Serial.begin(9600);
  delay(10); 
  Serial.print("\n-- ESP8266 Blink Test --\n");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LED_ON);
  digitalWrite(D8, HIGH);
  delay(DELAY);
  digitalWrite(LED_BUILTIN, LED_OFF);
  digitalWrite(D8, LOW);
  delay(DELAY);
}

