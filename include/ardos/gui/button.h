#pragma once

#include <ardos/gui/panel.h>
#include <functional>
#include <string>

class Button : public Panel
{
  public:
    using Callback = std::function<void()>;

    Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label);

    void render() override;

  private:
    std::string label;
};