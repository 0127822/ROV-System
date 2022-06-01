#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <SPI.h>
#include <mcp2515.h>
void readSerial(void *para);
void sendBus(void *para);
void writeSerial(void *para);
void readBus(void *para);
bool flag = false ;
struct can_frame canMsg1;
struct can_frame IMU;
String info;
char imu[3];

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;
SemaphoreHandle_t myMutex;
SemaphoreHandle_t myMutex2;

#define IMU_ID 0x0A6
#define CURRENT_ID 0xB5
#define MOTORS_ID 0xF5

MCP2515 mcp2515(10);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   Serial.setTimeout(50);
   mcp2515.reset();
   mcp2515.setBitrate(CAN_1000KBPS);
   mcp2515.setNormalMode();
   
   myMutex = xSemaphoreCreateBinary();

  myMutex2 = xSemaphoreCreateBinary();
  
  if (myMutex2 == NULL)
  {
        Serial.println("mutex can not be created");
  }
  
  if (myMutex == NULL)
  {
        Serial.println("mutex can not be created");
  }
  xTaskCreate(readSerial, "Task1", 100, NULL, 2, &TaskHandle_1);
  xTaskCreate(sendBus, "Task2", 100, NULL, 1, &TaskHandle_2);

  xTaskCreate(writeSerial, "Task3", 100, NULL, 1, &TaskHandle_3);
  xTaskCreate(readBus, "Task4", 100, NULL, 2, &TaskHandle_4);

  xSemaphoreGive(myMutex2);
  xSemaphoreGive(myMutex);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void readSerial(void *para)
{
  (void)para;
  while (1)
  { xSemaphoreTake(myMutex2, portMAX_DELAY);
//      Serial.println("task1");

    if (Serial.available() > 0)
    {
      flag = true ;
      info = Serial.readStringUntil('\n');
    }

      
      xSemaphoreGive(myMutex2);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}




void sendBus(void *para)
{
  (void)para;
  while (1)
  {
    xSemaphoreTake(myMutex2, portMAX_DELAY);
//    Serial.println("task2");

    if (flag)
    {
      canMsg1.can_id  = IMU_ID;
      canMsg1.can_dlc =  8;
      canMsg1.data[0] = info[0];
      canMsg1.data[1] = info[1];
      canMsg1.data[2] = info[2];
      canMsg1.data[3] = info[3];
      canMsg1.data[4] = info[4];
      canMsg1.data[5] = info[5];
      canMsg1.data[6] = info[6];
      canMsg1.data[7] = info[7];
      mcp2515.sendMessage(&canMsg1);
      
      flag = false ;
    }
    

    
    xSemaphoreGive(myMutex2);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}


void readBus(void *para)
{
  (void)para;
  while (1)
  {
    
    xSemaphoreTake(myMutex, portMAX_DELAY);
//    Serial.println("task3");

    if (mcp2515.readMessage(&IMU) == MCP2515::ERROR_OK) {
      if (IMU.can_id == IMU_ID) {
          imu[0] = map(IMU.data[0],0,255,-127,127);
          imu[1] = map(IMU.data[1],0,255,-127,127);
          imu[2] = map(IMU.data[2],0,255,-127,127);
      }
    }
    
    
    xSemaphoreGive(myMutex);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}



void writeSerial(void *para)
{
  (void)para;
  while (1)
  { 
    
    xSemaphoreTake(myMutex, portMAX_DELAY);
//    Serial.println("task4");
  
    Serial.print(imu[0]);
    Serial.print(imu[1]);
    Serial.print(imu[2]);
  
    
    xSemaphoreGive(myMutex);
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
