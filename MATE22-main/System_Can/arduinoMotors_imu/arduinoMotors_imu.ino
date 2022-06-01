#include <Servo.h>
#include <SPI.h>
#include <mcp2515.h>
#include "MPU9250.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

MPU9250 mpu;

/********************************************************************************************************************************************************************/
// Motors

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

/********************************************************************************************************************************************************************/
//Servo SCam;

/********************************************************************************************************************************************************************/
// Threading

TaskHandle_t TaskHandle_FromStation;
TaskHandle_t TaskHandle_IMU;
TaskHandle_t TaskHandle_CSensors;

void IMU(void *para);
void readBus(void *para);
void CSensors(void *para);
SemaphoreHandle_t myMutex;

/********************************************************************************************************************************************************************/


/********************************************************************************************************************************************************************/
// Pins Determination

#define Laser 44
//#define Servopin 30
//#define Lighting 44
#define LGripper 38
#define RGripper 40
#define BGripper 36

// Current sensors
#define CS1 A1
#define CS2 A3
#define CS3 A5
#define CS4 A7
#define CS5 A9
#define CS6 A11
#define CS7 A13
#define CS8 A15

/********************************************************************************************************************************************************************/

/********************************************************************************************************************************************************************/
// Communications

MCP2515 mcp2515(53);
struct can_frame msgMotors,msgIMU,msgCS;

#define MOTORS_ID 0xF5
#define LL_ID 0x30
#define IMU_ID 0x68
#define CURRENT_ID 0xB5

/********************************************************************************************************************************************************************/

/********************************************************************************************************************************************************************/
// Buffers and initial values

#define sensitivity 66
#define offsetVoltage 2500

float currentValue[8];
int speeds[8],LL[2];

/********************************************************************************************************************************************************************/


void setup() {
  Serial.begin(115200);
  Serial.setTimeout(30);

  // IMU
  Wire.begin();
    delay(2000);

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }


  // Threading
  myMutex = xSemaphoreCreateBinary();
  
  if (myMutex == NULL)
  {
        Serial.println("mutex can not be created");
  }

  // Communications
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  
//  SCam.attach(Servopin);
  
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

  //Threading
  xTaskCreate(IMU, "Task1", 600, NULL, 0, &TaskHandle_IMU);
  xTaskCreate(readBus, "Task2", 300, NULL, 1, &TaskHandle_FromStation);
//  xTaskCreate(CSensors, "Task3", 600, NULL, 2, &TaskHandle_FromStation);
  xSemaphoreGive(myMutex);
  vTaskStartScheduler();
  
}

void loop() {
  
}

//Task1 the Sent data to station
void IMU(void *para){
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while(1){
    xSemaphoreTake(myMutex, portMAX_DELAY);
    if (1) {
      mpu.update();
//        static uint32_t prev_ms = millis();
//        if (millis() > prev_ms + 10) {
            print_roll_pitch_yaw();
//            prev_ms = millis();
//        }
    mpu.update();
    }
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,5);
  }
}

