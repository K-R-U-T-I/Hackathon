#include <SoftwareSerial.h>
SoftwareSerial Inter(3,2);
#include "dht.h"
#define ldr_in A0  //analog
#define moist_in A1  //analog
#define dht11_in A2  //analog
#define pir_in 4 //digital
int ldr_out, moist_out, pir_out,humi,temp;
String data_of_all_sensors,str1;


dht DHT;
void setup(){

  pinMode(pir_in,INPUT);
  Serial.begin(9600);
  Inter.begin(4800);
  pinMode(3,INPUT);
  pinMode(2,OUTPUT);
  delay(500);//Delay to let system boot
}//end "setup()"
 
void loop(){
  //Start of Program 
    //LDR Reading
   ldr_out =  analogRead(ldr_in);
  
    //Moisture Reading
   moist_out = analogRead(moist_in);
   moist_out = map(moist_out,1023,0,0,100); //convert to percentage

    //PIR Reading
   pir_out = digitalRead(pir_in);

    //DHT11 reading
   DHT.read11(dht11_in);
   humi = DHT.humidity;
   temp = DHT.temperature;

   data_of_all_sensors = String("SL=") + String(ldr_out) + String("&Mt=") + String(moist_out) + String("&Hm=") + String(humi) + String("&Tmp=") + String(temp) + String("&PIR=") + String(pir_out) + "\n";
   Serial.println(data_of_all_sensors);
   Inter.println(data_of_all_sensors);
   delay(2000);

  while(Inter.available()>0)
  {
      str1 = Inter.readString();
      Serial.println(str1);
      if(str1.charAt(0) == '1')
      {
          digitalWrite(8,HIGH);
          Serial.println("LED is ON");
      }
      else if(str1.charAt(0) == ':' )
      {
          digitalWrite(8,LOW);
          Serial.println("LED is OFF");
      
      }
      if(str1.charAt(1) == '0')
      {
          digitalWrite(13,HIGH);//13 will be HIGH 
          digitalWrite(12,LOW);
          delay(500);
          /*digitalWrite(12,LOW);
          digitalWrite(13,LOW);*/
          Serial.println("Motor opens shade");
          
      }
       else if(str1.charAt(1) == '1')
      {
         digitalWrite(12,HIGH); //12 will be high white will be 12
         digitalWrite(13,LOW);
         delay(500);
         /*digitalWrite(12,LOW);
         digitalWrite(13,LOW);*/
         Serial.println("Motor closes shade");
      }

     
  }

}// end loop() 
