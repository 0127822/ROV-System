#include <Arduino_FreeRTOS.h>
#include <SPI.h>
#include <mcp2515.h>
#include <semphr.h>

/********************************************************************************************************************************************************************/
// Threading

TaskHandle_t TaskHandle_FromStation;
TaskHandle_t TaskHandle_FromROV;

SemaphoreHandle_t myMutex;

void readSerial(void *para);
void sendBus(unsigned char n);
void writeSerial();
void readBus(void *para);

/********************************************************************************************************************************************************************/
// Communications

struct can_frame canMsg1;//Motors Message
struct can_frame canMsg2;//Laser & Lighting Message
struct can_frame Sensors;

#define IMU_ID 0x68
#define CURRENT_ID 0xB5
#define MOTORS_ID 0xF5
#define LL_ID 0x30
MCP2515 mcp2515(10);


/********************************************************************************************************************************************************************/
// Buffers and Variables

String info;
unsigned char imu[4];
unsigned char Current[8];
String imu_buff = "";
String LL_buff="";
String msg;
String motors_buff;

void setup() {
  // Communications
  Serial.begin(115200);
  Serial.setTimeout(30);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();

  // Threading
  myMutex = xSemaphoreCreateBinary();

  
  if (myMutex == NULL)
  {
        Serial.println("mutex can not be created");
  }

  xTaskCreate(readSerial, "Task1", 200, NULL, 7, &TaskHandle_FromStation);
  xTaskCreate(readBus, "Task2", 200, NULL, 1, &TaskHandle_FromROV);

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
      if(info [0] == '*')
      {
        if(info != motors_buff)
        {
          motors_buff =info;
            sendBus(0);
        }
      }
      if(info [0] == '#')
      {
        if(info != LL_buff)
        {
          LL_buff =info;
            sendBus(1);
        }
      }
    }
    
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,1);
  }
}

void writeSerial(int x)
{
  if(x == 0){
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
  else if(x == 1){
    Serial.write('s');
    Serial.write(Current[0]);
    Serial.write(Current[1]);
    Serial.write(Current[2]);
    Serial.write(Current[3]);
    Serial.write(Current[4]);
    Serial.write(Current[5]);
    Serial.write(Current[6]);
    Serial.write(Current[7]);
    Serial.write('a');
    Serial.flush();
  }
}


void readBus(void *para)
{
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while (1)
  {
    
    xSemaphoreTake(myMutex, portMAX_DELAY);
    if (mcp2515.readMessage(&Sensors) == MCP2515::ERROR_OK) {
    
      if (Sensors.can_id == IMU_ID) {
        for (int i = 0; i < Sensors.can_dlc; i++)  { // print the data
//          Serial.print(IMU.data[i]);
//          Serial.print(" ");    
          imu[i] = Sensors.data[i];
        }
//          Serial.println("");
          writeSerial(0);
      }
      else if(Sensors.can_id == CURRENT_ID){
        for(int i=0; i<Sensors.can_dlc; i++){
          Current[i] = Sensors.data[i];
        }
        writeSerial(1);
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
      canMsg1.data[0] = info[1];
      canMsg1.data[1] = info[2];
      canMsg1.data[2] = info[3];
      canMsg1.data[3] = info[4];
      canMsg1.data[4] = info[5];
      canMsg1.data[5] = info[6];
      canMsg1.data[6] = info[7];
      canMsg1.data[7] = info[8];

//      for(int i = 0 ; i < 8 ; i ++)
//      {
//        Serial.print(canMsg1.data[i]);
//      }
//      Serial.println("");
      ///////////////////////////////////
     // Serial.println("aaaa");
//      Serial.println(canMsg2.data[1]);
      mcp2515.sendMessage(&canMsg1);
     // Serial.println("aaa");
  }
  else if(n == 1)
      {
        canMsg2.can_id = LL_ID;
        canMsg2.can_dlc =  1;   
        canMsg2.data[0] = info[1];
        //Serial.println("llllll");
      
        mcp2515.sendMessage(&canMsg2);
//        Serial.println(canMsg2.can_id,HEX);
//        Serial.println("lll");
      }
}
