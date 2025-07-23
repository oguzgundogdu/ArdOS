#pragma once

class Driver
{
  public:
    virtual void start() = 0;    // Start the driver
    virtual void stop() = 0;     // Stop the driver
    virtual void run() = 0;      // Run the driver logic
    virtual ~Driver() = default; // Virtual destructor for cleanup
};