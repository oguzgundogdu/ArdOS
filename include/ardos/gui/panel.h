#pragma once

#include "Adafruit_ILI9341.h"
#include <ardos/gui/event.h>
#include <cstdint>
#include <functional>

using namespace ardos::gui::event;

class Panel : public ComponentEventListener
{
  protected:
    using Callback = std::function<void()>;
    int x, y, width, height;
    bool focused = false;
    bool is_visible = true;
    Callback mCallback;
    int color = ILI9341_WHITE;           // Default color
    int backgroundColor = ILI9341_BLACK; // Default background color
    int borderColor = ILI9341_WHITE;     // Default border color
    void onTouch(void* data = nullptr) override;

  public:
    Panel(int x, int y, int width, int height);
    virtual ~Panel();
    virtual bool contains(int px, int py);
    virtual void Init();

    bool intersects(int16_t rx, int16_t ry, int16_t rw, int16_t rh);

    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    void setX(int newX)
    {
        x = newX;
    }
    void setY(int newY)
    {
        y = newY;
    }
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }
    int getWidth() const
    {
        return width;
    }
    int getHeight() const
    {
        return height;
    }
    void setSize(int newWidth, int newHeight)
    {
        width = newWidth;
        height = newHeight;
    }
    void setDimensions(int newX, int newY, int newWidth, int newHeight)
    {
        x = newX;
        y = newY;
        width = newWidth;
        height = newHeight;
    }
    void setFocused(bool state)
    {
        focused = state;
    }
    bool isFocused() const
    {
        return focused;
    }

    void setVisible(bool visible);
    bool isVisible() const
    {
        return is_visible;
    }

    void setCallback(Callback cb)
    {
        mCallback = std::move(cb);
    }

    Callback getCallback() const
    {
        return mCallback;
    }

    void setColor(int newColor)
    {
        color = newColor;
    }
    int getColor() const
    {
        return color;
    }

    void setBackgroundColor(int newBackgroundColor)
    {
        backgroundColor = newBackgroundColor;
    }
    int getBackgroundColor() const
    {
        return backgroundColor;
    }
    void setBorderColor(int newBorderColor)
    {
        borderColor = newBorderColor;
    }
    int getBorderColor() const
    {
        return borderColor;
    }
};
