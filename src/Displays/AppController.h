#pragma once
#include "Displays/DisplayConfiguration.h"

#include "Displays/One/DisplayOne.h"
#include "Displays/Two/DisplayTwo.h"
#include "Displays/Three/DisplayThree.h"
#include "Displays/Four/DisplayFour.h"

DisplayOne displayOne;
DisplayTwo displayTwo;
DisplayThree displayThree;
DisplayFour displayFour;

uint8_t displaysWelcome = 0;

class AppController {
public:
    void init() {
        displayOne.init();
        displayTwo.init();
        displayThree.init();
        displayFour.init();
    }
    void run() {
        if(voltage.getVoltageIgnitionStatus() == 1) {
            if(displaysWelcome == 0) {
                core.setLedBrightness(settingsMemory.getSettingDisplayContrast());
                displayOne.welcome();
                displayTwo.welcome();
                displayThree.welcome();
                displayFour.welcome();

                displaysWelcome = 1;
                delay(1500);
            }
            displayOne.run();
            displayTwo.run();
            displayThree.run();
            displayFour.run();
        } else {
            if(voltage.getVoltageIgnitionStatus() == 2) {
                core.setLedBrightness(0);
                voltage.setVoltageIgnitionStatus(0);
                displayOne.clear();
                displayTwo.clear();
                displayFour.clear();
            }
            displayThree.run();
            displaysWelcome = 0;
        }
    }
};