// Task2 the delivered data from station
void readBus(void *para){
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while (1)
  {
    xSemaphoreTake(myMutex, portMAX_DELAY);
    if (mcp2515.readMessage(&msgMotors) == MCP2515::ERROR_OK) {
      if ( msgMotors.can_id == MOTORS_ID) {
        for(int i= 0 ; i < msgMotors.can_dlc ; i ++)
        {
         speeds[i] = (msgMotors.data[i]*2)-202;
         Serial.print(speeds[i]);
         Serial.print(" "); 
        }
        Serial.println("");
        
//         TFR.writeMicroseconds(speeds[0]+1500);
//         TFL.writeMicroseconds(speeds[1]+1500);
//         TBR.writeMicroseconds(speeds[2]+1500);
//         TBL.writeMicroseconds(speeds[3]+1500);
//
//         BFR.writeMicroseconds(speeds[4]+1500);
//         BFL.writeMicroseconds(speeds[5]+1500);
//         BBR.writeMicroseconds(speeds[6]+1500);
//         BBL.writeMicroseconds(speeds[7]+1500);
          
      }

      else if (msgMotors.can_id == LL_ID) {// msgLL.can_id == LL_ID
        for(int i= 0 ; i < msgMotors.can_dlc ; i ++)
        {
          LL[i] = msgMotors.data[i];
          Serial.print((char)LL[i]);
          Serial.print("");
        }
          Serial.println("");
          if(LL[0]&0x01){ //Laser
            digitalWrite(Laser,1);     // Laser On
            Serial.println("laser Open");
          }
          else if((LL[0]&0x01)==0){
            digitalWrite(Laser,0);     // Laser Off
            Serial.println("laser Closed");
          }
          
          if(LL[0]&0x02){ 
            digitalWrite(LGripper,1);     // Left Gripper On
            Serial.println("Left Gripper Open");
          }
          else if((LL[0]&0x02)==0){
            digitalWrite(LGripper,0);     // Left Gripper Closed
            Serial.println("Left Gripper Closed");
          }
          if(LL[0]&0x04){ //RGipper
            digitalWrite(RGripper,1);     // Right Gripper Open
            Serial.println("Right Gripper Open");
          }
          else if((LL[0]&0x04)==0){
            digitalWrite(RGripper,0);     // Right Gripper Closed
            Serial.println("Right Gripper Closed");
          }
          if(LL[0]&0x08){ //BGripper
            digitalWrite(BGripper,1);     // Back Gripper Open
            Serial.println("Back Gripper Open");
          }
          else if((LL[0]&0x08)==0){
            digitalWrite(BGripper,0);     // Back Gripper Closed
            Serial.println("Back Gripper Closed");
          }
          
//          if((LL[0]&0x1C) == 0)
//          {
//            SCam.write(70);
//          }
//          else if(((LL[0]&0x1C)>>2) == 1)
//          {
//            SCam.write(90);
//          }
//          else if(((LL[0]&0x1C)>>2) == 2)
//          {
//            SCam.write(120);
//          }
//          else if(((LL[0]&0x1C)>>2) == 3)
//          {
//            SCam.write(140);
//          }
//          else if(((LL[0]&0x1C)) == 4)
//          {
//            SCam.write(160);
//          }
        }
    }
    
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,10);
  }
}

void CSensors(void *para){
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while (1)
  {
    currentValue[0] = ( ( ( ( analogRead(CS1) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[1] = ( ( ( ( analogRead(CS2) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[2] = ( ( ( ( analogRead(CS3) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[3] = ( ( ( ( analogRead(CS4) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[4] = ( ( ( ( analogRead(CS5) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[5] = ( ( ( ( analogRead(CS6) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[6] = ( ( ( ( analogRead(CS7) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);
    currentValue[7] = ( ( ( ( analogRead(CS8) / 1024.0 ) * 5000 ) - offsetVoltage ) / sensitivity);

    msgCS.can_id  = CURRENT_ID;
    msgCS.can_dlc =  8;
    for(int i = 0; i < 8; i++){
      msgCS.data[i] = (int) (currentValue[i] * 10);
      Serial.print("Current ");
      Serial.print(i);
      Serial.print(currentValue[i]);
      Serial.print("\t");
      Serial.println(msgCS.data[i]);
    }
    Serial.println(" ");
    mcp2515.sendMessage(&msgCS);
    
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,100);
  }
}

void print_roll_pitch_yaw() {
     int yaw=mpu.getYaw(),pitch=mpu.getPitch(),roll =mpu.getRoll();
     msgIMU.can_id  = IMU_ID;
     msgIMU.can_dlc =  4;
     msgIMU.data[0] = (unsigned char)(yaw+180) & 0xFF;
     msgIMU.data[1] = (unsigned char)(pitch+180) & 0xFF;
     msgIMU.data[2] = (unsigned char)(roll+180) & 0xFF;
     msgIMU.data[3] = (unsigned char)(((unsigned char)((yaw+180) >> 8)) | ((unsigned char)(((pitch+180) >> 8)<<1)) | ((unsigned char)(((roll+180) >> 8)<<2)));
     mcp2515.sendMessage(&msgIMU);
//     Serial.print("Yaw, Pitch, Roll: ");
//     Serial.print(yaw, DEC);
//     Serial.print(", ");
//     Serial.print(pitch, DEC);
//     Serial.print(", ");
//     Serial.println(roll, DEC);
}
