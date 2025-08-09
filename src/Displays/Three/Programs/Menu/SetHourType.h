#pragma once

void setDisplayProgramSetHourType() {
  settings.setMainPosition(9);
}

void encoderTurnDetectedSetHourType() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (settingsMemory.getDateHourType() == 1) {
        settingsMemory.setDateHourType(0);
      } else {
        settingsMemory.setDateHourType(1);
      }
    } else {
      if (settingsMemory.getDateHourType() == 0) {
        settingsMemory.setDateHourType(1);
      } else {
        settingsMemory.setDateHourType(0);
      }
    }
    settings.setReloadDisplay();
  }
  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramSetHourType() {
  encoderTurnDetectedSetHourType();

  if (settings.isReloadDisplay()) {
    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawStr(30, 15, { "Time format" });
    display3.drawXBMP(0, 23, 16, 16, settingsMemory.getDateHourType() == 0 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(20, 36, { "12-hour format" });

    display3.drawXBMP(0, 45, 16, 16, settingsMemory.getDateHourType() == 1 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(20, 58, { "24-hour format" });
    display3.sendBuffer();
  }
}