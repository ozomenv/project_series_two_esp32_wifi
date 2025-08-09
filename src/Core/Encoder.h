#define PIN_CLK 12
#define PIN_DT 11
#define PIN_SW 46
#include <ESP32Encoder.h>

extern SettingsMemory settingsMemory;

class Encoder {
public:
  ESP32Encoder encoderClass;
  int64_t lastPosition = 0;
  bool turnDetected = false;
  bool rotationDirection = false;
  unsigned long lastButtonPress = 0;

  void encoderInit() {
    pinMode(PIN_SW, INPUT_PULLUP);
    ESP32Encoder::useInternalWeakPullResistors = puType::up;
    encoderClass.attachHalfQuad(PIN_DT, PIN_CLK);
    encoderClass.setCount(0);
  }

  boolean isSelected() {
    if (digitalRead(PIN_SW) == LOW) {
      if (millis() - lastButtonPress > 200) {
        lastButtonPress = millis();
        if (settingsMemory.getEncoderSoundOff() == 0) {
          //tone(BUZZER_PIN, 3000, 15);
        }
        return true;
      }
      lastButtonPress = millis();
    }
    return false;
  }

  boolean isTurnDetected() {
    int64_t newPos = encoderClass.getCount();
    if (abs(newPos - lastPosition) >= 2) {
      rotationDirection = (newPos > lastPosition);
      lastPosition = newPos;
      turnDetected = true;
    }
    if (turnDetected) {
      if (settingsMemory.getEncoderSoundOff() == 0) {
        //tone(BUZZER_PIN, 10000, 10);
      }
      turnDetected = false;
      return true;
    }
    return false;
  }

  boolean isRotationDirection() {
    return rotationDirection;
  }
};
