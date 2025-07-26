#include "Arduino.h"
#include <ardos/gui/menubar.h>

MenuBar::MenuBar() : Container(0, 0, MENU_WIDTH, MENU_HEIGHT)
{
    setBackgroundColor(MENU_BG_COLOR);
    setBorderColor(MENU_BG_COLOR);
    setColor(MENU_TEXT_COLOR);
    mButton = new Button(0, 0, 50, MENU_HEIGHT, "Menu");
    mButton->setBackgroundColor(MENU_BG_COLOR);
    mButton->setBorderColor(MENU_BG_COLOR);
    mButton->setColor(MENU_TEXT_COLOR);
    mButton->setCallback(
        [this]()
        {
            Serial.println("Menu button clicked");
            if (mMenu)
            {
                toggleContextMenu();
            }
            else
            {
                mMenu = new ContextMenu(0, MENU_HEIGHT);
                mMenu->AddItem("File Explorer",
                               [&]()
                               {
                                   
                               });
                mMenu->AddItem("Settings", []() {});
                mMenu->AddItem("About", []() {});
                AddChild(mMenu);
                mMenu->Init();
            }
        });
    AddChild(mButton);
}

void MenuBar::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderMenuBar, 0, 0, (uintptr_t)this, this,
    };
    eventDispatcher->dispatch(event);

    for (auto* child : GetChildren())
    {
        if (child)
        {
            child->Init();
        }
    }
}

/*void MenuBar::render()
{
    Screen* screen = Screen::getInstance();



    screen->setCursor(MENU_WIDTH - 40, y + 4);
    auto timeStr = getFormattedTime();
    Serial.print("Current time: ");
    Serial.println(timeStr.c_str());
    screen->print(timeStr.c_str());
    Serial.println("MenuBar rendered");
}*/

/*std::string MenuBar::getFormattedTime()
{
    DateTime now = ardos::kernel::RTC::Now();

    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", now.hour(), now.minute());
    return std::string(buf);
}*/