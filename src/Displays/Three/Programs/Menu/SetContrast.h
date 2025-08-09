#pragma once
boolean reloadDisplayForSetContrast = true;
uint8_t contrast_numbers[10] = {0, 40, 85, 110, 135, 160, 185, 210, 230, 255};

void setDisplayProgramSetContrast() {
  reloadDisplayForSetContrast = true;
  settings.setMainPosition(4);
}

uint8_t getThisPositionContrast(uint8_t  contrast) {
  for (uint8_t  i = 0; i < sizeof(contrast_numbers) / sizeof(contrast_numbers[0]); i++) {
    if (contrast_numbers[i] == contrast) {
      return i;
    }
  }
}

uint8_t displayContrast = getThisPositionContrast(settingsMemory.getSettingDisplayContrast());

uint8_t getThisContrast(uint8_t  position) {
  return contrast_numbers[position];
}


void encoderTurnDetectedSetContrast() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (displayContrast > 0) {
        displayContrast--;
      }
    } else {
      if (displayContrast < 9) {
        displayContrast++;
      }
    }
    settingsMemory.setDisplayContrast(getThisContrast(displayContrast));
    core.setLedBrightness(settingsMemory.getSettingDisplayContrast());

    reloadDisplayForSetContrast = true;
  }
  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramSetContrast() {
  encoderTurnDetectedSetContrast();
  displayContrast = getThisPositionContrast(settingsMemory.getSettingDisplayContrast());
  if (reloadDisplayForSetContrast) {
    reloadDisplayForSetContrast = false;
    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawXBMP(15, 23, 100, 24, bitmap_icon_contrast_block_bits);
    display3.drawBox(19, 25, (10 * displayContrast), 19);
    display3.drawStr(34, 15, { "Brightness" });
    display3.drawStr(2, 38, { "-" });
    display3.drawStr(118, 38, { "+" });
    display3.sendBuffer();
  }
}