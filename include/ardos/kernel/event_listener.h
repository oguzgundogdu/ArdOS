#pragma once

#include <ardos/kernel/event.h>

class EventListener {
public:
  virtual void onEvent(const Event &e) = 0;
};