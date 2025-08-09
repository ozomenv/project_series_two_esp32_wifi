#pragma once
volatile uint8_t setMinute_thisMinuteForSet = 0;

void setDisplayProgramSetMinute() {
  setMinute_thisMinuteForSet = datetime.getMinute();
  settings.setReloadMenuForDisplay();
  settings.setMainPosition(3);
}
void encoderTurnDetectedSetMinute() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (setMinute_thisMinuteForSet == 0) {
        setMinute_thisMinuteForSet = 59;
      } else {
        setMinute_thisMinuteForSet--;
      }
    } else {
      if (setMinute_thisMinuteForSet == 59) {
        setMinute_thisMinuteForSet = 0;
      } else {
        setMinute_thisMinuteForSet++;
      }
    }
    settings.setLastTimeUpdate(settings.getLastTimeUpdate() + 700);
    settings.setLastTimeFlip(1);
  }

  if (encoder.isSelected()) {
    if (setMinute_thisMinuteForSet != datetime.getMinute()) {
      datetime.saveMinute(setMinute_thisMinuteForSet);
    }
    setDisplayProgramShownMenu();
  }
}
void showProgramSetMinute() {
  encoderTurnDetectedSetMinute();

  if (millis() - settings.getLastTimeUpdate() > 500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();

    display3.setFont(separator_for_time_font);
    display3.drawStr(66, 59, { ":" });

    display3.setFont(numbers_digital_font);
    display3.drawStr(datetime.isTwoLevel(datetime.getHour()) ? 18 : 45, 55, datetime.getHourChar(datetime.getHour()));

    if (settings.isTimeFlip()) {
      display3.setFont(numbers_digital_font);
      display3.drawStr(81, 55, datetime.getMinuteChar(setMinute_thisMinuteForSet));
    }

    display3.drawXBMP(0, 27, 16, 16, bitmap_icon_setting_bits);

    display3.setFont(u8g_font_7x13B);

    display3.drawStr(0, datetime.isTypeAm(datetime.getHour()) ? 21 : 57, datetime.getTypeHour(datetime.getHour()));

    display3.sendBuffer();
  }
}