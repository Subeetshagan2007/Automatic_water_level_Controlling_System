// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;
const int relayPin = 7;

// Variables
long duration;
int distance;

void setup() {
  // Initialize the pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);

  // Start serial communication (optional for debugging)
  Serial.begin(9600);
}

void loop() {
  // Send the trigger signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin and calculate distance
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Convert to centimeters

  // Print the distance (for debugging)
  Serial.print("Distance: ");
  Serial.println(distance);

  // Threshold values for water levels
  int lowWaterLevel = 30;  // Distance threshold when water is low (pump should turn on)
  int fullWaterLevel = 5;  // Distance threshold when the tank is full (pump should turn off)

  // If the water level is low (distance is greater than lowWaterLevel), turn the pump ON
  if (distance > lowWaterLevel) {
    digitalWrite(relayPin, LOW); // LOW to activate the relay (turn pump ON)
    digitalWrite(ledPin, HIGH);   // Turn on LED
  }
  // If the water level is full (distance is less than fullWaterLevel), turn the pump OFF
  else if (distance <= fullWaterLevel) {
    digitalWrite(relayPin, HIGH ); // HIGH to deactivate the relay (turn pump OFF)
    digitalWrite(ledPin, LOW);   // Turn off LED to indicate full water level
  }

  delay(1000); // Delay before taking the next reading
}
