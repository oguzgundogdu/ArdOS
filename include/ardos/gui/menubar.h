#pragma once

#include "ardos/gui/button.h"
#include "ardos/gui/contextmenu.h"
#include <functional>

class MenuBar : public Container
{
  public:
    MenuBar();

    void render() override;

  private:
    ContextMenu* mMenu = nullptr;
    Button* mButton = nullptr;
    std::function<void()> callback;
    std::string getFormattedTime();
    void toggleContextMenu()
    {
        if (mMenu)
        {
            mMenu->setVisible(!mMenu->isVisible());
        }
    }
};