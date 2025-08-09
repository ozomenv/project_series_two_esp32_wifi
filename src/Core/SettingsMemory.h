#include <Preferences.h>

class SettingsMemory {
private:
  Preferences prefs;
public:
  uint8_t settingDisplayContrast = 255;
  uint8_t settingDateHourType = 0;
  uint8_t settingSoundWarningOff = 0;
  uint8_t settingEncoderSoundOff = 0;
  uint8_t settingBlackoutDisplayOff = 0;

  void init() {
    prefs.begin("settings", true);  // true = read-only

    settingDisplayContrast = prefs.getUChar("contrast", 255);
    settingDateHourType = prefs.getUChar("hourtype", 0);
    settingSoundWarningOff = prefs.getUChar("warnsound", 0);
    settingEncoderSoundOff = prefs.getUChar("encsound", 0);
    settingBlackoutDisplayOff = prefs.getUChar("blackout", 0);

    prefs.end();
  }

  uint8_t getSettingDisplayContrast() {
    return settingDisplayContrast;
  }

  uint8_t getDateHourType() {
    return settingDateHourType;
  }

  uint8_t getSoundWarningOff() {
    return settingSoundWarningOff;
  }

  uint8_t getEncoderSoundOff() {
    return settingEncoderSoundOff;
  }

  uint8_t getBlackoutDisplayOff() {
    return settingBlackoutDisplayOff;
  }

  void setDisplayContrast(uint8_t c) {
    settingDisplayContrast = c;
    saveValue("contrast", c);
  }

  void setDateHourType(uint8_t c) {
    settingDateHourType = c;
    saveValue("hourtype", c);
  }

  void setSoundWarningOff(uint8_t w) {
    settingSoundWarningOff = w;
    saveValue("warnsound", w);
  }

  void setEncoderSoundOff(uint8_t s) {
    settingEncoderSoundOff = s;
    saveValue("encsound", s);
  }

  void setBlackoutDisplayOff(uint8_t b) {
    settingBlackoutDisplayOff = b;
    saveValue("blackout", b);
  }

private:
  void saveValue(const char* key, uint8_t value) {
    prefs.begin("settings", false);  // false = write mode
    prefs.putUChar(key, value);
    prefs.end();
  }
};
