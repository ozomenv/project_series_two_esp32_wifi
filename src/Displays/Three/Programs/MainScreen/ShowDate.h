#pragma once
void showProgramDate() {
  if (millis() - settings.getLastTimeUpdate() > 10000 || settings.isReloadDisplay()) {
    settings.setLastTimeUpdate(millis());

    display3.clearBuffer();
    display3.drawXBMP(21, 0, 89, 64, bitmap_icon_calendar_bits);
    display3.setFont(u8g_font_7x14B);
    display3.drawStrX2(75, 56, datetime.getDayChar(datetime.getDay()));
    display3.setFont(u8g_font_8x13Br);
    display3.drawStr(((129 - display3.getUTF8Width(datetime.getMonthChar(datetime.getMonth()))) / 2), 20, datetime.getMonthChar(datetime.getMonth()));
    display3.sendBuffer();
  }
}