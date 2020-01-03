#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
const char* ssid = "i.Uchiha";
const char* password = "1234567890";

const char* host = "www.dweet.io";
const char* thing  = "testJ7";
String thing_content;
HTTPClient http;

SoftwareSerial Inter(D2,D3);

void setup() {
  Serial.begin(9600);
  Inter.begin(4800);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  /*while(!Serial){
    Serial.println("waiting for serial");
  }*/

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(Serial.available()){
     thing_content = Serial.readString();
  }*/
  //thing_content = "Sunlight=28&Moisture=29&CurrentHumidity=40&CurrentTemperature=25&PirSecurity=0";
  

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
        return;
  }
  else{
    Serial.println("connection succeed");
  }
   // We now create a URI for the request
   
   while(Inter.available()>0){
       Serial.println("Reading.........................................................................................................");
       thing_content = Inter.readString();
   }

   Serial.println(thing_content);
  String url = "/dweet/for/";
  url += thing;
  url += "?";
  url += thing_content;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
  /*Serial.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");*/
  /*int timeout = millis() + 5000;
  while (client.available() == 0) {
    if (timeout - millis() < 0) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
   Serial.println("Sent to client");
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print("\nMessage From Client:");
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");*/
  delay(100);
  if (WiFi.status() == WL_CONNECTED)
    { //Check WiFi connection status
    //Declare an object of class HTTPClient
    http.begin("http://dweet.io/get/latest/dweet/for/water_on_off"); //Specify request destination
    int httpCode = http.GET();
    Serial.println(httpCode);
    //Send the request
    if (httpCode > 0)
    {
    
      String payload = http.getString();   //Get the request response payload
      int length = payload.length();
      String substr = String(payload.charAt((length-6))) + String(payload.charAt((length-5)));
      Serial.println(substr);                     //Print the response payload
      Inter.println(substr);
    
    }
    
    http.end();   //Close connection
    
    }
    
    delay(10000); //Send a request every 10 seconds
    //{"this":"succeeded","by":"getting","the":"dweets","with":[{"thing":"water_on_off","created":"2019-03-03T05:36:02.118Z","content":{"out":10}}]}



 
}
