#pragma once
extern Core core;

char tempEngine_tempText[2];
int tempEngine_temp = 0;
unsigned long tempEngine_lastTimeUpdate = millis() - 3400;

void tempEngineClear() {
  tempEngine_lastTimeUpdate = millis() - 3400;
  tempEngine_temp = 0;
}

inline char* getFormatTempEngine(int temp) {
  sprintf(tempEngine_tempText, "%d", temp);
  return tempEngine_tempText;
}

void showTempEngine() {
  if (tempEngine_temp != temperature.getTemperatureWater() && millis() - tempEngine_lastTimeUpdate > 3300) {
    tempEngine_temp = temperature.getTemperatureWater();
    tempEngine_lastTimeUpdate = millis();

    display2.clearBuffer();
    display2.setFont(numbers_temp_font);

    if (tempEngine_temp < 50) {
      display2.drawStr(29, 58, {"--"});
    }else if (tempEngine_temp >= 100) {
      display2.drawStr(0, 58, getFormatTempEngine(tempEngine_temp));
    } else {
      display2.drawStr(29, 58, getFormatTempEngine(tempEngine_temp));
    }

    display2.drawXBMP(83, 26, 22, 32, bitmap_icon_temp_bits);
    display2.drawXBMP(107, 13, 21, 45, bitmap_icon_temp_water_bits);

    display2.sendBuffer();

    if (sound.getSoundWarningStatus() == 0 && temperature.getTemperatureWater() >= 100) {
      sound.setSoundWarningStatus(1);
    }

  }
  if (settingsMemory.getSoundWarningOff() == 0 && sound.getSoundWarningStatus() == 1) {
    core.playWarning();
    if(sound.getSoundCountRepeat() > 3) {
      sound.setSoundWarningStatus(2);
      sound.setSoundCountRepeat(0);
    }
  }
}
