#include <ardos/gui/panel.h>

class Container : public Panel
{
  public:
    Container(int x, int y, int width, int height);

    void render() override;
    void onTouch(int16_t tx, int16_t ty) override;

    void addChild(Panel* panel);
    void removeChild(Panel* panel);

  private:
    std::vector<Panel*> children;
};