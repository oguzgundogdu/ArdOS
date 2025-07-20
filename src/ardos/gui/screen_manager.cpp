#include "Arduino.h"
#include <ardos/gui/screen_manager.h>
#include <ardos/gui/window.h>
#include <ardos/kernel/state.h>
#include <cstdint>

ScreenManager::ScreenManager() {}

void ScreenManager::start() {
  tft->begin();
  tft->setRotation(1);
  tft->fillScreen(ILI9341_BLACK);

  menubar->draw(*tft);
  menubar->setCallback([this]() {
    uintptr_t activePanel = ardos::kernel::state.active_panel_id;
    int16_t lastX = 0;
    int16_t lastY = 0;
    if (activePanel != 0) {
      Panel *activePanelPtr = getPanelById(activePanel);
      if (activePanelPtr) {
        lastX = activePanelPtr->getX();
        lastY = activePanelPtr->getY();
      }
    }

    auto targetX = lastX + 20;
    auto targetY = lastY + 20;
    if (targetX + 120 > 320) {
      targetX = 0;
    }
    if (targetY + 60 > 240) {
      targetY = 0;
    }

    Window *w = new Window(targetX, targetY, 120, 60, "Test Window");
    this->addPanel(w);
  });
}

void ScreenManager::draw() {
  if (!needs_redraw)
    return;
  needs_redraw = false;

  arrangeWindowStack();

  for (auto *p : panels) {
    p->draw(*tft);
  }
}

void ScreenManager::addPanel(Panel *panel) {
  panels.push_back(panel);
  Serial.print("Panel added: ");
  Serial.println((uintptr_t)panel);
  ardos::kernel::state.active_panel_id = (uintptr_t)panel;
  focused = panel;
  panel->setFocused(true);
  needs_redraw = true;
}

void ScreenManager::onEvent(const Event &e) {
  switch (e.type) {
  case EventType::Touch:
    Serial.print("Touch event at: ");
    Serial.print(e.x);
    Serial.print(", ");
    Serial.println(e.y);

    if (menubar->contains(e.x, e.y)) {
      Serial.println("Menu bar touched");
      menubar->onTouch(e.x, e.y);
      needs_redraw = true;
      return; // Menu bar handled the touch
    }
    for (auto *p : panels) {

      if (p == nullptr) {
        Serial.println("Touch: Null panel found, skipping");
        continue;
      }

      Serial.print("Checking panel: ");
      Serial.println((uintptr_t)p);

      if (p->contains(e.x, e.y)) {
        Serial.print("Panel found: ");
        Serial.println((uintptr_t)p);

        // Bring to front (end of list)
        panels.erase(std::remove(panels.begin(), panels.end(), p),
                     panels.end());
        panels.push_back(p);
        focused = p;
        p->setFocused(true);

        p->onTouch(e.x, e.y);
        needs_redraw = true;
      } else if (needs_redraw) {
        p->setFocused(false);
      }
    }

    break;
  case EventType::Kill:
    for (auto *p : panels) {

      if (p == nullptr) {
        Serial.println("Kill: Null panel found, skipping");
        continue;
      }

      uintptr_t panelPtr = (uintptr_t)p;

      if (e.id != 0 && panelPtr == e.id) {
        int16_t px = p->getX();
        int16_t py = p->getY();
        int16_t pw = p->getWidth();
        int16_t ph = p->getHeight();

        // Remove the panel from the list
        auto it = std::remove(panels.begin(), panels.end(), p);
        if (it != panels.end()) {
          panels.erase(it);
          Serial.println("Panel removed");

          // Clear the area
          tft->fillRect(px, py, pw, ph, ILI9341_BLACK);

          std::vector<Panel *> toRedraw;
          for (auto it = panels.begin(); it != panels.end();) {
            if ((*it)->intersects(px, py, pw, ph)) {
              toRedraw.push_back(*it);
              it = panels.erase(it);
            } else {
              ++it;
            }
          }
          for (auto *p : toRedraw) {
            panels.push_back(p);
            p->draw(*tft);
          }
        }
      }
    }
    break;
  }
}

Panel *ScreenManager::getPanelById(uintptr_t id) {
  for (auto *p : panels) {
    if ((uintptr_t)p == id) {
      return p;
    }
  }
  return nullptr;
}

void ScreenManager::arrangeWindowStack() {
  Panel *lastPanel = panels.empty() ? nullptr : panels.back();
  if (lastPanel) {
    focused = lastPanel;
    lastPanel->setFocused(true);
    ardos::kernel::state.active_panel_id = (uintptr_t)lastPanel;
  } else {
    focused = nullptr;
    ardos::kernel::state.active_panel_id = 0;
  }
}