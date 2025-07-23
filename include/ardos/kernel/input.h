#pragma once

#include "ardos/bus/message_bus.h"

namespace ardos::kernel {
class InputManager : public ardos::bus::MessageListener {
public:
  InputManager();
  void onMessage(const std::string &topic,
                 const ardos::bus::Message &message) override;

  static InputManager *getInstance() {
    static InputManager instance;
    return &instance;
  }

private:
  bool wasTouched = false;
  int16_t last_x = -1;
  int16_t last_y = -1;
  tm last_touch_time;
  void handleTouch(const ardos::bus::Message &message);
  void handleTouchStart(const ardos::bus::Message &message);
  void handleTouchMove(const ardos::bus::Message &message);
  void handleTouchEnd(const ardos::bus::Message &message);
};
} // namespace ardos::kernel