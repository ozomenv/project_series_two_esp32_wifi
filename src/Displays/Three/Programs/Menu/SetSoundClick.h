#pragma once
void setDisplayProgramSetSoundClick() {
  settings.setMainPosition(12);
}

void encoderTurnDetectedSetSoundClick() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (settingsMemory.getEncoderSoundOff() == 1) {
        settingsMemory.setEncoderSoundOff(0);
      } else {
        settingsMemory.setEncoderSoundOff(1);
      }
    } else {
      if (settingsMemory.getEncoderSoundOff() == 0) {
        settingsMemory.setEncoderSoundOff(1);
      } else {
        settingsMemory.setEncoderSoundOff(0);
      }
    }
    settings.setReloadDisplay();
  }
  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramSetSoundClick() {
  encoderTurnDetectedSetSoundClick();

  if (settings.isReloadDisplay()) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawStr(0, 15, { "Sound alert when " });
    display3.drawStr(0, 29, { "encoder rotates" });
    display3.drawXBMP(10, 40, 16, 16, settingsMemory.getEncoderSoundOff() == 1 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(30, 53, { "Off" });

    display3.drawXBMP(70, 40, 16, 16, settingsMemory.getEncoderSoundOff() == 0 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(90, 53, { "On" });
    display3.sendBuffer();
  }
}