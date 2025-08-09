#pragma once
char tempOil_tempText[2];
int tempOil_temp = 0;

unsigned long tempOil_lastTimeUpdate = millis() - 3300;

void tempOilClear() {
  tempOil_lastTimeUpdate = millis() - 3300;
  tempOil_temp = 0;
}

inline char* getFormatTempOil(int temp) {
  sprintf(tempOil_tempText, "%d", temp);
  return tempOil_tempText;
}

void showTempOil() {
  if (tempOil_temp != temperature.getTemperatureOil() && millis() - tempOil_lastTimeUpdate > 3200) {
    tempOil_lastTimeUpdate = millis();

    tempOil_temp = temperature.getTemperatureOil();

    display1.clearBuffer();
    display1.setFont(numbers_temp_font);
    if (tempOil_temp < 50) {
      display1.drawStr(29, 58, {"--"});
    }else if (tempOil_temp >= 100) {
      display1.drawStr(0, 58, getFormatTempOil(tempOil_temp));
    } else {
      display1.drawStr(29, 58, getFormatTempOil(tempOil_temp));
    }

    display1.drawXBMP(83, 26, 22, 32, bitmap_icon_temp_bits);
    display1.drawXBMP(110, 13, 18, 45, bitmap_icon_oil_bits);

    display1.sendBuffer();
  }
}