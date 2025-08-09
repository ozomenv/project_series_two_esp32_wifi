#pragma once
char tempAir_tempText[2];
int tempAir_temp = 0;

unsigned long tempAir_lastTimeUpdate = millis() - 3100;

void tempAirClear() {
  tempAir_lastTimeUpdate = millis() - 3100;
  tempAir_temp = 0;
}

inline char* getFormatTempAir(int temp) {
  sprintf(tempAir_tempText, "%d", temp);
  return tempAir_tempText;
}

void showTempAir() {
  if (tempAir_temp != temperature.getTemperatureAir() && millis() - tempAir_lastTimeUpdate > 3000) {
    tempAir_lastTimeUpdate = millis();

    tempAir_temp = temperature.getTemperatureAir();

    if (tempAir_temp < -50 || tempAir_temp > 60) {
      tempAir_temp = 0;
    }

    display4.clearBuffer();
    display4.setFont(numbers_temp_font);

    if (tempAir_temp < -9) {
      display4.drawStr(0, 58, getFormatTempAir(tempAir_temp));
    } else if (tempAir_temp >= 0 && tempAir_temp <= 9) {
      display4.drawStr(58, 58, getFormatTempAir(tempAir_temp));
    } else {
      display4.drawStr(29, 58, getFormatTempAir(tempAir_temp));
    }

    display4.drawXBMP(83, 26, 22, 32, bitmap_icon_temp_bits);
    display4.drawXBMP(110, 13, 18, 45, bitmap_icon_temp_air_bits);

    display4.sendBuffer();
  }
}