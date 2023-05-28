#ifndef WEATHER_DISPLAY_H
#define WEATHER_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "OpenMetro.h"

namespace WeatherManager {

void startDisplay(Adafruit_SSD1306 &oled, int16_t displayAddres);
void loadWeather();
void setCity(String name, float latitude, float longitude);
void printCity();
void printTemperature();
void printWeather();

}  // namespace WeatherManager

#endif