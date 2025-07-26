#pragma once

#include "ardos/gui/button.h"
#include "ardos/gui/contextmenu.h"
#include <functional>

#define MENU_HEIGHT 20
#define MENU_WIDTH 320
#define MENU_BG_COLOR ILI9341_DARKCYAN
#define MENU_TEXT_COLOR ILI9341_WHITE

class MenuBar : public Container
{
  public:
    MenuBar();
    void Init() override;

  private:
    ContextMenu* mMenu = nullptr;
    Button* mButton = nullptr;
    std::function<void()> mCallback;
    std::string getFormattedTime();
    void toggleContextMenu()
    {
        if (mMenu)
        {
            mMenu->setVisible(!mMenu->isVisible());
            mMenu->Init();
        }
    }
};