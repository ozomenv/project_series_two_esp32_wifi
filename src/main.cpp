#define BUZZER_PIN 7
#include "Arduino.h"
#include "Resources/Resources.h"
#include "Core/Core.h"
#include "Core/Button.h"
#include <Core/WifiCore.h>
#include "Displays/AppController.h"

WifiCore wifiCore;
Core core;
AppController appController;
Button buttonHour(16);
Button buttonMinute(15);

void setup() {
    Serial.begin(115200);
    core.init();
    appController.init();
    wifiCore.init();
}

void loop() {
    appController.run();
    core.refresh();
    wifiCore.handle();
}
