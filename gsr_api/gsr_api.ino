// Watch video here: https://www.youtube.com/watch?v=O5Ye5xJF44c

/* 
GSR connection pins to Arduino microcontroller

Arduino           GSR

GND               GND
5V                VCC
A2                SIG

D13             RED LED

*/

/*
 GSR, standing for galvanic skin response, is a method of 
 measuring the electrical conductance of the skin. Strong 
 emotion can cause stimulus to your sympathetic nervous 
 system, resulting more sweat being secreted by the sweat 
 glands. Grove – GSR allows you to spot such strong emotions 
 by simple attaching two electrodes to two fingers on one hand,
 an interesting gear to create emotion related projects, like 
 sleep quality monitor. http://www.seeedstudio.com/wiki/Grove_-_GSR_Sensor
 */

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <Arduino_JSON.h>

// WiFi
#define WIFI_SSID "Pranav"
#define WIFI_PASS "123456789"

// WebServer
ESP8266WebServer server(80);

// WiFi Client
WiFiClient client;

// const int LED = 13;
const int GSR= A0;
int sensorValue = 0;
int gsrAvg = 0;

void handleRoot() {
  String s = "<h1>Hello, World</h1>";
  server.send(200, "text/html", s);
}

void handleGetGsr() {
  JSONVar jv;
  jv["gsrAvg"] = gsrAvg;
  String jsonStr = JSON.stringify(jv);
  server.send(200, "application/json", jsonStr);
}

void setup()
{
  Serial.begin(9600);

  // Connect to WiFi
  Serial.print("\n\n\nConnecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(50);
  }
  Serial.println("OK!\n");
  Serial.print("Successfully connected to: ");
  Serial.println(WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Handling server
  server.on("/", handleRoot);
  server.on("/getgsr", handleGetGsr);
  server.begin();
  Serial.println("Web server started");
}

void loop()
{
  server.handleClient();
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(100);
  }
  gsrAvg = sum / 10;
  Serial.print("GSR Average: ");
  Serial.println(gsrAvg);
//  int humanResistance = ((1024 + 2*gsrAvg) * 10000) / (516 - gsrAvg);
//  Serial.print("Human Resistance: ");
//  Serial.println(humanResistance);
}
