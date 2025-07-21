#pragma once

#include <ardos/kernel/event.h>

class EventListener {
public:
  virtual void OnEvent(const Event &e) = 0;
};