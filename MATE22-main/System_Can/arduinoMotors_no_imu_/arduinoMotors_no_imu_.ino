#include <Servo.h>
#include <SPI.h>
#include <mcp2515.h>
#include<Servo.h>
//1--bfl2    2--bbr3    3--tfr4    4--tfl5      5--tbl6    6--bbl7   7-tbr8  8--bfr9

#define tfr 4
#define tfl 5
#define tbr 8
#define tbl 6
#define bfr 9
#define bfl 2
#define bbr 3
#define bbl 7

Servo TFR;
Servo TFL;
Servo TBR;
Servo TBL;
Servo BFR;
Servo BFL;
Servo BBR;
Servo BBL;

Servo SCam;

#define Laser A2
#define Servopin A3
#define Lighting A5
#define LGripper A0
#define RGripper A1
#define BGripper A4

#define MOTORS_ID 0xF5
#define LL_ID 0x30

MCP2515 mcp2515(10);
struct can_frame msgMotors,msgLL;

int speeds[8],LL[2];

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(30);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  SCam.attach(Servopin);
  pinMode(2,1);
  
  pinMode(Laser,OUTPUT);//Laser
  pinMode(Lighting,OUTPUT);//Lighting
 


  TFR.attach(tfr);// attach BFR to pin D2 
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
  Serial.println("wait---");
  delay(10000); 
  Serial.println("lol lol lol lol....");

  
}

void loop() {
  if (mcp2515.readMessage(&msgMotors) == MCP2515::ERROR_OK) {
      if ( msgMotors.can_id == MOTORS_ID) {
        for(int i= 0 ; i < msgMotors.can_dlc ; i ++)
        {
         speeds[i] = (msgMotors.data[i]*2)-202;
         Serial.print(speeds[i]);
         Serial.print(" "); 
        }
        Serial.println("");
        
         TFR.writeMicroseconds(speeds[0]+1500);
         TFL.writeMicroseconds(speeds[1]+1500);
         TBR.writeMicroseconds(speeds[2]+1500);
         TBL.writeMicroseconds(speeds[3]+1500);

         BFR.writeMicroseconds(speeds[4]+1500);
         BFL.writeMicroseconds(speeds[5]+1500);
         BBR.writeMicroseconds(speeds[6]+1500);
         BBL.writeMicroseconds(speeds[7]+1500);
          
      }

      else if (msgMotors.can_id == LL_ID) {// msgLL.can_id == LL_ID
        for(int i= 0 ; i < msgMotors.can_dlc ; i ++)
        {
          LL[i] = msgMotors.data[i];
          Serial.print((char)LL[i]);
          Serial.print("");
        }
        Serial.println("");
          digitalWrite(Laser,LL[0]&0x01);     // Laser On/Off
          digitalWrite(Lighting,LL[0]&0x02);  // Lighting On/Off
          digitalWrite(LGripper,LL[0]&0x20);     // Lgripper Open/Close
          digitalWrite(RGripper,LL[0]&0x40);  // RGripper Open/Close
          digitalWrite(BGripper,LL[0]&0x80);     // BGripper Open/Close
          
          if((LL[0]&0x1C) == 0)
          {
            SCam.write(70);
          }
          else if(((LL[0]&0x1C)>>2) == 1)
          {
            SCam.write(90);
          }
          else if(((LL[0]&0x1C)>>2) == 2)
          {
            SCam.write(120);
          }
          else if(((LL[0]&0x1C)>>2) == 3)
          {
            SCam.write(140);
          }
          else if(((LL[0]&0x1C)) == 4)
          {
            SCam.write(160);
          }
        }
    }
//    if (mcp2515.readMessage(&msgLL) == MCP2515::ERROR_OK) {
//      Serial.println( msgLL.can_id,HEX);
//      if (true) {// msgLL.can_id == LL_ID
//        for(int i= 0 ; i < msgLL.can_dlc ; i ++)
//        {
//          LL[i] = msgLL.data[i];
//          Serial.print((char)LL[i]);
//          Serial.print("");
//        }
//        Serial.println("");
////          digitalWrite(A2,LL[0]);
////          digitalWrite(A5,LL[1]);
//        }
//        }
        


//    }
}
