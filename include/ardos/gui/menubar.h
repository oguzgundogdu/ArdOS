#pragma once

#include <ardos/gui/panel.h>
#include <functional>

class MenuBar : public Panel
{
  public:
    MenuBar();

    void draw(Adafruit_ILI9341& tft) override;
    void onTouch(int16_t tx, int16_t ty) override;

    void setCallback(std::function<void()> cb);

  private:
    std::function<void()> callback;
    String getFormattedTime();
};