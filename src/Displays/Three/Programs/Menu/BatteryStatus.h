#pragma once

void setDisplayProgramBatteryStatus() {
  digitalWrite(35, HIGH);
  settings.setMainPosition(14);
}

void encoderTurnDetectedBatteryStatus() {
  if (encoder.isSelected()) {
    digitalWrite(35, LOW);
    setDisplayProgramShownMenu();
  }
}

char* getFractionalPartBattery(float number) {
  float fraction = number - static_cast<int>(number);
  sprintf(voltage_tempText, "%d v", static_cast<int>(fraction * 10));
  return voltage_tempText;
}

void showProgramBatteryStatus() {
  encoderTurnDetectedBatteryStatus();

  if (settings.isReloadDisplay() || millis() - settings.getLastTimeUpdate() > 1500) {
    settings.setLastTimeUpdate(millis());

    float voltage = analogRead(17) * 3.3 / 4095.0;
    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawStr(18, 14, { "Battery status" });

    display3.setFont(u8g_font_9x18Br);
    if (settings.isTimeFlip()) {
      if (voltage < 2.5){
        display3.drawStr(36, 35, { "REPLACE" });
      }
      if (voltage >= 2.5 && voltage <= 2.7){
        display3.drawStr(55, 35, { "LOW" });
      }
    }

    if (voltage > 2.7){
      display3.drawStr(58, 35, { "OK" });
    }

    display3.setFont(u8g_font_timR14);
    display3.drawStr(85, 61, {"."});
    display3.drawStr(74, 61, getIntegerPart(voltage));
    display3.drawStr(92, 61, getFractionalPartBattery(voltage));

    display3.sendBuffer();
  }
}