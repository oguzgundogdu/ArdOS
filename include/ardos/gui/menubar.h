#pragma once

#include "ardos/gui/button.h"
#include "ardos/gui/contextmenu.h"
#include <ardos/gui/panel.h>
#include <functional>

class MenuBar : public Panel
{
  public:
    MenuBar();

    void render() override;
    void onTouch(int16_t tx, int16_t ty) override;

  private:
    ContextMenu* mMenu = nullptr;
    Button* mButton = nullptr;
    std::function<void()> callback;
    String getFormattedTime();
};