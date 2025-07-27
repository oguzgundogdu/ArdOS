#pragma once

#include "ardos/bus/message_bus.h"

#define RENDER_PANEL_MESSAGE "render/Panel"
#define RENDER_CONTAINER_MESSAGE "render/Container"
#define RENDER_MENUBAR_MESSAGE "render/MenuBar"
#define RENDER_CONTEXTMENU_MESSAGE "render/ContextMenu"
#define RENDER_WINDOW_MESSAGE "render/Window"
#define RENDER_BUTTON_MESSAGE "render/Button"
#define RENDER_LABEL_MESSAGE "render/Label"

using namespace ardos::bus;

namespace ardos::gui::bus
{
    class RenderComponentMessage : public Message
    {
      public:
        RenderComponentMessage(void* component, uint32_t source_pid)
            : Message{MessageType::Render, source_pid}, mComponent(component)
        {
        }

        void* getComponent() const
        {
            return mComponent;
        }

      private:
        void* mComponent = nullptr; // Pointer to the component to be rendered
    };
} // namespace ardos::gui::bus