#pragma once

#include <Adafruit_ILI9341.h>

class Panel
{
  protected:
    int x, y, width, height;
    bool focused = false;

  public:
    Panel(int x, int y, int width, int height);
    virtual void draw(Adafruit_ILI9341& tft) = 0;
    virtual bool contains(int px, int py);
    virtual void onTouch(int16_t tx, int16_t ty); // default empty
    bool intersects(int16_t rx, int16_t ry, int16_t rw, int16_t rh);
    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    int getWidth() const
    {
        return width;
    }
    int getHeight() const
    {
        return height;
    }
    void setFocused(bool state)
    {
        focused = state;
    }
    bool isFocused() const
    {
        return focused;
    }
};
