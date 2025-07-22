#include "ardos/kernel/process.h"
#include "Arduino.h"

using namespace ardos::kernel;

Process::Process(const std::string& name, ProcessContext* context, Application* app)
    : name(name), context(context), pid(PidManager::allocatePid()), state(ProcessState::Created), app(app)
{
}

void Process::start()
{
    if (state == ProcessState::Created || state == ProcessState::Stopped)
    {
        app->start(context);
        state = ProcessState::Running;
        Serial.print("Process started: ");
        Serial.println(name.c_str());
    }
}

void Process::stop()
{
    if (state == ProcessState::Running)
    {
        app->stop();
        Serial.print("Process stopped: ");
        Serial.println(name.c_str());
    }
    PidManager::releasePid(pid);
    context->memory.clear(); // Clear process memory
    Serial.print("Process memory cleared for: ");
    Serial.println(name.c_str());
    context = nullptr; // Clear context
    app = nullptr;     // Clear application reference
    Serial.print("Process context cleared for: ");
    Serial.println(name.c_str());
    // Set state to stopped
    Serial.print("Process state set to Stopped for: ");
    Serial.println(name.c_str());
    state = ProcessState::Stopped;
}

uint32_t Process::getPid() const
{
    return pid;
}

ProcessState Process::getState() const
{
    return state;
}

const std::string& Process::getName() const
{
    return name;
}

ProcessContext* Process::getContext() const
{
    return context;
}

void Process::tick()
{
    if (state == ProcessState::Running)
    {
        app->run();
    }
}