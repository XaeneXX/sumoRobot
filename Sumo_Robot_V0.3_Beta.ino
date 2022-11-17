#include <dummy.h>
#include <EasyUltrasonic.h>
// Motor R
int motor1PinR = 18; //IN1
int motor1PinF = 19; //IN2

//Motor L
int motor2PinR = 12; //IN4
int motor2PinF = 17; //IN3

//IR sensor
int L_sensor=39;
int R_sensor=36;
//for non-blocking delay
unsigned long previousMillis = 0UL;
unsigned long previousDistance = 0;
//unsigned long interval = 1000UL;

//SR04 setup
#define TRIGPIN 2 // Digital pin connected to the trig pin of the ultrasonic sensor
#define ECHOPIN 4 // Digital pin connected to the echo pin of the ultrasonic sensor

EasyUltrasonic ultrasonic; // Create the ultrasonic object

void setup() {
  // sets the pins as outputs:
  pinMode(motor1PinF, OUTPUT);
  pinMode(motor1PinR, OUTPUT);
  pinMode(motor2PinF, OUTPUT);
  pinMode(motor2PinR, OUTPUT);
  //IR sensor pin setup
  pinMode(R_sensor, INPUT);
  pinMode(L_sensor, INPUT);
  //assign SR04
  ultrasonic.attach(TRIGPIN, ECHOPIN); // Attaches the ultrasonic sensor on the specified pins on the ultrasonic object
  //serial comm speed
  Serial.begin(115200);
}

void loop() 
{
//strategi: jika distance >1m, pusing clockwise
scan();
                //kalau jumpa ada objek...kita pecut laju-laju
if(!RSense() && !LSense())
{
Serial.println("Rsensor OFF, LSensor OFF");
forward(255);//speed & move time
}
//ke belakang jika duda2 sensor active
if(RSense() && LSense())
  {
    Serial.println("Rsensor ON, LSensor ON");
    stop();
    reverse(180);
    delay(1000);
    stop();
    scan();
  }

if(RSense() && !LSense()) //right detect left doesn't
  {
    Serial.println("Rsensor ON, LSensor OFF");
    stop();
    rotateL(180);//pusing clockwise
    delay(1000);
    stop();
    scan();
  }

if(!RSense() && LSense()) //left detect right doesn't
  {
    Serial.println("Rsensor OFF, LSensor ON");
    stop();
    rotateR(180);//pusing clockwise
    delay(1000);
    stop();
    scan();
  }
}


void rotateR(int speed)//16nov2022-nanti edit: rotate selagi distance >1m
{
  RF(speed);
  LR(speed);
}

void rotateL(int speed)//16nov2022-nanti edit: rotate selagi distance >1m
{
  RR(speed);
  LF(speed);
}

void forward(int speed)
{
  RF(speed);
  LF(speed);
}

void reverse(int speed)
{
  RR(speed);
  LR(speed);
}
void RF(int speed)
{
  analogWrite(motor1PinF, speed);
  analogWrite(motor1PinR, 0);   
}

void RR(int speed)
{
  analogWrite(motor1PinF, 0);
  analogWrite(motor1PinR, speed);   
}

void LF(int speed)
{
  analogWrite(motor2PinF, speed);
  analogWrite(motor2PinR, 0);   
}

void LR(int speed)
{
  analogWrite(motor2PinF, 0);
  analogWrite(motor2PinR, speed);   
}

void stop()
{
  analogWrite(motor1PinF, 0);
  analogWrite(motor1PinR, 0); 
  analogWrite(motor2PinF, 0);
  analogWrite(motor2PinR, 0); 
}

bool RSense()
{
return(digitalRead(R_sensor));
}

bool LSense()
{
return(digitalRead(L_sensor));
}

void wait(long time)
{
  unsigned long  currentMillis = millis();
  while(currentMillis < previousMillis + (time*1000))
    {}
  previousMillis = currentMillis;
}

void scan()//scan sekeliling
{
float distance = ultrasonic.getDistanceCM();

float currentDistance=distance;

while(currentDistance >= previousDistance) //selagi sensor x detect object, buat scanning secara berpusing arah jam
  {rotateR(150);
  delay(500);
  stop();}
  previousDistance = currentDistance;

}
