#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "i.Uchiha";
const char* password = "1234567890";
HTTPClient http;
void setup ()
{

Serial.begin(115200);
WiFi.begin(ssid, password);
delay(1000);
Serial.print("Connecting to Access point..");
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(100);

}
delay(100);
Serial.println("connected");

}

void loop() {

if (WiFi.status() == WL_CONNECTED)
{ //Check WiFi connection status
//Declare an object of class HTTPClient
http.begin("http://dweet.io/get/latest/dweet/for/testJ7"); //Specify request destination
int httpCode = http.GET();
Serial.println(httpCode);
//Send the request
if (httpCode > 0)
{

  String payload = http.getString();   //Get the request response payload
  Serial.println(payload);                     //Print the response payload

}

http.end();   //Close connection

}

delay(10000); //Send a request every 10 seconds

}
