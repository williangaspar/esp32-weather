#include "WeatherManager.h"

namespace WeatherManager {

HTTPClient http;
Adafruit_SSD1306 *screen = nullptr;
OpenMetro::CityResponse city;

float temperature = 0;

void startDisplay(Adafruit_SSD1306 &oledDisplay, int16_t displayAddress) {
  screen = &oledDisplay;

  if (!screen->begin(SSD1306_SWITCHCAPVCC, displayAddress)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1)
      ;
  }
  screen->clearDisplay();
  screen->setTextSize(1);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 2);
  screen->println(""); // I added these 2 lines because I'm using a dual color OLED,
  screen->println(""); // and the text does not look good when it is in between the 2 colors
  screen->println("Loading");
  screen->display();
}

void setCity(String name, float latitude, float longitude) {
  city.name = name;
  city.latitude = latitude;
  city.longitude = longitude;
}

void loadWeather() {
  String url = OpenMetro::Request::getWeatherURL(city.latitude,
                                                 city.longitude);
  http.begin(url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    String result = http.getString();
    DynamicJsonDocument doc(2048);

    DeserializationError error = deserializeJson(doc, result);
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
    }

    JsonObject currentWeather = doc["current_weather"];

    temperature = currentWeather["temperature"].as<float>();
  }
  http.end();
}

void printCity() {
  screen->clearDisplay();
  screen->setTextSize(city.name.length() > 10 ? 1 : 2);
  screen->setCursor(0, 2);
  screen->println(city.name);
  screen->display();
}

void printTemperature() {
  screen->setCursor(0, 24);
  screen->setTextSize(3);
  screen->print(temperature);
  screen->print("C");
  screen->display();
}

void printWeather() {
  if (city.name != "") {
    loadWeather();
    printCity();
    printTemperature();
  }
}

}  // namespace WeatherManager