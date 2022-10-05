// Motor A
int motor1PinR = 18; //IN1
int motor1PinF = 19; //IN2
int motor2PinR = 12; //IN4
int motor2PinF = 17; //IN3
int dutyCycle = 180;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1PinF, OUTPUT);
  pinMode(motor1PinR, OUTPUT);
  pinMode(motor2PinF, OUTPUT);
  pinMode(motor2PinR, OUTPUT);
  //pinMode(enable1Pin, OUTPUT);

  Serial.begin(115200);
  Serial.print("Testing DC Motor...");
}

void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1PinF, LOW);
  digitalWrite(motor1PinR, HIGH); 
  digitalWrite(motor2PinF, LOW);
  digitalWrite(motor2PinR, HIGH); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1PinF, LOW);
  digitalWrite(motor1PinR, LOW);
  digitalWrite(motor2PinF, LOW);
  digitalWrite(motor2PinR, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1PinF, HIGH);
  digitalWrite(motor1PinR, LOW); 
  digitalWrite(motor2PinF, HIGH);
  digitalWrite(motor2PinR, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1PinF, LOW);
  digitalWrite(motor1PinR, LOW);
  digitalWrite(motor2PinF, LOW);
  digitalWrite(motor2PinR, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1PinF, HIGH);
  digitalWrite(motor1PinR, LOW);
  digitalWrite(motor2PinF, HIGH);
  digitalWrite(motor2PinR, LOW);
  while (dutyCycle <= 255){
    //ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle + 5;
    delay(500);
  }
  dutyCycle = 200;
}
