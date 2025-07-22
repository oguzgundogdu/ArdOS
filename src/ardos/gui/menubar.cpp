#include "Arduino.h"
#include "ardos/gui/gui_manager.h"
#include <ardos/gui/menubar.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/rtc.h>

MenuBar::MenuBar() : Container(0, 0, MENU_WIDTH, MENU_HEIGHT)
{
    Serial.println("Creating MenuBar");

    mButton = new Button(0, 0, 50, MENU_HEIGHT, "Menu");
    mButton->setBackgroundColor(MENU_BG_COLOR);
    mButton->setBorderColor(MENU_BG_COLOR);
    mButton->setColor(MENU_TEXT_COLOR);
    mButton->setCallback(
        [this]()
        {
            if (mMenu)
            {
                toggleContextMenu();
            }
            else
            {
                mMenu = new ContextMenu(0, MENU_HEIGHT);
                mMenu->addItem("File Explorer",
                               [&]()
                               {
                                   GuiManager* guiManager = GuiManager::getInstance();
                                   guiManager->CreateWindow("File Explorer", 200, 150);
                                   mMenu->setVisible(false);
                               });
                mMenu->addItem("Settings", []() { Serial.println("Settings selected"); });
                mMenu->addItem("About", []() { Serial.println("About selected"); });
                addChild(mMenu);

                mMenu->render();
            }
        });
    addChild(mButton);

    Serial.println("MenuBar created");
}

void MenuBar::render()
{
    Serial.println("Rendering MenuBar");
    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, MENU_BG_COLOR);
    screen->setCursor(x + 4, y + 4);
    screen->setTextColor(MENU_TEXT_COLOR);
    screen->setTextSize(1);
    mButton->render();

    screen->setCursor(MENU_WIDTH - 40, y + 4);
    auto timeStr = getFormattedTime();
    Serial.print("Current time: ");
    Serial.println(timeStr.c_str());
    screen->print(timeStr.c_str());
    Serial.println("MenuBar rendered");
}

std::string MenuBar::getFormattedTime()
{
    DateTime now = ardos::kernel::RTC::Now();

    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", now.hour(), now.minute());
    return std::string(buf);
}