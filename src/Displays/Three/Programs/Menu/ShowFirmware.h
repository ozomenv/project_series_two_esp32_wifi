#pragma once
void setDisplayProgramShowTextFirmware() {
  countLines = 0;
  writelnTextWithScroll(textFirmware, false);
  settings.setMainPosition(10);
  lineHeight = display3.getMaxCharHeight();
}

void showProgramFirmware() {
  showProgramWritelnText(textFirmware);
}


