// include/ardos/kernel/state.h
#pragma once

#include <cstdint>
namespace ardos::ui
{
    class Panel;
} // namespace ardos::ui

namespace ardos::kernel
{

    struct State
    {
        uintptr_t active_panel_id = 0;
        uintptr_t focused_panel_id = 0;
        uintptr_t hovered_panel_id = 0;
        bool is_touch_down = false;
    };

    extern State state;

} // namespace ardos::kernel