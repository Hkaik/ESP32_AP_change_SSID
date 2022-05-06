#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char *ssid = "MyESP32AP";
const char *password = "testpassword";
String ssid_val = "Kevin";
String pw_val = "073862516";
String ssid_state = "";
bool switch_state = HIGH;
 
AsyncWebServer server(80);
 
void AP_mode(){
  WiFi.softAP(ssid, password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("waiting request...");
  
    request->send(200, "text/plain", "message received");
    int paramsNr = request->params();
    ssid_val = request->getParam(0)->name();
    pw_val = request->getParam(1)->name();
    Serial.print("SSID: ");
    Serial.println(ssid_val);
    Serial.print("PassWord: ");
    Serial.println(pw_val);
 
  });

  server.begin();
 }
 

void setup(){
  Serial.begin(115200);
  pinMode(12, INPUT);
 
  Serial.println();
  Serial.println(WiFi.softAPIP());
 
// server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
// request->send(200, "text/plain", "Hello World");
// });

 
 }
void loop(){

  if (digitalRead(12) == switch_state){
    Serial.println("change to AP Mode");
    ssid_state = ssid_val;
    while (ssid_state == ssid_val && digitalRead(12) == switch_state){
    AP_mode();
    Serial.print(ssid_val);
    Serial.print(pw_val);
    delay(3000);
  }
  Serial.println("SSID had changed!!!");
  delay(5000);
  
  }else
  
  {
    Serial.println("change to STA Mode");
    WiFi.begin(ssid_val.c_str(), pw_val.c_str());
    Serial.print("Connecting to WiFi");
 
    while (WiFi.status() != WL_CONNECTED && digitalRead(12) != switch_state){
      Serial.print(".");
      delay(500);
  }
    Serial.println("success connect to Wi-Fi !!! ");
    delay(5000);
    //STA_MODE
  }

  
}

 
