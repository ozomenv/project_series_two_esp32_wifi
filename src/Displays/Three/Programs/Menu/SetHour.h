#pragma once
volatile uint8_t _thisHourForSet = 0;

void setDisplayProgramSetHour() {
  _thisHourForSet = datetime.getHour();
  settings.setMainPosition(2);
}
void encoderTurnDetectedSetHour() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (_thisHourForSet == 0) {
        _thisHourForSet = 23;
      } else {
        _thisHourForSet--;
      }
    } else {
      if (_thisHourForSet >= 23) {
        _thisHourForSet = 0;
      } else {
        _thisHourForSet++;
      }
    }
    settings.setLastTimeUpdate(settings.getLastTimeUpdate() + 700);
    settings.setLastTimeFlip(1);
  }

  if (encoder.isSelected()) {
    datetime.saveHour(_thisHourForSet);
    setDisplayProgramSetMinute();
  }
};

void showProgramSetHour() {
  encoderTurnDetectedSetHour();

  if (millis() - settings.getLastTimeUpdate() > 500) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();
    display3.setFont(separator_for_time_font);
    display3.drawStr(66, 59, { ":" });

    display3.setFont(numbers_digital_font);
    if (settings.isTimeFlip()) {
      display3.drawStr(datetime.isTwoLevel(_thisHourForSet) ? 18 : 45, 55, datetime.getHourChar(_thisHourForSet));
    }
    display3.drawStr(81, 55, datetime.getMinuteChar(datetime.getMinute()));

    display3.drawXBMP(0, 27, 16, 16, bitmap_icon_setting_bits);

    display3.setFont(u8g_font_7x13B);

    display3.drawStr(0, datetime.isTypeAm(_thisHourForSet) ? 21 : 57, datetime.getTypeHour(_thisHourForSet));

    display3.sendBuffer();
  }
}