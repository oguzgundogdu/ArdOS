#pragma once

#include <ardos/gui/panel.h>
#include <functional>
#include <string>
#include <vector>

class ContextMenu : public Panel
{
  public:
    using Callback = std::function<void()>;

    struct MenuItem
    {
        std::string label;
        Callback callback;
    };

    ContextMenu(int16_t x, int16_t y);

    void addItem(const std::string& label, Callback callback);
    void render() override;
    void onTouch(int16_t tx, int16_t ty) override;

  private:
    std::vector<MenuItem> items;
    static constexpr int ITEM_HEIGHT = 14;
};