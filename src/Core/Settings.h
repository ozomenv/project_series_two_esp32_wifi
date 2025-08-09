class Settings {
public:
  void init() {
  }

  uint8_t mainPosition = 0;
  uint8_t mainScreenPosition = 0;
  uint8_t reloadDisplay = 0;
  uint8_t lastTimeFlip = 0;
  uint8_t reloadMenuForDisplay = 0;
  uint8_t defaultBlackout = 70;
  unsigned long lastTimeUpdate = 0;
  unsigned long lastTimeUpdateVoltage = 0;

  uint8_t getReloadMenuForDisplay() {
    return reloadMenuForDisplay;
  }

  uint8_t getMainScreenPosition() {
    return mainScreenPosition;
  }
  uint8_t getMainPosition() {
    return mainPosition;
  }
  uint8_t getDefaultBlackout() {
    return defaultBlackout;
  }
  unsigned long getLastTimeUpdate() {
    return lastTimeUpdate;
  }
  unsigned long getLastTimeUpdateVoltage() {
    return lastTimeUpdateVoltage;
  }

  bool isReloadDisplay() {
    if (reloadDisplay == 1) {
      reloadDisplay = 0;
      return true;
    }
    return false;
  }

  bool isReloadMenuForDisplay() {
    if (reloadMenuForDisplay == 1) {
      reloadMenuForDisplay = 0;
      return true;
    }
    return false;
  }

  void setMainScreenPosition(uint8_t m) {
    mainScreenPosition = m;
    reloadDisplay = 1;
  }

  void setReloadDisplay() {
    reloadDisplay = 1;
  }

  void setMainPosition(uint8_t p) {
    mainPosition = p;
    reloadDisplay = 1;
  }

  bool isTimeFlip() {
    if (lastTimeFlip == 1) {
      lastTimeFlip = 0;
      return true;
    }
    if (lastTimeFlip == 0) {
      lastTimeFlip = 1;
      return false;
    }
  }

  void setLastTimeFlip(uint8_t l) {
    lastTimeFlip = l;
  }

  void setReloadMenuForDisplay() {
    reloadMenuForDisplay = 1;
  }

  void setLastTimeUpdate(unsigned long l) {
    lastTimeUpdate = l;
  }

  void setLastTimeUpdateVoltage(unsigned long l) {
    lastTimeUpdateVoltage = l;
  }
};
