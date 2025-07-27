#pragma once

#include <ardos/gui/container.h>
#include <string>

class ContextMenu : public Container
{
  public:
    struct MenuItem
    {
        std::string label;
        Callback callback;
    };

    ContextMenu(int16_t x, int16_t y);

    void AddItem(const std::string& label, const Callback& callback);
    void Init() override;
    void onBlur(Event&) override;

  private:
    static constexpr int ITEM_HEIGHT = 14;
};