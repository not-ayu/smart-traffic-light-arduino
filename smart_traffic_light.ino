#include <Wire.h>

// Lane LEDs and sensors
int northRed = 2, northYellow = 3, northGreen = 4, sensorNorth = 5;
int eastRed = 6, eastYellow = 7, eastGreen = 8, sensorEast = 9;
int southRed = 10, southYellow = 11, southGreen = 12, sensorSouth = A0;
int westRed = A2, westYellow = A3, westGreen = 13, sensorWest = A1;

void setup() {
  int leds[] = {
    northRed, northYellow, northGreen,
    eastRed, eastYellow, eastGreen,
    southRed, southYellow, southGreen,
    westRed, westYellow, westGreen
  };
  for (int i = 0; i < 12; i++) pinMode(leds[i], OUTPUT);

  pinMode(sensorNorth, INPUT);
  pinMode(sensorEast, INPUT);
  pinMode(sensorSouth, INPUT);
  pinMode(sensorWest, INPUT);

  Serial.begin(9600);
  Serial.println("Smart Traffic Started...");
  delay(2000);
}

void loop() {
  // Read sensor states
  bool n = digitalRead(sensorNorth) == 0;
  bool e = digitalRead(sensorEast) == 0;
  bool s = digitalRead(sensorSouth) == 0;
  bool w = digitalRead(sensorWest) == 0;

  // At least one lane has traffic
  if (n || e || s || w) {
    if (n) controlLane("North", northRed, northYellow, northGreen, 15);
    if (e) controlLane("East", eastRed, eastYellow, eastGreen, 15);
    if (s) controlLane("South", southRed, southYellow, southGreen, 15);
    if (w) controlLane("West", westRed, westYellow, westGreen, 15);
  } else {
    // No traffic — cycle each for 3 sec
    controlLane("North", northRed, northYellow, northGreen, 3);
    controlLane("East", eastRed, eastYellow, eastGreen, 3);
    controlLane("South", southRed, southYellow, southGreen, 3);
    controlLane("West", westRed, westYellow, westGreen, 3);
  }
}

void controlLane(String name, int red, int yellow, int green, int greenTime) {
  allRed();

  Serial.print(name);
  Serial.print(" Lane - Green for ");
  Serial.print(greenTime);
  Serial.println("s");

  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(greenTime * 1000);
  digitalWrite(green, LOW);

  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(1000);
}

void allRed() {
  int redPins[] = {northRed, eastRed, southRed, westRed};
  int yellowPins[] = {northYellow, eastYellow, southYellow, westYellow};
  int greenPins[] = {northGreen, eastGreen, southGreen, westGreen};

  for (int i = 0; i < 4; i++) {
    digitalWrite(redPins[i], HIGH);
    digitalWrite(yellowPins[i], LOW);
    digitalWrite(greenPins[i], LOW);
  }
}
