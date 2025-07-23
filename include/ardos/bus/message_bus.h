#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace ardos::bus
{

    enum class MessageType : uint16_t
    {
        Display = 1 << 0,
        Render = 1 << 1,
        Input = 1 << 2,
        Time = 1 << 3
    };

    class Message
    {
      public:
        Message(MessageType type, uint32_t source_pid = 0) : type(type), source_pid(source_pid)
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

} // namespace ardos::bus