#pragma once
extern Core core;

unsigned long warning_lastTimeUpdate = 0;
uint8_t warning_status = 0;

void checkWarning() {
  if(settingsMemory.getSoundWarningOff() == 0) {
    return;
  }
  if ((warning_status == 0 || warning_status == 1) && millis() - warning_lastTimeUpdate > 2000) {
    warning_lastTimeUpdate = millis();

    if(warning_status == 0 && voltage.getVoltageIgnition() > 13) {
      warning_status = 1;
    }

    if(voltage.getVoltageIgnition() > 13 && voltage.getVoltageIgnition() < 15) {
      settings.setLastTimeUpdateVoltage(millis());
    }

    if(warning_status == 1 && millis() - settings.getLastTimeUpdateVoltage() > 10000) {
      warning_status = 2;

      settings.setMainScreenPosition(2);
    }
  }
  if (warning_status == 2) {
    core.playWarning();
    if(sound.getSoundCountRepeat()  > 3) {
      warning_status = 3;
      sound.setSoundCountRepeat(0);
    }
  }
}
