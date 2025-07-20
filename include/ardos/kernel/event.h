#include <cstdint>
enum class EventType { Touch, Kill, Drag, Focus, Custom };

struct Event {
  EventType type; // Exp: Touch
  int16_t x, y;
  uintptr_t id;         // Unique identifier for the event
  void *data = nullptr; // Additional data if needed
};