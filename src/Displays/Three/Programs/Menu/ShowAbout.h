#pragma once
void setDisplayProgramShowTextAbout() {
  countLines = 0;
  writelnTextWithScroll(textAbout, false);

  settings.setMainPosition(8);

  lineHeight = display3.getMaxCharHeight();
}

void showProgramAbout() {
  showProgramWritelnText(textAbout);
}


