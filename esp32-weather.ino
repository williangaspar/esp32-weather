#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <WiFi.h>
#include <Wire.h>
#include <uri/UriBraces.h>

#include <string>

#include "OpenMetro.h"
#include "WeatherManager.h"
#include "html.h"
#include "password.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

WebServer server(80);
HTTPClient http;

unsigned long startTime;
unsigned long currentTime;
const unsigned long period = 60000;

void setup() {
  Serial.begin(9600);

  WeatherManager::startDisplay(oled, 0x3C);

  WiFi.begin(Password::ssid, Password::password, 6);

  oled.print("Connecting");
  oled.display();

  while (WiFi.status() != WL_CONNECTED) {
    oled.print(".");
    oled.display();
    delay(400);
  }

  server.on("/", handleOnConnect);
  server.on(UriBraces("/cities/get/{}"), handleOnGetCities);
  server.on(UriBraces("/cities/set/{}/{}/{}"), handleOnSetCity);
  server.onNotFound(handleOnNotFound);

  server.begin();
  Serial.println("HTTP server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  oled.print("Waiting on ");
  oled.println(WiFi.localIP());
  oled.display();

  startTime = millis();
}

void handleOnConnect() {
  server.send(200, "text/html", HTML::homePage);
}

void handleOnGetCities() {
  String cityName = server.pathArg(0);
  String url = OpenMetro::Request::getCityURL(cityName, 10);

  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String result = http.getString();
    server.send(200, "text/json", result);
  } else {
    server.send(500, "text/plain", "Could not load city");
  }
  http.end();
}

void handleOnSetCity() {
  String name = server.pathArg(0);
  name.replace("%20", " ");
  float latitude = server.pathArg(1).toFloat();
  float longitude = server.pathArg(2).toFloat();

  WeatherManager::setCity(name, latitude, longitude);
  WeatherManager::printWeather();

  server.send(200, "text/html", HTML::allSet);
}

void handleOnNotFound() {
  server.send(404, "text/plain", "Page not found");
}

void loop() {
  server.handleClient();
  currentTime = millis();

  if (currentTime - startTime >= period) {
    Serial.println("Getting new weather");
    startTime = currentTime;
    WeatherManager::printWeather();
  }
}
