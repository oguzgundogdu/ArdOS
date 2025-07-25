#include "ardos/bus/message_bus.h"

using namespace ardos::bus;

std::map<std::string, std::vector<MessageListener*>>* MessageBus::subscribers =
    new std::map<std::string, std::vector<MessageListener*>>();

void MessageBus::subscribe(const std::string& topic, MessageListener* listener)
{
    (*subscribers)[topic].push_back(listener);
}

void MessageBus::unsubscribe(const std::string& topic, MessageListener* listener)
{
    auto it = subscribers->find(topic);
    if (it != subscribers->end())
    {
        auto& listeners = it->second;
        listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
        if (listeners.empty())
        {
            subscribers->erase(it);
        }
    }
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