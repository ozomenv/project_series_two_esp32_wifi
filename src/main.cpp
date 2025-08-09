#include <Core/WifiCore.h>

WifiCore WifiCore;

void setup() {
    Serial.begin(115200);
    WifiCore.init();
}

void loop() {
    WifiCore.handle();
}
