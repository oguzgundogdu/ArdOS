
#include <ardos/kernel/event_listener.h>
#include <vector>

namespace ardos::kernel
{

    class EventManager
    {
      public:
        static std::vector<EventListener*> listeners;
        static void dispatch(const Event& event);
        static void registerListener(EventListener* listener);
    };

} // namespace ardos::kernel