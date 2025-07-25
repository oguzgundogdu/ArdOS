#pragma once

#include "ardos/gui/menubar.h"
#include <ardos/user/application.h>

using namespace ardos::user;

namespace ardos::app
{
    class Desktop : public Application
    {
      public:
        Desktop();
        ~Desktop();
        void start() override;
        void stop() override;
        void run() override;

      private:
        MenuBar* mMenuBar = nullptr;
    };
} // namespace ardos::app
