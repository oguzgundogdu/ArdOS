#pragma once
#include <ardos/gui/panel.h>

class Container : public Panel
{
  public:
    Container(int x, int y, int width, int height);
    ~Container() override;

    void render() override;
    void onTouch(int16_t tx, int16_t ty) override;

    void addChild(Panel* panel);
    void removeChild(Panel* panel);
    const std::vector<Panel*>& getChildren() const
    {
        return *children;
    }

  private:
    std::vector<Panel*>* children = new std::vector<Panel*>();
};