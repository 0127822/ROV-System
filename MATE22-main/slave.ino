#include <SPI.h>
#include <mcp2515.h>
#include <Wire.h>

int n = 0;
volatile bool interrupt = false;
struct can_frame frame;
int send_msg =0;

void irqHandler() {
    interrupt = true;
}

struct can_frame canMsg1;
struct can_frame canMsg_rec;

MCP2515 mcp2515(10);
void setup()
{
  Wire.setClock(10000);
  Wire.begin(0x11);
  
  Serial.begin(9600); 
  delay(1000);  
               
  Wire.onReceive(receiveEvents);
  attachInterrupt(0, irqHandler, FALLING);

  canMsg1.can_id  = 0x0A6;
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x8E;
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
}

void loop(){
   if (interrupt) {
        interrupt = false;
        uint8_t irq = mcp2515.getInterrupts();
        if (irq & MCP2515::CANINTF_RX0IF) {
            if (mcp2515.readMessage(MCP2515::RXB0, &frame) == MCP2515::ERROR_OK) {
                // frame contains received from RXB0 message
                    Serial.print(frame.can_id, HEX); // print ID
                    Serial.print(" "); 
                    
                    for (int i = 0; i<frame.can_dlc; i++)  {  // print the data
                      Serial.print(frame.data[i],HEX);
                      Serial.print(" ");
                    }

                     Serial.println();      
            }
            }
        
        if (irq & MCP2515::CANINTF_RX1IF) {
            if (mcp2515.readMessage(MCP2515::RXB1, &frame) == MCP2515::ERROR_OK) {
               Serial.print(frame.can_id, HEX); // print ID
                    Serial.print(" "); 
                    for (int i = 0; i<frame.can_dlc; i++)  {  // print the data
                      Serial.print(frame.data[i],HEX);
                      Serial.print(" ");
                    }
                     Serial.println();      
                // frame contains received from RXB1 message
            }
        }
    }

    if (send_msg){
      send_msg = 0;
      n = Wire.read();
      canMsg1.data[0]= n;
      n = Wire.read();
      canMsg1.data[1]= n;
      n = Wire.read();
      canMsg1.data[2]= n;
      Serial.print(canMsg1.data[0]);
      Serial.print(" ");
      Serial.print(canMsg1.data[1]);
      Serial.print(" ");
      Serial.println(canMsg1.data[2]);
      mcp2515.sendMessage(&canMsg1);
    }
  }


void receiveEvents(int numBytes)
{  
  send_msg = 1;
}
