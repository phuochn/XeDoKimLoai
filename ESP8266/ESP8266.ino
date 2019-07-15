#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
void KiemTraKimLoai(void);
const char* ssid = "WiFi_ESP8266_NODEMCU";
ESP8266WebServer server(80);
String data, data_old;
const int buttonPin = D0;     
const int ledPin =  D4; 
int PHKimLoai = LOW;
void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  // Connecting WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid); //WiFi.softAP(ssid, password); nếu có mật khẩu 
  // Starting WEB-server
  server.on("/",HTTP_handleRoot );
  server.onNotFound(HTTP_handleRoot);
  server.begin();  
}

void loop() 
{
    server.handleClient();
    KiemTraKimLoai();
    delay(50);
}
/****************************************************************/
void KiemTraKimLoai(void)
{
    PHKimLoai = digitalRead(buttonPin);
    if (PHKimLoai == HIGH) 
    {
        digitalWrite(ledPin, LOW);
        server.send(200, "text/html", "1");
    } 
    else if(PHKimLoai == LOW) 
    {
        digitalWrite(ledPin, HIGH);
        server.send ( 200, "text/html", "0" );
    }
}
/****************************************************************/
void HTTP_handleRoot(void) 
{
    data = server.arg("kitu");
    if(data != data_old)
    {
        data_old = data;
        Serial.println(data);
    }
}
