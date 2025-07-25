#pragma once
#include "ardos/process/managed_process.h"

#include <map>

using AppFactory = std::function<ardos::process::ManagedProcess*()>;

class AppRegistry
{
  public:
    static std::map<std::string, AppFactory>& getAppRegistry();
    static void registerApp(const std::string& name, AppFactory factory);

  private:
    static std::map<std::string, AppFactory>* registry;
};
