
#include "Arduino.h"
#include <ardos/kernel/input.h>

#include <ardos/kernel/event_manager.h> // Include the header for EventManager
#define T_CS 7

XPT2046_Touchscreen ts(T_CS);

namespace input {

void begin() {
  ts.begin();
  ts.setRotation(3); // landscape mode
}

void poll() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    Event e;
    e.type = EventType::Touch;
    e.x = p.x;
    e.y = p.y;

    int16_t screenX = map(p.x, 200, 3800, 0, 320);
    int16_t screenY = map(p.y, 200, 3800, 0, 240);
    e.x = screenX;
    e.y = screenY;

    Serial.print("Touch detected at: ");
    Serial.print(e.x);
    Serial.print(", ");
    Serial.println(e.y);
    ardos::kernel::EventManager::dispatch(e);
  }
}

} // namespace input