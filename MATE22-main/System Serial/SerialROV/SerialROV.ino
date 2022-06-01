#include <Servo.h>
//#1--tbr 3  2--tfl5    3--tfr 2   4--bbl7    5--bfr 9    6--bfl 6   7--bbr 8  8--tbl 4
#define tfr 2
#define tfl 5
#define tbr 3
#define tbl 4
#define bfr 9
#define bfl 6
#define bbr 8
#define bbl 7

Servo TFR;
Servo TFL;
Servo TBR;
Servo TBL;
Servo BFR;
Servo BFL;
Servo BBR;
Servo BBL;

String info;
String info_buff = "";
int speeds[8];
char LL[2];


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LED_BUILTIN,OUTPUT);
  Serial.setTimeout(30);

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
  // put your main code here, to run repeatedly:
     if(Serial.available() > 0)
    {
      info = Serial.readStringUntil('\0');
      Serial.flush();
      if(info != info_buff)
      {
        for(int i = 0 ; i < 8 ; i ++)
        {
          speeds[i] = ((int)info[i]*2);
          Serial.print(speeds[i]);
          Serial.print("");    
        }

        for(int i = 8 ; i < 10 ; i++)
        {
          LL[i-8] = info[i];
        }
        if(LL[0] == 'o')
        {
          digitalWrite(LED_BUILTIN,HIGH);
        }
        else if(LL[0] == 'f')
        {
          digitalWrite(LED_BUILTIN,LOW);
        }
        if(LL[1] == 'o')
        {
          digitalWrite(LED_BUILTIN,HIGH);
        }
        else if(LL[1] == 'f')
        {
          digitalWrite(LED_BUILTIN,LOW);
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
      
        info_buff =info;
      }

     }
}
