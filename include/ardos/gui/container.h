#pragma once
#include <ardos/gui/panel.h>

class Container : public Panel
{
  public:
    Container(int x, int y, int width, int height);
    ~Container() override;

    void onTouch(Event&) override;
    void Init() override;
    void AddChild(Panel* panel);
    void RemoveChild(Panel* panel);
    void setVisible(bool visible) override
    {
        Panel::setVisible(visible);
        for (auto* child : *mChildren)
        {
            if (child)
            {
                child->setVisible(visible);
            }
        }
    }
    const std::vector<Panel*>& GetChildren() const
    {
        return *mChildren;
    }

  private:
    std::vector<Panel*>* mChildren = new std::vector<Panel*>();
};