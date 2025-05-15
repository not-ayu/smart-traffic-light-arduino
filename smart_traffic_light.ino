// Define LED pins and sensor pins for each lane
int northRed = 2, northYellow = 3, northGreen = 4, sensorNorth = 5;
int eastRed = 6, eastYellow = 7, eastGreen = 8, sensorEast = 9;
int southRed = 10, southYellow = 11, southGreen = 12, sensorSouth = A0;
int westRed = A2, westYellow = A3, westGreen = 13, sensorWest = A1;

void setup() {
  // Array of all traffic light LEDs to initialize as output
  int leds[] = {
    northRed, northYellow, northGreen,
    eastRed, eastYellow, eastGreen,
    southRed, southYellow, southGreen,
    westRed, westYellow, westGreen
  };

  // Set all LED pins as OUTPUT
  for (int i = 0; i < 12; i++) pinMode(leds[i], OUTPUT);

  // Set all IR sensor pins as INPUT
  pinMode(sensorNorth, INPUT);
  pinMode(sensorEast, INPUT);
  pinMode(sensorSouth, INPUT);
  pinMode(sensorWest, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
  Serial.println("Smart Traffic Started...");
  delay(2000);  // Initial delay before starting loop
}

void loop() {
  // Read each IR sensor: LOW means vehicle detected
  bool n = digitalRead(sensorNorth) == 0;
  bool e = digitalRead(sensorEast) == 0;
  bool s = digitalRead(sensorSouth) == 0;
  bool w = digitalRead(sensorWest) == 0;

  // If any lane has traffic, give priority with longer green time
  if (n || e || s || w) {
    if (n) controlLane("North", northRed, northYellow, northGreen, 15);
    if (e) controlLane("East", eastRed, eastYellow, eastGreen, 15);
    if (s) controlLane("South", southRed, southYellow, southGreen, 15);
    if (w) controlLane("West", westRed, westYellow, westGreen, 15);
  } else {
    // No traffic detected — run all lanes for default short time
    controlLane("North", northRed, northYellow, northGreen, 3);
    controlLane("East", eastRed, eastYellow, eastGreen, 3);
    controlLane("South", southRed, southYellow, southGreen, 3);
    controlLane("West", westRed, westYellow, westGreen, 3);
  }
}

// Controls signal for a single lane
void controlLane(String name, int red, int yellow, int green, int greenTime) {
  allRed();  // Ensure all other lights are red

  // Debug message
  Serial.print(name);
  Serial.print(" Lane - Green for ");
  Serial.print(greenTime);
  Serial.println("s");

  // Turn on green, wait, then switch to yellow and finally back to red
  digitalWrite(red, LOW);     // Red off
  digitalWrite(green, HIGH);  // Green on
  delay(greenTime * 1000);    // Wait for greenTime
  digitalWrite(green, LOW);   // Green off

  digitalWrite(yellow, HIGH); // Yellow on
  delay(2000);                // Yellow duration
  digitalWrite(yellow, LOW);  // Yellow off
  digitalWrite(red, HIGH);    // Red on again
  delay(1000);                // Small pause before next lane
}

// Sets all lights to red before giving green to any one lane
void allRed() {
  int redPins[] = {northRed, eastRed, southRed, westRed};
  int yellowPins[] = {northYellow, eastYellow, southYellow, westYellow};
  int greenPins[] = {northGreen, eastGreen, southGreen, westGreen};

  for (int i = 0; i < 4; i++) {
    digitalWrite(redPins[i], HIGH);    // Turn all red lights ON
    digitalWrite(yellowPins[i], LOW);  // Turn all yellow lights OFF
    digitalWrite(greenPins[i], LOW);   // Turn all green lights OFF
  }
}
