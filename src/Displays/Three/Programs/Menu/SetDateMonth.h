#pragma once
volatile uint8_t _thisMonthForSet = 1;

void setDisplayProgramSetDateMonth() {
  _thisMonthForSet = datetime.getMonth();
  settings.setMainPosition(6);
}
void encoderTurnDetectedSetMonth() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (_thisMonthForSet > 1) {
        _thisMonthForSet--;
      } else {
        _thisMonthForSet = 12;
      }
    } else {
      if (_thisMonthForSet < 12) {
        _thisMonthForSet++;
      } else {
        _thisMonthForSet = 1;
      }
    }
    settings.setLastTimeUpdate(settings.getLastTimeUpdate() + 700);
    settings.setLastTimeFlip(1);
  }

  if (encoder.isSelected()) {
    if (_thisMonthForSet != datetime.getMonth()) {
      datetime.saveMonth(_thisMonthForSet);
    }
    setDisplayProgramSetDateDay();
  }
}
void showProgramSetDateMonth() {

  encoderTurnDetectedSetMonth();

  if (millis() - settings.getLastTimeUpdate() > 500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();

    display3.setFont(u8g_font_helvB18r);
    display3.drawStr(5, 50, datetime.getDayChar(datetime.getDay()));
    display3.drawStr(30, 50, { "." });
    if (settings.isTimeFlip()) {
      display3.drawStr(40, 50, datetime.getMonthNumericChar(_thisMonthForSet));
    }
    display3.drawStr(66, 50, { "." });

    display3.drawStr(76, 50, datetime.getYearChar(datetime.getYear()));

    display3.drawXBMP(0, 8, 16, 16, bitmap_icon_setting_bits);
    display3.sendBuffer();
  }
}