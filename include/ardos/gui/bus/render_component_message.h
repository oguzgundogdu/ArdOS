#pragma once

#include "ardos/bus/message_bus.h"

#define RENDER_PANEL_MESSAGE "render/Panel"
#define RENDER_CONTAINER_MESSAGE "render/Container"
#define RENDER_MENUBAR_MESSAGE "render/MenuBar"
#define RENDER_CONTEXTMENU_MESSAGE "render/ContextMenu"
#define RENDER_WINDOW_MESSAGE "render/Window"
#define RENDER_BUTTON_MESSAGE "render/Button"

using namespace ardos::bus;

namespace ardos::gui::bus
{
    class RenderComponentMessage : public Message
    {
      public:
        RenderComponentMessage(uint32_t component_id, uint32_t source_pid)
            : Message{MessageType::Render, source_pid}, component_id(component_id)
        {
        }

        uint32_t getComponentId() const
        {
            return component_id;
        }

      private:
        uint32_t component_id;
    };
} // namespace ardos::gui::bus