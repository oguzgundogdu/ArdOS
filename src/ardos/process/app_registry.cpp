#include "ardos/process/app_registry.h"

std::map<std::string, AppFactory>* AppRegistry::registry = new std::map<std::string, AppFactory>();

std::map<std::string, AppFactory>& AppRegistry::getAppRegistry()
{
    static std::map<std::string, AppFactory> registry;
    return registry;
}

void AppRegistry::registerApp(const std::string& name, AppFactory factory)
{
    getAppRegistry()[name] = factory;
}