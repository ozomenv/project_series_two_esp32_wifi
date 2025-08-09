#pragma once
void showProgramTime() {
  if (millis() - settings.getLastTimeUpdate() > 700 || settings.isReloadDisplay()) {
    settings.setLastTimeUpdate(millis());
    display3.clearBuffer();
    if (settings.isTimeFlip()) {
      display3.setFont(separator_for_time_font);
      display3.drawStr(66, 59, { ":" });
    }

    display3.setFont(numbers_digital_font);
    display3.drawStr(datetime.isTwoLevel(datetime.getHour()) ? 18 : 45, 55, datetime.getHourChar(datetime.getHour()));
    display3.drawStr(81, 55, datetime.getMinuteChar(datetime.getMinute()));

    display3.setFont(u8g_font_7x13B);
    display3.drawStr(0, datetime.isTypeAm(datetime.getHour()) ? 21 : 57, datetime.getTypeHour(datetime.getHour()));

    display3.sendBuffer();
  }
}