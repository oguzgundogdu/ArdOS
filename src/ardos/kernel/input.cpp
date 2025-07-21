
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

namespace {
bool wasTouched = false;
int16_t last_x = -1;
int16_t last_y = -1;
} // namespace

void poll() {
  bool touching = ts.touched();

  if (touching) {
    TS_Point p = ts.getPoint();
    int16_t screenX = map(p.x, 200, 3800, 0, 320);
    int16_t screenY = map(p.y, 200, 3800, 0, 240);

    Event e;
    e.x = screenX;
    e.y = screenY;

    if (!wasTouched) {
      e.type = EventType::TouchStart;
      wasTouched = true;
    } else {
      if (abs(screenX - last_x) > 2 || abs(screenY - last_y) > 2) {
        e.type = EventType::TouchMove;
      } else {
        return;
      }
    }

    last_x = screenX;
    last_y = screenY;
    ardos::kernel::EventManager::dispatch(e);

  } else if (wasTouched) {
    Event e;
    e.x = last_x;
    e.y = last_y;
    e.type = EventType::TouchEnd;
    wasTouched = false;
    ardos::kernel::EventManager::dispatch(e);
  }
}

} // namespace input