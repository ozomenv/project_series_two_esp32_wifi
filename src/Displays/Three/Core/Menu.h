class MenuItemObject {
public:
  MenuItemObject(uint8_t parentId = 0, uint8_t id = 0, char* name = "", const uint8_t* icon = nullptr, void (*callback)() = nullptr)
    : _parentId(parentId), _id(id), _name(name), _icon(icon), _callback(callback){};
  uint8_t getParentId() {
    return _parentId;
  };
  uint8_t getId() {
    return _id;
  };
  char* getName() {
    return _name;
  };
  const uint8_t* getIcon() {
    return _icon;
  }
  void triggerCallback() {
    if (_callback != nullptr) {
      _callback();
    }
  }
private:
  uint8_t _parentId;
  uint8_t _id;
  char* _name;
  const uint8_t* _icon;
  void (*_callback)() PROGMEM;
};

class MenuListClass {
public:
  uint8_t _countAll = 14;

  MenuItemObject* _listActiveItems;
  MenuItemObject* _listAllItems;

  uint8_t _thisId = 0;
  uint8_t _thisPrevId = 0;
  uint8_t _thisNextId = 0;
  uint8_t _thisParentId = 0;
  uint8_t _countThisParent = 0;

  MenuListClass() {
    _listActiveItems = new MenuItemObject[_countAll];
    _listAllItems = new MenuItemObject[_countAll]{
      MenuItemObject(0, 0, { "Time" }, bitmap_icon_time_bits, setDisplayProgramSetHour),
      MenuItemObject(0, 1, { "Date" }, bitmap_icon_date_bits, setDisplayProgramSetDateYear),
      MenuItemObject(0, 2, { "Brightness" }, bitmap_icon_contrast_bits, setDisplayProgramSetContrast),
      MenuItemObject(0, 3, { "Dimming" }, bitmap_icon_display_bits, setDisplayProgramSetBlackoutDisplay),
      MenuItemObject(0, 4, { "Time format" }, bitmap_icon_clock_setting_bits, setDisplayProgramSetHourType),
      MenuItemObject(0, 5, { "Sound alert" }, bitmap_icon_sound_bits, menuSetNextLevel),
      MenuItemObject(0, 6, { "Clock battery" }, battery2_bits, setDisplayProgramBatteryStatus),
      MenuItemObject(0, 7, { "About" }, bitmap_icon_about_bits, setDisplayProgramShowTextAbout),
      MenuItemObject(0, 8, { "Firmware" }, bitmap_icon_firmware_bits, setDisplayProgramShowTextFirmware),
      MenuItemObject(0, 9, { "Wi-Fi" }, bitmap_icon_firmware_bits, setDisplayProgramShowWifi),
      MenuItemObject(0, 10, { "Exit" }, bitmap_icon_exit_bits, setDisplayProgramShownFirstDisplay),

      MenuItemObject(5, 0, { "Back" }, bitmap_icon_back_bits, menuSetPrevLevel),
      MenuItemObject(5, 1, { "Volt warning" }, bitmap_icon_voltage_bits, setDisplayProgramSetSoundWarning),
      MenuItemObject(5, 2, { "Rotates" }, bitmap_icon_encoder_bits, setDisplayProgramSetSoundClick),
    };
  };

  void reinitMenu() {
    _countThisParent = 0;

    for (uint8_t i = 0; i < _countAll; ++i) {
      MenuItemObject& item = _listAllItems[i];
      if (item.getParentId() == _thisParentId) {
        _listActiveItems[_countThisParent] = item;
        ++_countThisParent;
      }
    }
    recalculatePrevNext();
  }

  void recalculatePrevNext() {
    if (_thisId == 0) {
      _thisPrevId = _countThisParent - 1;
    } else {
      _thisPrevId = _thisId - 1;
    }

    if (_thisId == _countThisParent - 1) {
      _thisNextId = 0;
    } else {
      _thisNextId = _thisId + 1;
    }
  }

  MenuItemObject getActiveItem() {
    return getItem(_thisParentId, _thisId);
  }
  MenuItemObject getPrevItem() {
    return getItem(_thisParentId, _thisPrevId);
  }
  MenuItemObject getNextItem() {
    return getItem(_thisParentId, _thisNextId);
  }
  void setPrevPosition() {
    if (_thisId == 0) {
      setPosition(_countThisParent - 1);
    } else {
      setPosition(_thisId - 1);
    }
  }
  void setNextPosition() {
    if (_thisId < _countThisParent - 1) {
      setPosition(_thisId + 1);
    } else {
      setPosition(0);
    }
  }
  void setPosition(uint8_t thisPosition) {
    _thisId = thisPosition;

    recalculatePrevNext();
  }

  void resetMenu() {
    _thisParentId = 0;
    _thisId = 0;
    reinitMenu();
  }

  void setNextLevel() {
    _thisParentId = getActiveItem().getId();
    _thisId = 1;
    reinitMenu();
  }

  void setPrevLevel() {
    _thisId = getActiveItem().getParentId();
    _thisParentId = 0;
    reinitMenu();
  }

  void showMenu() {
    display3.clearBuffer();
    display3.setFont(u8g_font_7x14B);
    showPrevMenu(getPrevItem());
    showThisMenu(getActiveItem());
    showNextMenu(getNextItem());
    display3.drawXBMP(128 - 8, 0, 8, 64, bitmap_scrollbar_background);
    display3.drawBox(125, 64 / _countThisParent * _thisId, 3, (64 + _countThisParent - 1) / _countThisParent);
    display3.sendBuffer();
  }

  void showThisMenu(MenuItemObject item) {
    display3.drawXBMP(0, 22, 128, 21, bitmap_item_sel_outline);
    display3.drawStr(25, 15 + 20 + 2, item.getName());
    if (item.getIcon() != nullptr) {
      display3.drawXBMP(4, 24, 16, 16, item.getIcon());
    }
  }

  void showPrevMenu(MenuItemObject item) {
    display3.drawStr(25, 15, item.getName());
    if (item.getIcon() != nullptr) {
      display3.drawXBMP(4, 2, 16, 16, item.getIcon());
    }
  }

  void showNextMenu(MenuItemObject item) {
    display3.drawStr(25, 15 + 20 + 20 + 2 + 2, item.getName());
    if (item.getIcon() != nullptr) {
      display3.drawXBMP(4, 46, 16, 16, item.getIcon());
    }
  }
private:
  MenuItemObject getItem(uint8_t parentId, uint8_t id) {
    for (uint8_t i = 0; i < _countThisParent; i++) {
      MenuItemObject item = _listActiveItems[i];
      if (item.getParentId() == _thisParentId && item.getId() == id) {
        return item;
      }
    }
  }
};
