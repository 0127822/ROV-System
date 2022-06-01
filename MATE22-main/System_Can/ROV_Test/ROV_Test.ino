#include <Servo.h>

#define tfr 6
#define tfl 8
#define tbr 10
#define tbl 12
#define bfr 7
#define bfl 9
#define bbr 13
#define bbl 11

Servo TFR;
Servo TFL;
Servo TBR;
Servo TBL;
Servo BFR;
Servo BFL;
Servo BBR;
Servo BBL;

#define Laser 48
//#define Servopin 30
//#define Lighting 44
#define LGripper 38
#define RGripper 40
#define BGripper 36

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(30);
  // put your setup code here, to run once:
  pinMode(Laser,1);//Laser
  pinMode(LGripper,1);
  pinMode(RGripper,1);
  pinMode(BGripper,1);
  // Motors Attaching and Initialization
  TFR.attach(tfr);
  TFL.attach(tfl);
  TBR.attach(tbr);
  TBL.attach(tbl);

  BFR.attach(bfr);
  BFL.attach(bfl);
  BBR.attach(bbr);
  BBL.attach(bbl);

  TFR.writeMicroseconds(1500);
  TFL.writeMicroseconds(1500);
  TBR.writeMicroseconds(1500);
  TBL.writeMicroseconds(1500);
  BFR.writeMicroseconds(1500);
  BFL.writeMicroseconds(1500);
  BBR.writeMicroseconds(1500);
  BBL.writeMicroseconds(1500);
  Serial.println("Initializing.......");
  delay(10000); 
  Serial.println("Initialized....");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  char x;
  if(Serial.available()>0){
    x = Serial.read();
    if(x == 'm'){
      Serial.println("All Motors running....");
      TFR.writeMicroseconds(1550);
  TFL.writeMicroseconds(1550);
  TBR.writeMicroseconds(1550);
  TBL.writeMicroseconds(1550);
  BFR.writeMicroseconds(1550);
  BFL.writeMicroseconds(1550);
  BBR.writeMicroseconds(1550);
  BBL.writeMicroseconds(1550);
  Serial.println("All Motors running....");
  delay(3000);
  TFR.writeMicroseconds(1500);
  TFL.writeMicroseconds(1500);
  TBR.writeMicroseconds(1500);
  TBL.writeMicroseconds(1500);
  BFR.writeMicroseconds(1500);
  BFL.writeMicroseconds(1500);
  BBR.writeMicroseconds(1500);
  BBL.writeMicroseconds(1500);
  Serial.println("Stopped....");
    }
    else if(x=='1'){
      TFR.writeMicroseconds(1550);
      delay(3000);
      TFR.writeMicroseconds(1500);
    }
    else if(x=='2'){
      TFL.writeMicroseconds(1550);
      delay(3000);
      TFL.writeMicroseconds(1500);
    }
    else if(x=='3'){
      TBR.writeMicroseconds(1550);
      delay(3000);
      TBR.writeMicroseconds(1500);
    }
    else if(x=='4'){
      TBL.writeMicroseconds(1550);
      delay(3000);
      TBL.writeMicroseconds(1500);
    }
    else if(x=='5'){
      BFR.writeMicroseconds(1550);
      delay(3000);
      BFR.writeMicroseconds(1500);
    }
    else if(x=='6'){
      BFL.writeMicroseconds(1550);
      delay(3000);
      BFL.writeMicroseconds(1500);
    }
    else if(x=='7'){
      BBR.writeMicroseconds(1550);
      delay(3000);
      BBR.writeMicroseconds(1500);
    }
    else if(x=='8'){
      BBL.writeMicroseconds(1580);
      delay(3000);
      BBL.writeMicroseconds(1500);
    }
    else if(x=='q'){
      digitalWrite(Laser,1);
      Serial.println("laser on");
    }
    else if(x=='a'){
      digitalWrite(Laser,0);
      Serial.println("laser off");
    }
    else if(x=='w'){
      digitalWrite(LGripper,1);
      Serial.println("LGripper open");
    }
    else if(x=='s'){
      digitalWrite(LGripper,0);
      Serial.println("LGripper closed");
    }
    else if(x=='e'){
      digitalWrite(RGripper,1);
      Serial.println("RGripper open");
    }
    else if(x=='d'){
      digitalWrite(RGripper,0);
      Serial.println("RGripper closed");
    }
    else if(x=='r'){
      digitalWrite(BGripper,1);
      Serial.println("BGripper open");
    }
    else if(x=='f'){
      digitalWrite(BGripper,0);
      Serial.println("BGripper closed");
    }
  }
  
}
