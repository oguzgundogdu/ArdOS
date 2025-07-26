#pragma once

#include <ardos/gui/container.h>
#include <functional>
#include <string>

class ContextMenu : public Container
{
  public:
    using Callback = std::function<void()>;

    struct MenuItem
    {
        std::string label;
        Callback callback;
    };

    ContextMenu(int16_t x, int16_t y);

    void AddItem(const std::string& label, const Callback& callback);
    void Init() override;
    void onBlur(void* data = nullptr) override;

  private:
    static constexpr int ITEM_HEIGHT = 14;
};