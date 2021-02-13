#include "SIM900.h"
#include "GSM.h"
#include <SoftwareSerial.h>
//We don't need the http functions. So we can disable the next line.
//#include "inetGSM.h"
#include "sms.h"
#include "call.h"

//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.

//Simple sketch to check if an incoming call is from an authorized
//number and in this case, send to this number an SMS with the value
//of a digital input.

//We have to create the classes for SMSs and calls.
CallGSM call;
SMSGSM sms;

  int analogPin = A0; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
  int val = 0;  // variable to store the value re

    
char number[20];
byte stat=0;
int value=0;
int pin=1;
char value_str[5];

void setup()
{
     pinMode(pin,INPUT);
     //Serial connection.
     Serial.begin(2400);
     Serial.println("GSM Shield testing.");
     //Start configuration of shield with baudrate.
     //For http uses is raccomanded to use 4800 or slower.
     if (gsm.begin(2400))
          Serial.println("\nstatus=READY");
     else Serial.println("\nstatus=IDLE");

    delay(2);
       pinMode(7,OUTPUT);   //set pin 7 to be an output
    pinMode(8,OUTPUT);    //set pin 8 to be an output
    
};

void loop()
{

  
           val =  analogRead(analogPin);
          delay(2);
          Serial.println(" The analog value: ");
         Serial.println(val);          // debug value
          if(  val > 500 ) {  
            opendoor();
          }
     //Chekcs status of call
     stat=call.CallStatusWithAuth(number,1,10);
     //If the incoming call is from an authorized number`
     //saved on SIM in the positions range from 1 to 3.
     if(stat==CALL_INCOM_VOICE_AUTH) {
          //Hang up the call.
          call.HangUp();
          delay(20);
          opendoor();
     }
     delay(10);
};



void opendoor()
{
   digitalWrite(7,HIGH);  
   delay(30000);
   digitalWrite(7,LOW);  
   delay(10000);
   digitalWrite(8,HIGH);
   delay(30000);
   digitalWrite(8,LOW);
   delay(1000);
}
