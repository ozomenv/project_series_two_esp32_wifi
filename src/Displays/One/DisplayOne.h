#pragma once
#include "Displays/One/Programs/ShowTempOil.h"

class DisplayOne {
public:
    void init() {
        display1.begin();
        display1.setBitmapMode(1);
    }
    void run() {
        showTempOil();
    }
    void clear() {
        display1.clearBuffer();
        display1.sendBuffer();
        tempOilClear();
    }
    void welcome() {
        display1.clearBuffer();

        display1.setFont(numbers_temp_font);
        display1.drawStr(0, 58, { "188" });
        display1.drawXBMP(83, 26, 22, 32, bitmap_icon_temp_bits);
        display1.drawXBMP(110, 13, 18, 45, bitmap_icon_oil_bits);

        display1.sendBuffer();
    }
};