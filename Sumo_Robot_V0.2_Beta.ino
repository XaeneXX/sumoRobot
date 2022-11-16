//#include <dummy.h>

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
//unsigned long interval = 1000UL;

void setup() {
  // sets the pins as outputs:
  pinMode(motor1PinF, OUTPUT);
  pinMode(motor1PinR, OUTPUT);
  pinMode(motor2PinF, OUTPUT);
  pinMode(motor2PinR, OUTPUT);
  //pinMode(enable1Pin, OUTPUT);
  pinMode(R_sensor, INPUT);
  pinMode(L_sensor, INPUT);

  Serial.begin(115200);
}

void loop() 
{
//strategi: jika distance >1m, pusing clockwise
//jika distance <1m & sensor x detect line, go forward with max speed (255)

//OR! gunakan IR sensor sebagai interrupt (normal routine adalah forward)
//undur jika jumpa garis: kedua2 sensor aktif

//ke depan jika dua2 sensor x active
if(!RSense() && !LSense())
{
Serial.println("Rsensor OFF, LSensor OFF");
forward(180,50);//speed & move time
}
//ke belakang jika duda2 sensor active
if(RSense() && LSense())
{
Serial.println("Rsensor ON, LSensor ON");
reverse(180,50);
}

if(RSense() && !LSense()) //right detect left doesn't
{
Serial.println("Rsensor ON, LSensor OFF");
reverse(180,50);//undur dulu, kemudian pusing clockwise
rotateR(180, 50);//pusing clockwise
}

if(!RSense() && LSense()) //left detect right doesn't
{
Serial.println("Rsensor OFF, LSensor ON");
reverse(180,50);//undur dulu, kemudian pusing clockwise
rotateL(180, 50);//pusing clockwise
}
  
}

void rotateR(int speed, int moveTime)//16nov2022-nanti edit: rotate selagi distance >1m
{
  //while(distance > 1)
  for(int x = 0;x <= moveTime; x++)//guna kaedah gerak sikit2 supaya as if dua2 motor jalan serentak
  {
  RF(speed);
  LR(speed);
  }
}

void rotateL(int speed, int moveTime)//16nov2022-nanti edit: rotate selagi distance >1m
{
  for(int x = 0;x <= moveTime; x++)//guna kaedah gerak sikit2 supaya as if dua2 motor jalan serentak
  {
  RR(speed);
  LF(speed);
  }
}

void forward(int speed, int moveTime)
{
  for(int x = 0;x <= moveTime; x++)//guna kaedah gerak sikit2 supaya as if dua2 motor jalan serentak
  {
  RF(speed);
  LF(speed);
  }
}

void reverse(int speed, int moveTime)
{
  for(int x = 0;x <= moveTime; x++)
  {
  RR(speed);
  LR(speed);
  }
}
void RF(int speed)
{
  analogWrite(motor1PinF, speed);
  digitalWrite(motor1PinR, 0);   
}

void RR(int speed)
{
  digitalWrite(motor1PinF, 0);
  digitalWrite(motor1PinR, speed);   
}

void LF(int speed)
{
  analogWrite(motor2PinF, speed);
  digitalWrite(motor2PinR, 0);   
}

void LR(int speed)
{
  digitalWrite(motor2PinF, 0);
  digitalWrite(motor2PinR, speed);   
}

void stop()
{
  digitalWrite(motor1PinF, 0);
  digitalWrite(motor1PinR, 0); 
  digitalWrite(motor2PinF, 0);
  digitalWrite(motor2PinR, 0); 
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
}
