#include <EasyUltrasonic.h>

#define TRIGPIN 2 // Digital pin connected to the trig pin of the ultrasonic sensor
#define ECHOPIN 4 // Digital pin connected to the echo pin of the ultrasonic sensor

EasyUltrasonic ultrasonic; // Create the ultrasonic object

void setup() {
  Serial.begin(9600); // Open the serial port

  ultrasonic.attach(TRIGPIN, ECHOPIN); // Attaches the ultrasonic sensor on the specified pins on the ultrasonic object
}

void loop() {
  float distanceCM = ultrasonic.getDistanceCM(); // Read the distance in centimeters

  // float distanceIN = ultrasonic.getDistanceIN(); // Uncomment if you want to get the distance in inches
  
  // Print the distance value in Serial Monitor
  Serial.print(distanceCM);
  Serial.println(" cm");

  delay(100);
}
