#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>
#include <Arduino_FreeRTOS.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define configUSE_PREEMPTION 1
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

unsigned char myData[6];
unsigned char dbuffer[6];
int speedMotor[8] = {0, 0, 0, 0, 0, 0,0,0};

void IMU(void *para);
void motors(void *para);

int n = 0;
volatile bool interrupt = false;
struct can_frame frame;
int send_msg =0;

void irqHandler() {
    interrupt = true;
}

void receiveEvents(int numBytes)
{  
  //send_msg = 1;
}

struct can_frame canMsg1;
struct can_frame canMsg_rec;

MCP2515 mcp2515(10);

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
void setup() {
  Serial.begin(115200);
  if(!bno.begin())
  {
   
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    //while(1);
  }
  xTaskCreate(IMU, "Task1", 100, NULL, 2, &TaskHandle_1);
  xTaskCreate(motors, "Task2", 100, NULL, 1, &TaskHandle_2);
  Wire.setClock(400000);
  bno.setExtCrystalUse(true);
  Wire.begin();
  
  
               
  //Wire.onReceive(receiveEvents);

  canMsg1.can_id  = 0x0A6;
  canMsg1.can_dlc = 6;
  canMsg1.data[0] = 0x8E;
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();

}

void loop() {

}

void IMU(void *para){
  (void) para;
  Serial.println("yabdany Task1");
  while(1){
    sensors_event_t event;
    bno.getEvent(&event);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
    myData[0] = (short int)event.orientation.x >> 8; //yaw
  myData[1] = (short int)event.orientation.x & 0xFF; //yaw
  myData[2] = ((short int)event.orientation.y+180) >> 8;//pitch
  myData[3] = ((short int)event.orientation.y+180) & 0xFF;//pitch
  myData[4] = ((short int)event.orientation.z+180) >> 8;//roll
  myData[5] = ((short int)event.orientation.z+180) & 0xFF;//roll
//  myData[2] = 100;
  if((myData[0] != dbuffer[0]) ||(myData[1] != dbuffer[1]) || (myData[2] != dbuffer[2]) || (myData[3] != dbuffer[3]) || (myData[4] != dbuffer[4]) || (myData[5] != dbuffer[5])){
              
              for(int i=0;i<6;i++){
                  dbuffer[i] = myData[i];
                  canMsg1.data[i] = myData[i];
              }
  
//      
//      
//      Serial.println("");
//      Serial.print(canMsg1.data[0]);
//      Serial.print(" ");
//      Serial.print(canMsg1.data[1]);
//      Serial.print(" ");
//      Serial.print(canMsg1.data[2]);
//      Serial.print(" ");
//      Serial.print(canMsg1.data[3]);
//      Serial.print(" ");
//      Serial.print(canMsg1.data[4]);
//      Serial.print(" ");
//      Serial.print(canMsg1.data[5]);
      mcp2515.sendMessage(&canMsg1);
  }
    vTaskDelay(50 / portTICK_PERIOD_MS);
}
}

void motors(void *para){
  (void) para;
  Serial.println("yabdany Task2");
  while(1){
            if (mcp2515.readMessage(&frame) == MCP2515::ERROR_OK) {
                    for (int i = 0; i<frame.can_dlc; i++)  {  // print the data
                      
                      speedMotor[i] = (frame.data[i]*2)-202;
                      Serial.print(speedMotor[i],DEC);
                      
                      Serial.print(" ");
                    }

                     Serial.println();      
            }
          vTaskDelay(50 / portTICK_PERIOD_MS);  
  }
}
