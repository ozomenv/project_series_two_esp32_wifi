#pragma once
#include "Displays/Three/Core/Prototype.h"

#include "Displays/Three/Core/WritelnText.h"

#include "Displays/Three/Programs/MainScreen/MainScreen.h";
#include "Displays/Three/Programs/MainScreen/ShowTime.h";
#include "Displays/Three/Programs/MainScreen/ShowDate.h";
#include "Displays/Three/Programs/MainScreen/ShowVoltage.h";

#include "Displays/Three/Programs/Menu/ShowMenu.h"
#include "Displays/Three/Programs/Menu/ShowAbout.h"
#include "Displays/Three/Programs/Menu/ShowFirmware.h"

#include "Displays/Three/Programs/Menu/SetContrast.h"

#include "Displays/Three/Programs/Menu/SetHour.h"
#include "Displays/Three/Programs/Menu/SetMinute.h"

#include "Displays/Three/Programs/Menu/SetDateYear.h"
#include "Displays/Three/Programs/Menu/SetDateMonth.h"
#include "Displays/Three/Programs/Menu/SetDateDay.h"
#include "Displays/Three/Programs/Menu/SetHourType.h"
#include "Displays/Three/Programs/Menu/SetSoundWarning.h"
#include "Displays/Three/Programs/Menu/SetSoundClick.h"
#include "Displays/Three/Programs/Menu/SetBlackoutDisplay.h"
#include "Displays/Three/Programs/Menu/BatteryStatus.h"
#include "Displays/Three/Programs/Menu/ShowWifi.h"

#include "Displays/Three/Programs/WarningVoltage.h";
#include "Displays/Three/Programs/BlackoutDisplay.h";
#include "Displays/Three/Programs/SettingsTime.h";

class DisplayThree {
public:
    void init() {
        display3.begin();
        display3.setBitmapMode(1);
    }
    void clear() {
        display3.clearBuffer();
        display3.sendBuffer();
    }
    void run() {
        settingsTime();
        blackoutDisplay();
        checkWarning();
        switch (settings.getMainPosition()) {
            case 0:
                showProgramFirstDisplay();
            break;
            case 1:
                showProgramMenu();
            break;
            case 2:
                showProgramSetHour();
            break;
            case 3:
                showProgramSetMinute();
            break;
            case 4:
                showProgramSetContrast();
            break;
            case 5:
                showProgramSetDateYear();
            break;
            case 6:
                showProgramSetDateMonth();
            break;
            case 7:
                showProgramSetDateDay();
            break;
            case 8:
                showProgramAbout();
            break;
            case 9:
                showProgramSetHourType();
            break;
            case 10:
                showProgramFirmware();
            break;
            case 11:
                showProgramSetSoundWarning();
            break;
            case 12:
                showProgramSetSoundClick();
            break;
            case 13:
                showProgramSetBlackoutDisplay();
            break;
            case 14:
                showProgramBatteryStatus();
            break;
            case 15:
                showProgramWifi();
            break;
            default: break;
        }
    }

    void welcome() {
        display3.clearBuffer();
        display3.setFont(separator_for_time_font);
        display3.drawStr(65, 59, { ":" });

        display3.setFont(numbers_digital_font);
        display3.drawStr(18, 55, { "00" });
        display3.drawStr(81, 55, { "00" });

        display3.setFont(u8g_font_7x13B);

        display3.drawStr(0, 21, {"AM"});
        display3.drawStr(0, 57, {"PM"});
        display3.sendBuffer();
    }
};