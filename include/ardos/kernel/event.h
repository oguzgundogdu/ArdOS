#include <cstdint>
enum class EventType
{
    Kill,
    Focus,
    Custom,
    TouchStart,
    TouchMove,
    TouchEnd
};

struct Event
{
    EventType type; // Exp: Touch
    int16_t x, y;
    uintptr_t id;         // Unique identifier for the event
    void* data = nullptr; // Additional data if needed
};