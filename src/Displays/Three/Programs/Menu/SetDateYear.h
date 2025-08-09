#pragma once
volatile uint16_t _thisYearForSet = 0;

void setDisplayProgramSetDateYear() {
  _thisYearForSet = datetime.getYear();
  settings.setMainPosition(5);
}
void encoderTurnDetectedSetYear() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (_thisYearForSet > 2000) {
        _thisYearForSet--;
      }
    } else {
      if (_thisYearForSet < 2099) {
        _thisYearForSet++;
      }
    }
    settings.setLastTimeUpdate(settings.getLastTimeUpdate() + 700);
    settings.setLastTimeFlip(1);
  }

  if (encoder.isSelected()) {
    if (_thisYearForSet != datetime.getYear()) {
      datetime.saveYear(_thisYearForSet);
    }
    setDisplayProgramSetDateMonth();
  }
}
void showProgramSetDateYear() {
  encoderTurnDetectedSetYear();

  if (millis() - settings.getLastTimeUpdate() > 500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();

    display3.setFont(u8g_font_helvB18r);
    display3.drawStr(5, 50, datetime.getDayChar(datetime.getDay()));
    display3.drawStr(30, 50, { "." });
    display3.drawStr(40, 50, datetime.getMonthNumericChar(datetime.getMonth()));
    display3.drawStr(66, 50, { "." });

    if (settings.isTimeFlip()) {
      display3.drawStr(76, 50, datetime.getYearChar(_thisYearForSet));
    }

    display3.drawXBMP(0, 8, 16, 16, bitmap_icon_setting_bits);
    display3.sendBuffer();
  }
}