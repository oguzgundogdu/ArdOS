#pragma once

#include <ardos/gui/panel.h>
#include <string>

class Button : public Panel
{
  public:
    void Init() override;
    Button(int16_t x, int16_t y, int16_t w, int16_t h, const std::string& label);
    void onBlur(Event&) override;
    void onTouch(Event&) override;
    std::string GetLabel() const
    {
        return mLabel;
    }

  private:
    std::string mLabel;
};