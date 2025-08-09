#pragma once
#include <SPI.h>
#include "Core/Settings.h"
#include "Core/Sound.h"
#include "Core/SettingsMemory.h"
#include "Core/Voltage.h"
#include "Core/Encoder.h"
#include "Core/Datetime.h"
#include "Core/Temperature.h"

Settings settings;
SettingsMemory settingsMemory;
Sound sound;
Voltage voltage;
Temperature temperature;
Datetime datetime;
Encoder encoder;

class Core {
public:
    static void init() {
        pinMode(35, OUTPUT);
        //Wire.begin(42, 41);
        //SPI.begin(14, -1, 13);
        datetime.clockInit();
        encoder.encoderInit();
        settings.init();
        settingsMemory.init();
        voltage.init();
        temperature.init();
        initLed();
    }
    static void refresh() {
        datetime.refresh();
        voltage.refresh();
        temperature.refresh();
    }
    static void playWarning() {
        if (sound.getSoundNoteIndex() < 4 && millis() - sound.getSoundLastToneTime() >= sound.getSoundPauses()[sound.getSoundNoteIndex()]) {
            //tone(BUZZER_PIN, sound.getSoundFrequencies()[sound.getSoundNoteIndex()], sound.getSoundDurations()[sound.getSoundNoteIndex()]);
            sound.setSoundLastToneTime(millis());
            sound.setSoundNoteIndex(sound.getSoundNoteIndex() + 1);
        }

        if (sound.getSoundNoteIndex() >= 4 && millis() - sound.getSoundLastToneTime() >= sound.getSoundPauses()[4]) {
            sound.setSoundNoteIndex(0);
            sound.setSoundCountRepeat(sound.getSoundCountRepeat() + 1);
        }
    }

    static void initLed() {
        ledcSetup(1, 5000, 8);
        ledcAttachPin(6, 1);
        setLedBrightness(0);
    }

    static void setLedBrightness(uint8_t brightness) {
        ledcWrite(1, brightness);
    }
};