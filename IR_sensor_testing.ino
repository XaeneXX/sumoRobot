int L_sensor=39;
int R_sensor=36;


void setup() {

Serial.begin(9600);
pinMode(R_sensor, INPUT);
  pinMode(L_sensor, INPUT);
}

void loop() {

Serial.println(digitalRead(L_sensor));
Serial.println("  ");
Serial.println(digitalRead(R_sensor));
delay(500);
}
