#pragma once
extern Button buttonHour;
extern Button buttonMinute;

void settingsTime() {
    if (buttonHour.click()) {
        //tone(BUZZER_PIN, 3000, 5);
        if (datetime.getHour() >= 23) {
            datetime.saveHour(0);
        } else {
            datetime.saveHour(datetime.getHour() + 1);
        }
        settings.setReloadDisplay();
    }
    if (buttonMinute.click()) {
        //tone(BUZZER_PIN, 3000, 5);
        if (datetime.getMinute() >= 59) {
            datetime.saveMinute(0);
        } else {
            datetime.saveMinute(datetime.getMinute() + 1);
        }
        settings.setReloadDisplay();
    }
}
