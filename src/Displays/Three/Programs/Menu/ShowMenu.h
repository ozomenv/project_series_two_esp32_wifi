#pragma once
#include "Displays/Three/Core/Menu.h"

MenuListClass menuList;

void setDisplayProgramShownFirstDisplay() {
  settings.setMainPosition(0);
  menuList.resetMenu();
}

void setDisplayProgramShownMenu() {
  settings.setReloadMenuForDisplay();
  menuList.reinitMenu();
  settings.setMainPosition(1);
}

void menuSetNextLevel() {
  menuList.setNextLevel();
  settings.setReloadMenuForDisplay();
}

void menuSetPrevLevel() {
  menuList.setPrevLevel();
  settings.setReloadMenuForDisplay();
}

void showProgramMenu() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      menuList.setPrevPosition();
    } else {
      menuList.setNextPosition();
    }
    settings.setReloadMenuForDisplay();
  }
  if (encoder.isSelected()) {
    menuList.getActiveItem().triggerCallback();
  }

  if (settings.isReloadMenuForDisplay()) {
    menuList.showMenu();
  }
}