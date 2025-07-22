#include "ardos/kernel/bus/message_bus.h"

using namespace ardos::kernel::bus;

std::map<std::string, std::vector<MessageListener*>>* MessageBus::subscribers =
    new std::map<std::string, std::vector<MessageListener*>>();

void MessageBus::subscribe(const std::string& topic, MessageListener* listener)
{
    (*subscribers)[topic].push_back(listener);
}

void MessageBus::publish(const std::string& topic, const Message& message)
{
    auto it = subscribers->find(topic);
    if (it != subscribers->end())
    {
        for (auto* listener : it->second)
        {
            listener->onMessage(topic, message);
        }
    }
}