#pragma once
uint8_t lineHeight = 0;
uint8_t scrollOffset = 0;
uint8_t countLines = 0;

void writelnTextWithScroll(const char* text, bool isWrite) {
  char c;
  int i = 0;
  int x = 0;
  int y = lineHeight - (scrollOffset * 14);
  uint8_t wordWidth;
  char word[20];
  uint8_t wordIndex = 0;

  while ((c = pgm_read_byte(text + i)) != '\0') {
    if (c == ' ' || c == '\n' || pgm_read_byte(text + i + 1) == '\0') {
      if (pgm_read_byte(text + i + 1) == '\0' && c != ' ') {
        word[wordIndex++] = c;
      }
      word[wordIndex] = '\0';

      wordWidth = display3.getStrWidth(word);

      if (x + wordWidth > 128) {
        x = 0;
        y += lineHeight;
        if (!isWrite) {
          countLines++;
        }
      }

      if (isWrite) {
        if (c == '\n' || (y >= 0 && y < (64 + 10))) {
          display3.setCursor(x, y);
          display3.print(word);
        }
      }
      if (c == '\n') {
        x = 0;
        y += lineHeight;
      } else {
        x += wordWidth + display3.getStrWidth(" ");
      }

      wordIndex = 0;
    } else {
      word[wordIndex++] = c;
    }

    text++;
  }

  if (!isWrite) {
    if (countLines > 4) {
      countLines -= 3;
    } else if (countLines < 5) {
      countLines = 1;
    }
  }
}


void encoderTurnDetectedScrollText() {
  if (encoder.isTurnDetected()) {
    if (encoder.isRotationDirection()) {
      if (scrollOffset > 0) {
        scrollOffset--;
      }
    } else {
      if (scrollOffset < countLines) {
        scrollOffset++;
      }
    }
    settings.setReloadDisplay();
  }
  if (encoder.isSelected()) {
    scrollOffset = 0;
    setDisplayProgramShownMenu();
  }
}

void showProgramWritelnText(const char* text) {
  encoderTurnDetectedScrollText();

  if (settings.isReloadDisplay()) {
    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    writelnTextWithScroll(text, true);
    display3.drawXBMP(128 - 8, 0, 8, 64, bitmap_scrollbar_background);
    display3.drawBox(125, (64 / countLines) * scrollOffset, 3, (64 + countLines - 1) / countLines);
    display3.sendBuffer();
  }
}


