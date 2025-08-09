class Sound {
public:
  unsigned long soundLastToneTime = millis();

  int soundFrequencies[4] = {1000, 1200, 1400, 1200};
  uint8_t soundDurations[4] = {150, 150, 100, 150};
  int soundPauses[5] = {150, 200, 100, 200, 700};
  uint8_t soundCountRepeat = 0;
  uint8_t soundNoteIndex = 0;
  uint8_t soundWarningStatus = 0;

  unsigned long getSoundLastToneTime() {
    return soundLastToneTime;
  }

  void setSoundLastToneTime(unsigned long m) {
    soundLastToneTime = m;
  }

  int* getSoundFrequencies() {
    return soundFrequencies;
  }

  uint8_t* getSoundDurations() {
    return soundDurations;
  }

  uint8_t getSoundWarningStatus() {
    return soundWarningStatus;
  }

  void setSoundWarningStatus(uint8_t s) {
    soundWarningStatus = s;
  }

  int* getSoundPauses() {
    return soundPauses;
  }

  uint8_t getSoundNoteIndex() {
    return soundNoteIndex;
  }

  void setSoundNoteIndex(uint8_t i) {
    soundNoteIndex = i;
  }

  uint8_t getSoundCountRepeat() {
    return soundCountRepeat;
  }

  void setSoundCountRepeat(uint8_t c) {
    soundCountRepeat = c;
  }
};
