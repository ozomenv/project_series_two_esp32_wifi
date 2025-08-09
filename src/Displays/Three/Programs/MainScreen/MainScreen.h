#pragma once

void encoderTurnDetectedSetFirstDisplay() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {

      if (settings.getMainScreenPosition() > 0) {
        settings.setMainScreenPosition(settings.getMainScreenPosition() - 1);
      } else {
        settings.setMainScreenPosition(2);
      }
    } else {
      if (settings.getMainScreenPosition() < 2) {
        settings.setMainScreenPosition(settings.getMainScreenPosition() + 1);
      } else {
        settings.setMainScreenPosition(0);
      }
    }
  }

  if (encoder.isSelected()) {
    setDisplayProgramShownMenu();
  }
}

void showProgramFirstDisplay() {
  encoderTurnDetectedSetFirstDisplay();
  switch (settings.getMainScreenPosition()) {
    case 0:
      showProgramTime();
      break;
    case 1:
      showProgramDate();
      break;
    case 2:
      showProgramVoltage();
      break;
    default: break;
  }
}