//Include and initialize json
#include <ArduinoJson.h>
const int JSONSIZE = 100;
//References used pins
int BEATPIN = A5;
int TEMPERATUREPIN = A4;
int OXYGENPIN = A3;

void setup() { 
  //Register each pin
  pinMode(BEATPIN, INPUT);
  pinMode(TEMPERATUREPIN, INPUT);
  pinMode(OXYGENPIN, INPUT);
  //Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  //Get and serialize data
  StaticJsonDocument<JSONSIZE> json;
  json["beat_rate"] = measureMockedAnalog(BEATPIN);
  json["temperature"] = measureMockedAnalog(TEMPERATUREPIN);
  json["oxygen"] = measureMockedAnalog(OXYGENPIN);
  serializeJson(json, Serial);
  Serial.println();
  //Wait one second to calculate again
  delay(1000);
}

double measureMockedAnalog(int pin) {
  // Calculate to mock the ratio to aprox. 0.01V to 1 (eg. 1V = 100)
  return analogRead(pin) / 2.05;
}
