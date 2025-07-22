#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace ardos::kernel::bus
{

    enum class MessageType
    {
        Screen
    };

    class Message
    {
      public:
        Message(MessageType type, uint32_t source_pid) : type(type), source_pid(source_pid)
        {
        }

        virtual ~Message() = default;

        MessageType getType() const
        {
            return type;
        }

        uint32_t getSourcePid() const
        {
            return source_pid;
        }

      private:
        MessageType type;
        uint32_t source_pid;
    };

    class MessageListener
    {
      public:
        virtual ~MessageListener() = default;
        virtual void onMessage(const std::string& topic, const Message& message) = 0;
    };

    class MessageBus
    {
      public:
        using Callback = std::function<void(const Message&)>;

        static void subscribe(const std::string& topic, MessageListener* listener);
        static void publish(const std::string& topic, const Message& message);

      private:
        static std::map<std::string, std::vector<MessageListener*>>* subscribers;
    };

} // namespace ardos::kernel::bus