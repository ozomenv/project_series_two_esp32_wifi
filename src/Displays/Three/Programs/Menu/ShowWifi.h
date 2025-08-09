#pragma once

void setDisplayProgramShowWifi() {

  settings.setMainPosition(15);
}

void encoderTurnDetectedWifi() {
  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramWifi() {
  encoderTurnDetectedWifi();

  if (settings.isReloadDisplay() || millis() - settings.getLastTimeUpdate() > 1500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    display3.drawStr(18, 14, { "Wi-Fi" });

    display3.setFont(u8g_font_9x18Br);


    display3.sendBuffer();
  }
}


