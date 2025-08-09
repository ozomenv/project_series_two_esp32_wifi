#pragma once

class Voltage {
public:
  float tempVoltageIgnition = 0;
  float tempVoltageBacklight = 0;
  float prevVoltageBacklight = 0;
  unsigned long lastTimeUpdateVoltage = 0;
  uint8_t tempVoltageIgnitionStatus = 0;
  uint8_t tempVoltageBacklightChangeStatus = 0;

  void init() {
    refreshVoltage();
  }

  void refresh() {
    if(millis() - lastTimeUpdateVoltage > 1000) {
      refreshVoltage();
    }
  }

  void refreshVoltage() {
    tempVoltageIgnition = (((analogRead( 10) * 3.3) / 4095.0) * 11.0);
    tempVoltageBacklight = (((analogRead( 9) * 3.3) / 4095.0) * 11.0);
    if (tempVoltageIgnitionStatus == 0 && tempVoltageIgnition > 8) {
      tempVoltageIgnitionStatus = 1;
      tempVoltageBacklightChangeStatus = 1;
    } else if (tempVoltageIgnitionStatus == 1 && tempVoltageIgnition < 8) {
      tempVoltageIgnitionStatus = 2;
      ledcWrite(1, 0);
    }

    if (tempVoltageIgnitionStatus == 1 && tempVoltageBacklightChangeStatus == 0) {
      if ((prevVoltageBacklight < 8.0 && tempVoltageBacklight >= 8.0) || (prevVoltageBacklight > 8.0 && tempVoltageBacklight <= 8.0)){
        tempVoltageBacklightChangeStatus = 1;
      }
    }

    prevVoltageBacklight = tempVoltageBacklight;
  }

  float getVoltageIgnition() const {
    return tempVoltageIgnition;
  }

  uint8_t getVoltageIgnitionStatus() const {
    return tempVoltageIgnitionStatus;
  }

  uint8_t setVoltageBacklightChangeStatus(const uint8_t s) {
    tempVoltageBacklightChangeStatus = s;
  }

  uint8_t getVoltageBacklightChangeStatus() {
    if (tempVoltageBacklightChangeStatus == 1) {
      tempVoltageBacklightChangeStatus = 0;
      return 1;
    }
    return 0;
  }

  bool isBacklightOn() const {
    if (tempVoltageBacklight > 8) {
      return true;
    }
    return false;
  }

  void setVoltageIgnitionStatus(const uint8_t s) {
    tempVoltageIgnitionStatus = s;
  }
};
