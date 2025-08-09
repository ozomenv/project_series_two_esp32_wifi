#pragma once

void setDisplayProgramSetSoundWarning() {
  settings.setMainPosition(11);
}

void encoderTurnDetectedSetSoundWarning() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (settingsMemory.getSoundWarningOff() == 1) {
        settingsMemory.setSoundWarningOff(0);
      } else {
        settingsMemory.setSoundWarningOff(1);
      }
    } else {
      if (settingsMemory.getSoundWarningOff() == 0) {
        settingsMemory.setSoundWarningOff(1);
      } else {
        settingsMemory.setSoundWarningOff(0);
      }
    }
    settings.setReloadDisplay();
  }
  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramSetSoundWarning() {
  encoderTurnDetectedSetSoundWarning();

  if (settings.isReloadDisplay()) {
    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawStr(0, 15, { "Sound alert about" });
    display3.drawStr(0, 29, { "low or high volt" });

    display3.drawXBMP(10, 40, 16, 16, settingsMemory.getSoundWarningOff() == 1 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(30, 53, { "Off" });

    display3.drawXBMP(70, 40, 16, 16, settingsMemory.getSoundWarningOff() == 0 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(90, 53, { "On" });
    display3.sendBuffer();
  }
}