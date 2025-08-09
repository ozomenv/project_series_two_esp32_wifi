#pragma once
#include "Displays/Two/Programs/ShowTempEngine.h"

class DisplayTwo {
public:
    void init() {
        display2.begin();
        display2.setBitmapMode(1);
    }
    void clear() {
        display2.clearBuffer();
        display2.sendBuffer();
    }
    void run() {
        showTempEngine();
        tempEngineClear();
    }
    void welcome() {
        display2.clearBuffer();

        display2.setFont(numbers_temp_font);
        display2.drawStr(0, 58, { "188" });
        display2.drawXBMP(83, 26, 22, 32, bitmap_icon_temp_bits);
        display2.drawXBMP(107, 13, 21, 45, bitmap_icon_temp_water_bits);

        display2.sendBuffer();
    }
};