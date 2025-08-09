#pragma once
char voltage_tempText[2];
float voltage_voltage = 0.0;
uint8_t voltage_status = 0;

inline char* getIntegerPart(float number) {
  sprintf(voltage_tempText, "%d", static_cast<int>(number));
  return voltage_tempText;
}

char* getFractionalPart(float number) {
  float fraction = number - static_cast<int>(number);
  sprintf(voltage_tempText, "%dv", static_cast<int>(fraction * 10));
  return voltage_tempText;
}

void showProgramVoltage() {
  if ((millis() - settings.getLastTimeUpdate() > 1500 && voltage_voltage != voltage.getVoltageIgnition()) || settings.isReloadDisplay()) {
    settings.setLastTimeUpdate(millis());

    voltage_voltage = voltage.getVoltageIgnition();

    if(voltage_voltage < 13) {
      voltage_status = 0;
    }
    if(voltage_voltage > 13 && voltage_voltage < 15) {
      voltage_status = 1;
    }
    if(voltage_voltage > 14.9) {
      voltage_status = 2;
    }

    display3.clearBuffer();
    if (settings.isTimeFlip()) {
      if (voltage_status == 0) {
        display3.drawXBMP(0, 35, 30, 23, bitmap_icon_battery_bits);
      } else if (voltage_status == 2){
        display3.drawXBMP(0, 35, 20, 19, bitmap_icon_error_bits);
      }
    }

    if (voltage_status == 1) {
       display3.drawXBMP(0, 35, 20, 20, bitmap_icon_ok_bits);
    }
    display3.setFont(separator_for_time_font);
    display3.drawStr(74, 58, {"."});

    display3.setFont(numbers_digital_font);
    display3.drawStr((voltage_voltage < 10) ? 54 : 30, 58, getIntegerPart(voltage_voltage));
    display3.drawStr(86, 58, getFractionalPart(voltage_voltage));

    display3.sendBuffer();
  }
}