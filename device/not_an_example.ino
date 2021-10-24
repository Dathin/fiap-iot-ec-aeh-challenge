//Include and initialize json
#include <ArduinoJson.h>
const int JSONSIZE = 100;
//References used pins
int BEATPIN = A5;
int TEMPERATUREPIN = A4;
int OXYGENPIN = A3;
int EMERGENCYPIN = 12;

void setup() { 
  //Register each pin
  pinMode(BEATPIN, INPUT);
  pinMode(TEMPERATUREPIN, INPUT);
  pinMode(OXYGENPIN, INPUT);
  pinMode(EMERGENCYPIN, INPUT);
  //Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  //Get and serialize data
  StaticJsonDocument<JSONSIZE> jsonMeasure;
  StaticJsonDocument<JSONSIZE> jsonEmergency;
  jsonMeasure["beat_rate"] = measureMockedAnalog(BEATPIN);
  jsonMeasure["temperature"] = measureMockedAnalog(TEMPERATUREPIN);
  jsonMeasure["oxygen"] = measureMockedAnalog(OXYGENPIN);
  serializeJson(jsonMeasure, Serial);
  Serial.println();
  if(digitalRead(EMERGENCYPIN) == 0) {
    jsonEmergency["emergency"] = true;
    serializeJson(jsonEmergency, Serial);
    Serial.println();
  }
  //Wait one second to calculate again
  delay(1000);
}

double measureMockedAnalog(int pin) {
  // Calculate to mock the ratio to aprox. 0.01V to 1 (eg. 1V = 100)
  return analogRead(pin) / 2.05;
}