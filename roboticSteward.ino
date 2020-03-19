#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char * ssid = "aditya";
const char * pswd = "qujjhzxn";

WiFiClient c;

void setup() 
{
       Serial.begin(115200);
       delay(10);
               
       Serial.println("Connecting to ");
       Serial.println(ssid); 
      
       WiFi.begin(ssid, pswd); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
      pinMode(D0, OUTPUT);
      pinMode(D1, OUTPUT);

      
}

void loop()
{
  if(WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin("http://jsonplaceholder.typicode.com/users/1");
    int httpCode = http.GET();

    if(httpCode > 0)
    {
     
      DynamicJsonDocument doc(2048);
      String payload = http.getString();
      Serial.println(payload);
      digitalWrite(D0, LOW);
      delay(1000);
      digitalWrite(D0, HIGH);
      DeserializationError err = deserializeJson(doc, payload);

      if(err)
      {
        Serial.println("Deserialization failed!!");
        Serial.println(err.c_str());
      }


      
      String name = doc["email"];
      Serial.println(name);

  }
  delay(30000);
}}
