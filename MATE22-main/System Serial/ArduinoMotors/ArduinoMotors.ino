#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SPI.h>
#include <mcp2515.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include<Servo.h>
#include <Wire.h>


Servo BFR;
Servo BFL;
Servo BBR;
Servo BBL;
Servo five;
Servo six;
Servo seven;
Servo eight;


TaskHandle_t TaskHandle_1;
//TaskHandle_t TaskHandle_2;


SemaphoreHandle_t myMutex;

void readBus( void *para );
//void sendBus( void *para );

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define MOTORS_ID 0xF5

MCP2515 mcp2515(10);
struct can_frame msgMotors;
struct can_frame msgIMU;
unsigned char myData[6];
unsigned char dbuffer[6];
int speeds[8];

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void displaySensorDetails(void)
{
  sensor_t sensor;
  bno.getSensor(&sensor);

  delay(500);
}



void displaySensorStatus(void)
{
  /* Get the system status values (mostly for debugging purposes) */
  uint8_t system_status, self_test_results, system_error;
  system_status = self_test_results = system_error = 0;
  bno.getSystemStatus(&system_status, &self_test_results, &system_error);

  /* Display the results in the Serial Monitor */
  Serial.println("");
  Serial.print("System Status: 0x");
  Serial.println(system_status, HEX);
  Serial.print("Self Test:     0x");
  Serial.println(self_test_results, HEX);
  Serial.print("System Error:  0x");
  Serial.println(system_error, HEX);
  Serial.println("");

}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(30);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();



  BFR.attach(2);// attach BFR to pin D2 
  BFL.attach(3);
  BBR.attach(4);
  BBL.attach(5);

  five.attach(6);
  six.attach(7);
  seven.attach(8);
  eight.attach(9);



  BFR.writeMicroseconds(1500);
  BFL.writeMicroseconds(1500);  
  BBR.writeMicroseconds(1500);  
  BBL.writeMicroseconds(1500);
  five.writeMicroseconds(1500);
  six.writeMicroseconds(1500);  
  seven.writeMicroseconds(1500);  
  eight.writeMicroseconds(1500);

  delay(7000); 

  
  myMutex = xSemaphoreCreateBinary();

  
  if (myMutex == NULL)
  {
        Serial.println("mutex can not be created");
  }

  xTaskCreate(readBus, "Task1", 200, NULL, 7, &TaskHandle_1);
//  xTaskCreate(sendBus, "Task2", 200, NULL, 1, &TaskHandle_2);

  
  xSemaphoreGive(myMutex);

  

//  if(!bno.begin())
//  {
//   
//    /* There was a problem detecting the BNO055 ... check your connections */
//    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }

//  delay(1000); 

  /* Display some basic information on this sensor */
//  displaySensorDetails();

  /* Optional: Display current status */
//  displaySensorStatus();

//  bno.setExtCrystalUse(true);
}

void loop() {
  // put your main code here, to run repeatedly:
}


void readBus(void *para)
{
  (void)para;
  TickType_t wait = xTaskGetTickCount();
  while (1)
  {
//    Serial.println("Task1");
    xSemaphoreTake(myMutex, portMAX_DELAY);
    

    if (mcp2515.readMessage(&msgMotors) == MCP2515::ERROR_OK) {
      if ( msgMotors.can_id == MOTORS_ID) {
        for(int i= 0 ; i < msgMotors.can_dlc ; i ++)
        {
         speeds[i] = (msgMotors.data[i]*2)-202;
         Serial.print(speeds[i]);
         Serial.print(" ");

         BFR.writeMicroseconds(speeds[0]+1500);
         BFL.writeMicroseconds(speeds[1]+1500);
         BBR.writeMicroseconds(speeds[2]+1500);
         BBL.writeMicroseconds(speeds[3]+1500);

         five.writeMicroseconds(speeds[4]+1500);
         six.writeMicroseconds(speeds[5]+1500);
         seven.writeMicroseconds(speeds[6]+1500);
         eight.writeMicroseconds(speeds[7]+1500);
         
        }
        Serial.println("");
          
      }
    }
    
    
    xSemaphoreGive(myMutex);
    vTaskDelayUntil(&wait,1);
  }
}





//void sendBus(void *para)
//{
//  (void)para;
//  TickType_t wait = xTaskGetTickCount();
//  while (1)
//  {
//    xSemaphoreTake(myMutex, portMAX_DELAY);
//    
//
//  sensors_event_t event;
//  bno.getEvent(&event);
//
////  Serial.print("X: ");
////  Serial.print(event.orientation.x, 4);
////  Serial.print("\tY: ");
////  Serial.print(event.orientation.y, 4);
////  Serial.print("\tZ: ");
////  Serial.print(event.orientation.z, 4);
////  Serial.println("");
//
//  myData[0] = (short int)event.orientation.x & 0xFF; //yaw
//  myData[1] = ((short int)event.orientation.y+180) &0xFF;//pitch
//  myData[2] = ((short int)event.orientation.z+180) & 0xFF;//pitch
//  myData[3] = ((short int)event.orientation.x >> 8) | (((short int)event.orientation.x >> 8)<<1) | (((short int)event.orientation.x >> 8)<<2); //yaw
//
//
//  
//
//  
//
//   if((myData[0] != dbuffer[0]) ||(myData[1] != dbuffer[1]) || (myData[2] != dbuffer[2]) || (myData[3] != dbuffer[3]) || (myData[4] != dbuffer[4]) || (myData[5] != dbuffer[5])){
//       for(int i=0;i<4;i++)
//       {
//          dbuffer[i] = myData[i];                        
//       }
//  Serial.print("X: ");
//  Serial.print(event.orientation.x, 4);
//  Serial.print("\tY: ");
//  Serial.print(event.orientation.y, 4);
//  Serial.print("\tZ: ");
//  Serial.print(event.orientation.z, 4);
//      msgIMU.can_id  = 0x0A6;
//      msgIMU.can_dlc = 4;
//      for(int i = 0 ; i < 4 ; i ++)
//      {
//        Serial.print(myData[i]);
//        msgIMU.data[i] = myData[i];
//        Serial.print(" ");                       
//      }
//        Serial.println(""); 
////        Serial.println("Task2"); 
//        mcp2515.sendMessage(&msgIMU);
//
//}    
//
//    
//    xSemaphoreGive(myMutex);
//    vTaskDelayUntil(&wait,20);
//  }
//}
