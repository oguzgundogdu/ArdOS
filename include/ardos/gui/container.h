#pragma once
#include <ardos/gui/panel.h>

class Container : public Panel
{
  public:
    Container(int x, int y, int width, int height);
    ~Container() override;

    void onTouch(void* data = nullptr) override;

    void AddChild(Panel* panel);
    void RemoveChild(Panel* panel);
    const std::vector<Panel*>& GetChildren() const
    {
        return *mChildren;
    }

  private:
    std::vector<Panel*>* mChildren = new std::vector<Panel*>();
};