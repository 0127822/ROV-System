

#include<Servo.h>


#define tfr 3
#define tfl 5
#define tbr 2
#define tbl 7
#define bfr 9
#define bfl 6
#define bbr 8
#define bbl 4


Servo TFR;
Servo TFL;
Servo TBR;
Servo TBL;
Servo BFR;
Servo BFL;
Servo BBR;
Servo BBL;
void setup(){
  Serial.begin(115200);
  TFR.attach(tfr);
  TFL.attach(tfl);
  TBR.attach(tbr);
  TBL.attach(tbl);

  BFR.attach(bfr);
  BFL.attach(bfl);
  BBR.attach(bbr);
  BBL.attach(bbl);
  


  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);

  delay(7000);
  
  TFR.writeMicroseconds(1550);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1550);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1550);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1550);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1550);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1550);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1550);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1550);
  digitalWrite(9,0);

  delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
}

void loop() {
  if(Serial.available()>0)
  {
    char m = Serial.read();
    if( m == '1')
    {
      TFR.writeMicroseconds(1550);
      Serial.println("1");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '2')
    {
      TFL.writeMicroseconds(1550);
      Serial.println("2");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '3')
    {
      TBR.writeMicroseconds(1550);
      Serial.println("3");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '4')
    {
      TBL.writeMicroseconds(1550);
      Serial.println("4");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '5')
    {
      BFR.writeMicroseconds(1550);
      Serial.println("5");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '6')
    {
      BFL.writeMicroseconds(1600);
      Serial.println("6");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '7')
    {
      BBR.writeMicroseconds(1550);
      Serial.println("7");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
    else if( m == '8')
    {
      BBL.writeMicroseconds(1550);
      Serial.println("8");
      delay(3000);
  
  TFR.writeMicroseconds(1500);
  digitalWrite(2,0);
  TFL.writeMicroseconds(1500);
  digitalWrite(3,0);  
  TBR.writeMicroseconds(1500);
  digitalWrite(4,0);  
  TBL.writeMicroseconds(1500);
  digitalWrite(5,0);
  BFR.writeMicroseconds(1500);
  digitalWrite(6,0);
  BFL.writeMicroseconds(1500);
  digitalWrite(7,0);  
  BBR.writeMicroseconds(1500);
  digitalWrite(8,0);  
  BBL.writeMicroseconds(1500);
  digitalWrite(9,0);
    }
  }
}
