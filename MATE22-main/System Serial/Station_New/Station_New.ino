#include <Arduino_FreeRTOS.h>
#include <SPI.h>
#include <mcp2515.h>
#include <semphr.h>


String pitch, yaw , roll , total ;
void readSerial(void *para);
void sendBus(unsigned char n);
void writeSerial();
void readBus(void *para);
struct can_frame canMsg1;
struct can_frame IMU;
String info;
unsigned char imu[6];
String imu_buff = "";
int x[3];
#define IMU_ID 0x0A6
#define CURRENT_ID 0xB5
#define MOTORS_ID 0xF5

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

SemaphoreHandle_t myMutex;

MCP2515 mcp2515(10);
String msg;
String info_buff;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(30);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();

  myMutex = xSemaphoreCreateBinary();

  
  if (myMutex == NULL)
  {
        Serial.println("mutex can not be created");
  }

  xTaskCreate(readSerial, "Task1", 200, NULL, 7, &TaskHandle_1);
  xTaskCreate(readBus, "Task2", 200, NULL, 1, &TaskHandle_2);

  xSemaphoreGive(myMutex);
    vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}


void readSerial(void *para)
{
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while (1)
  {
    xSemaphoreTake(myMutex, portMAX_DELAY);
    if(Serial.available() > 0)
    {
      info = Serial.readStringUntil('\0');
//      Serial.println("Time Step");
      Serial.flush();
      if(info != info_buff)
      {
        info_buff =info;
          sendBus(0);
      }
    }
    
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,1);
  }
}

void writeSerial()
{
  Serial.write('s');
  Serial.write(imu[0]);
  //Serial.write('\n');
  Serial.write(imu[1]);
  //Serial.write('\n');
  Serial.write(imu[2]);
  //Serial.write('\n');
  Serial.write(imu[3]);
  //Serial.write('\n');
  Serial.write('a');
  Serial.flush();
}


void readBus(void *para)
{
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while (1)
  {
    
    xSemaphoreTake(myMutex, portMAX_DELAY);
    if (mcp2515.readMessage(&IMU) == MCP2515::ERROR_OK) {
    
      if (IMU.can_id == IMU_ID) {
        for (int i = 0; i < IMU.can_dlc; i++)  { // print the data
//          Serial.print(IMU.data[i]);
//          Serial.print(" ");    
          imu[i] = IMU.data[i];
        }
//          Serial.println("");
          writeSerial();
      }
    }
    
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,20);
  }
}


void sendBus(unsigned char n)
{
  if(n == 0){
      canMsg1.can_id  = MOTORS_ID;
      canMsg1.can_dlc =  8;
      canMsg1.data[0] = info[0];
      canMsg1.data[1] = info[1];
      canMsg1.data[2] = info[2];
      canMsg1.data[3] = info[3];
      canMsg1.data[4] = info[4];
      canMsg1.data[5] = info[5];
      canMsg1.data[6] = info[6];
      canMsg1.data[7] = info[7];
      Serial.println(canMsg1.data[0]);
      mcp2515.sendMessage(&canMsg1);
  }
}
