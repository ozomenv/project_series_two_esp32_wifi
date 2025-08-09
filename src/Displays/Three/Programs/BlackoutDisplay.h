#pragma once

void blackoutDisplay() {
  if(voltage.getVoltageBacklightChangeStatus() == 0 || settingsMemory.getBlackoutDisplayOff() == 1) {
    return;
  }

  if(voltage.isBacklightOn()) {
    core.setLedBrightness(settings.getDefaultBlackout());
  } else {
    core.setLedBrightness(settingsMemory.getSettingDisplayContrast());
  }
}
