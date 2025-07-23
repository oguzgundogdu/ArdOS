#pragma once

namespace ardos::kernel
{
    class Kernel
    {
      public:
        Kernel();
        void start();
        void stop();
        void run();
        static Kernel* getInstance();

      private:
        void initializeDrivers();
        void initializeProcesses();
        static Kernel* instance;

        // Add other kernel-related methods and members as needed
    };
} // namespace ardos::kernel