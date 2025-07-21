#include <cstdint>
enum class EventType
{
    Kill,
    TouchStart,
    TouchMove,
    TouchEnd,
    TimeChanged,
    SleepRequest,
    WakeRequest,
    PowerSaveRequest,
};

struct Event
{
    EventType type; // Exp: Touch
    int16_t x, y;
    uintptr_t id;         // Unique identifier for the event
    void* data = nullptr; // Additional data if needed
};