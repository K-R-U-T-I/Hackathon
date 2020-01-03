#include "dht.h"
#define ldr_in A0  //analog
#define moist_in A1  //analog
#define dht11_in A2  //analog
#define pir_in 4 //digital
int ldr_out, moist_out, pir_out;

dht DHT;
void setup(){

  pinMode(pir_in,INPUT);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
}//end "setup()"
 
void loop(){
  //Start of Program 
    //LDR Reading
   ldr_out =  analogRead(ldr_in);
   Serial.print("Sunlight : ");           
   Serial.print(ldr_out); 

    //Moisture Reading
   moist_out = analogRead(moist_in);
   moist_out = map(moist_out,1023,0,0,100); //convert to percentage
   Serial.print("    Mositure : ");
   Serial.print(moist_out);
   Serial.println("%");

    //PIR Reading
   pir_out = digitalRead(pir_in);
   Serial.print("    PIR Security : ");
   Serial.print(pir_out);

    //DHT11 reading
   DHT.read11(dht11_in);
   Serial.print("    Current humidity : ");
   Serial.print(DHT.humidity);
   Serial.print("%");
   Serial.print("    Temperature : ");
   Serial.print(DHT.temperature); 
   Serial.println("C  ");
   delay(2500);

   

}// end loop() 
