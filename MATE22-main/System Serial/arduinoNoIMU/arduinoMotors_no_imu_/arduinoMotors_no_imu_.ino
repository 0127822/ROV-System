#include <Servo.h>
#include <SPI.h>
#include <mcp2515.h>
#include<Servo.h>

#define tfr 9
#define tfl 7
#define tbr 8
#define tbl 4
#define bfr 3
#define bfl 5
#define bbr 2
#define bbl 6

Servo TFR;
Servo TFL;
Servo TBR;
Servo TBL;
Servo BFR;
Servo BFL;
Servo BBR;
Servo BBL;


#define MOTORS_ID 0xF5

MCP2515 mcp2515(10);
struct can_frame msgMotors;
int speeds[8];

void setup() {
Serial.begin(115200);
  Serial.setTimeout(30);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  pinMode(2,1);


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

  delay(7000); 
  
}

void loop() {
  if (mcp2515.readMessage(&msgMotors) == MCP2515::ERROR_OK) {
      if ( msgMotors.can_id == MOTORS_ID) {
        for(int i= 0 ; i < msgMotors.can_dlc ; i ++)
        {
         speeds[i] = (msgMotors.data[i]*2)-202;
         Serial.print(speeds[i]);
         Serial.print(" ");

         TFR.writeMicroseconds(speeds[0]+1500);
         TFL.writeMicroseconds(speeds[1]+1500);
         TBR.writeMicroseconds(speeds[2]+1500);
         TBL.writeMicroseconds(speeds[3]+1500);

         BFR.writeMicroseconds(speeds[4]+1500);
         BFL.writeMicroseconds(speeds[5]+1500);
         BBR.writeMicroseconds(speeds[6]+1500);
         BBL.writeMicroseconds(speeds[7]+1500);
         
        }
        Serial.println("");
          
      }
    }
}
