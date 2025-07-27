#include "Arduino.h"
#include "ardos/user/event.h"
#include <ardos/gui/label.h>
#include <ardos/gui/menubar.h>
#include <ardos/gui/window.h>

MenuBar::MenuBar() : Container(0, 0, MENU_WIDTH, MENU_HEIGHT)
{
    this->getEventDispatcher()->registerListener(EventType::TimeChange, this);
    setBackgroundColor(MENU_BG_COLOR);
    setBorderColor(MENU_BG_COLOR);
    setColor(MENU_TEXT_COLOR);
    mButton = new Button(0, 0, 50, MENU_HEIGHT, "Menu");
    mButton->setBackgroundColor(MENU_BG_COLOR);
    mButton->setBorderColor(MENU_BG_COLOR);
    mButton->setColor(MENU_TEXT_COLOR);
    mButton->setCallback(
        [this](Event& e)
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
                               [&](Event& e)
                               {
                                   mMenu->setVisible(false);
                                   mMenu->Init();
                                   Window* fileExplorer = new Window(0, MENU_HEIGHT + 20, 200, 150, "File Explorer");
                                   fileExplorer->Init();
                               });
                mMenu->AddItem("Settings", [](Event& e) {});
                mMenu->AddItem("About", [](Event& e) {});
                AddChild(mMenu);
                mMenu->Init();
            }
        });
    AddChild(mButton);
    lblTime = new Label("--:--", MENU_WIDTH - 40, 0, 40, MENU_HEIGHT);
    lblTime->setBackgroundColor(MENU_BG_COLOR);
    lblTime->setBorderColor(MENU_BG_COLOR);
    lblTime->setColor(MENU_TEXT_COLOR);
    AddChild(lblTime);
}

void MenuBar::Init()
{
    auto* eventDispatcher = getEventDispatcher();
    Event event{
        EventType::RenderMenuBar, 0, 0, eventDispatcher->getEventSeq(), this,
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

void MenuBar::onTimeTick(Event& e)
{
    std::string timeStr = e.data ? *static_cast<std::string*>(e.data) : "--:--";
    lblTime->SetText(timeStr);
    lblTime->Init();
}