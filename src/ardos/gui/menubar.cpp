#include "Arduino.h"
#include <ardos/gui/menubar.h>
#include <ardos/kernel/config.h>
#include <ardos/kernel/rtc.h>
#include <ardos/kernel/screen.h>

MenuBar::MenuBar() : Panel(0, 0, MENU_WIDTH, MENU_HEIGHT)
{
    mButton = new Button(0, 0, 50, MENU_HEIGHT, "Menu");
    mButton->setCallback(
        [this]()
        {
            if (mMenu)
            {
                mMenu->render();
                // mMenu->onTouch(0, 0); // Simulate touch to open menu
            }
        });
    mMenu = new ContextMenu(0, MENU_HEIGHT);
    mMenu->addItem("File Explorer", []() { Serial.println("File Explorer selected"); });
    mMenu->addItem("Settings", []() { Serial.println("Settings selected"); });
    mMenu->addItem("About", []() { Serial.println("About selected"); });
}

void MenuBar::render()
{
    Screen* screen = Screen::getInstance();
    screen->fillRect(x, y, width, height, MENU_BG_COLOR);
    screen->setCursor(x + 4, y + 4);
    screen->setTextColor(MENU_TEXT_COLOR);
    screen->setTextSize(1);
    mButton->render();

    screen->setCursor(MENU_WIDTH - 40, y + 4);
    auto timeStr = getFormattedTime();
    Serial.print("Current time: ");
    Serial.println(timeStr);
    screen->print(timeStr.c_str());
}

void MenuBar::onTouch(int16_t tx, int16_t ty)
{
    if (contains(tx, ty))
    {
        if (mCallback)
        {
            mCallback();
        }

        mButton->onTouch(tx, ty);
    }
}

String MenuBar::getFormattedTime()
{
    DateTime now = ardos::kernel::RTC::Now();

    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", now.hour(), now.minute());
    return String(buf);
}