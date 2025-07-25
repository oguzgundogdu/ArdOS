#include "ardos/kernel/process.h"

using namespace ardos::kernel;

Process::Process(const std::string& name, ProcessContext* context, ManagedProcess* app)
    : name(name), context(context), pid(PidManager::allocatePid()), state(ProcessState::Created), app(app)
{
}

void Process::start()
{
    if (state == ProcessState::Created || state == ProcessState::Stopped)
    {
        app->start();
        state = ProcessState::Running;
    }
}

void Process::stop()
{
    if (state == ProcessState::Running)
    {
        app->stop();
    }
    PidManager::releasePid(pid);
    context->memory.clear(); // Clear process memory

    context = nullptr; // Clear context
    app = nullptr;     // Clear application reference
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

ManagedProcess* Process::getApplication() const
{
    return app;
}

void Process::tick()
{
    if (state == ProcessState::Running)
    {
        app->run();
    }
}
