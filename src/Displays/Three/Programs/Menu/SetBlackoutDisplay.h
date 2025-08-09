#pragma once

void setDisplayProgramSetBlackoutDisplay() {
  settings.setMainPosition(13);
}

void encoderTurnDetectedSetBlackoutDisplay() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (settingsMemory.getBlackoutDisplayOff() == 1) {
        core.setLedBrightness(settings.getDefaultBlackout());
        settingsMemory.setBlackoutDisplayOff(0);
      } else {
        core.setLedBrightness(settingsMemory.getSettingDisplayContrast());
        settingsMemory.setBlackoutDisplayOff(1);
      }
    } else {
      if (settingsMemory.getBlackoutDisplayOff() == 0) {
        core.setLedBrightness(settingsMemory.getSettingDisplayContrast());
        settingsMemory.setBlackoutDisplayOff(1);
      } else {
        core.setLedBrightness(settings.getDefaultBlackout());
        settingsMemory.setBlackoutDisplayOff(0);
      }
    }
    settings.setReloadDisplay();
  }
  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramSetBlackoutDisplay() {
  encoderTurnDetectedSetBlackoutDisplay();

  if (settings.isReloadDisplay() || millis() - settings.getLastTimeUpdate() > 500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawStr(0, 15, { "Display dimming " });
    display3.drawStr(0, 29, { "when backlight is" });
    display3.drawStr(0, 43, { "turned on" });
    display3.drawXBMP(10, 48, 16, 16, settingsMemory.getBlackoutDisplayOff() == 1 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(30, 61, { "Off" });

    display3.drawXBMP(70, 48, 16, 16, settingsMemory.getBlackoutDisplayOff() == 0 ? bitmap_icon_radio_button_selected_bits : bitmap_icon_radio_button_empty_bits);
    display3.drawStr(90, 61, { "On" });
    display3.sendBuffer();
  }
}