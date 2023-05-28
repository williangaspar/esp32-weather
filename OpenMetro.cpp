#include "OpenMetro.h"

namespace OpenMetro {

CityResponse::CityResponse() {
  name = "";
  country = "";
  admin1 = "";
  latitude = 0;
  longitude = 0;
};

String Request::getCityURL(String name, int8_t count) {
  String countStr = String(count);
  return "https://geocoding-api.open-meteo.com/v1/search?name=" + name + "&count=" + countStr + format + language;
};

String Request::getCityURL(String name) {
  return Request::getCityURL(name, 1);
};

String Request::getWeatherURL(float latitude, float longitude) {
  String latitudeStr = String(latitude);
  String longitudeStr = String(longitude);

  return "https://api.open-meteo.com/v1/forecast?latitude=" + latitudeStr + "&longitude=" +
         longitudeStr + "&current_weather=true" + format + language;
};

}  // namespace OpenMetro