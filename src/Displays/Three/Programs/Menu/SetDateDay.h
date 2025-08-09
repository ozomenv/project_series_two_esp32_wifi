#pragma once
uint8_t _thisDayForSet = 1;

void setDisplayProgramSetDateDay() {
  _thisDayForSet = datetime.getDay();
  settings.setMainPosition(7);
}

void encoderTurnDetectedSetDay() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (_thisDayForSet > 1) {
        _thisDayForSet--;
      } else {
        _thisDayForSet = datetime.getMaxDays(datetime.getMonth());
      }
    } else {
      if (_thisDayForSet < datetime.getMaxDays(datetime.getMonth())) {
        _thisDayForSet++;
      } else {
        _thisDayForSet = 1;
      }
    }
    settings.setLastTimeUpdate(settings.getLastTimeUpdate() + 700);
    settings.setLastTimeFlip(1);
  }

  if (encoder.isSelected()) {
    if (_thisDayForSet != datetime.getDay()) {
      datetime.saveDay(_thisDayForSet);
    }
    setDisplayProgramShownMenu();
  }
}
void showProgramSetDateDay() {

  encoderTurnDetectedSetDay();

  if (millis() - settings.getLastTimeUpdate() > 500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();
    display3.setFont(u8g_font_helvB18r);

    if (settings.isTimeFlip()) {
      display3.drawStr(5, 50, datetime.getDayChar(_thisDayForSet));
    }

    display3.drawStr(30, 50, { "." });
    display3.drawStr(40, 50, datetime.getMonthNumericChar(datetime.getMonth()));
    display3.drawStr(66, 50, { "." });
    display3.drawStr(76, 50, datetime.getYearChar(datetime.getYear()));
    display3.drawXBMP(0, 8, 16, 16, bitmap_icon_setting_bits);
    display3.sendBuffer();
  }
}