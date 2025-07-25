#include "ardos/gui/menubar.h"
#include <ardos/app/desktop.h>

using namespace ardos::app;

Desktop::Desktop() : Application()
{
}

Desktop::~Desktop()
{
    delete mMenuBar;
}

void Desktop::start()
{
    mMenuBar = new MenuBar();
    mMenuBar->Init();
}

void Desktop::stop()
{
    if (mMenuBar)
    {
        delete mMenuBar;
        mMenuBar = nullptr;
    }
}

void Desktop::run()
{
}
