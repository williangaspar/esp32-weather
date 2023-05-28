#ifndef OPEN_METRO_H
#define OPEN_METRO_H

#include <Arduino.h>
#include <stdint.h>

namespace OpenMetro {

class Request {
 private:
  inline static const String format = "&format=json";
  inline static const String language = "&language=en";

 public:
  static String getCityURL(String name);
  static String getCityURL(String name, int8_t count);
  static String getWeatherURL(float latitude, float longitude);
};

class CityResponse {
 public:
  CityResponse();
  String name;
  String country;
  String admin1;
  float latitude;
  float longitude;
};

}  // namespace OpenMetro

#endif
