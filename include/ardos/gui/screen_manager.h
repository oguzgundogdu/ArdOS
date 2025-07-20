#pragma once

#include <Adafruit_ILI9341.h>
#include <ardos/gui/menubar.h>
#include <ardos/gui/panel.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/event_listener.h>
#include <vector>

class ScreenManager : public EventListener {
public:
  ScreenManager();
  void draw();
  void onEvent(const Event &e) override;
  void addPanel(Panel *panel);
  Panel *getPanelById(uintptr_t id);
  void start();
  void arrangeWindowStack();

private:
  Adafruit_ILI9341 *tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
  std::vector<Panel *> panels;
  bool needs_redraw = true;
  Panel *focused = nullptr;
  MenuBar *menubar = new MenuBar();
};