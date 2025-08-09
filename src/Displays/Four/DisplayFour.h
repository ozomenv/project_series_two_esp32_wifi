#pragma once
#include "Displays/Four/Programs/ShowTempAir.h"

class DisplayFour {
public:
    void init() {
        display4.begin();
        display4.setBitmapMode(1);
    }
    void clear() {
        display4.clearBuffer();
        display4.sendBuffer();
        tempAirClear();
    }
    void run() {
        showTempAir();
    }
    void welcome() {
        display4.clearBuffer();

        display4.setFont(numbers_temp_font);
        display4.drawStr(0, 58, { "+88" });
        display4.drawXBMP(83, 26, 22, 32, bitmap_icon_temp_bits);
        display4.drawXBMP(110, 13, 18, 45, bitmap_icon_temp_air_bits);

        display4.sendBuffer();
    }
};