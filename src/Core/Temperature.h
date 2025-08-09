#pragma once
class Temperature {
public:
  int temperatureOil = 0;
  int temperatureWater = 0;
  int temperatureAir = 0;
  unsigned long lastTimeUpdateTemperature = 0;

  void init() {
    refreshTemperature();
  }

  void refresh() {
    if(millis() - lastTimeUpdateTemperature > 1000) {
      refreshTemperature();
      lastTimeUpdateTemperature = millis();
    }
  }

  void refreshTemperature() {
    temperatureOil = calculateTemperatureOil();
    temperatureWater = calculateTemperatureWater();
    temperatureAir = calculateTemperatureAir();
  }

  static int calculateTemperatureOil() {
    int analogValue = analogRead(3);
    float voltage = analogValue * 5.0 / 1023.0;

    float resistance = 10000.0 * (5.0 / voltage - 1.0);

    float temperature = 1.0 / (1.0 / (25.0 + 273.15) + log(resistance / 10000.0) / 3950.0);
    temperature -= 273.15;
    return static_cast<int>(temperature);
  }

  static int calculateTemperatureWater() {
    int analogValue = analogRead(8);
    float voltage = analogValue * 5.0 / 1023.0;

    float resistance = 10000.0 * (5.0 / voltage - 1.0);

    float temperature = 1.0 / (1.0 / (25.0 + 273.15) + log(resistance / 10000.0) / 3950.0);
    temperature -= 273.15;
    return static_cast<int>(temperature);
  }

  int calculateTemperatureAir() {
    int analogValue = analogRead(18);
    float voltage = analogValue * 5.0 / 1023.0;

    float resistance = 10000.0 * (5.0 / voltage - 1.0);

    float temperature = 1.0 / (1.0 / (25.0 + 273.15) + log(resistance / 10000.0) / 3950.0);
    temperature -= 273.15;
    return static_cast<int>(temperature);
  }

  int getTemperatureOil() {
    if (temperatureOil <= 199) {
      return temperatureOil;
    }
    return 199;
  }

  int getTemperatureWater() {
    if (temperatureWater <= 199) {
      return temperatureWater;
    }
    return 199;
  }

  int getTemperatureAir() {
    if (temperatureAir <= 199) {
      return temperatureAir;
    }
    return 199;
  }
};
