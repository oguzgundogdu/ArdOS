#include <ardos/gui/panel.h>

Panel::Panel(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {}

bool Panel::contains(int px, int py) {
  return (px >= x && px < x + width && py >= y && py < y + height);
}

void Panel::onTouch(int16_t tx, int16_t ty) {
  // default: do nothing
}
bool Panel::intersects(int16_t rx, int16_t ry, int16_t rw, int16_t rh) {
  return !(x + width < rx || x > rx + rw || y + height < ry || y > ry + rh);
}