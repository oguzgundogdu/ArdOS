#pragma once

#include "panel.h"
#include <string>

class Label : public Panel
{
  public:
    Label(const std::string& text, int x, int y, int width, int height);

    void Init() override;

  protected:
    std::string text;

  public:
    void SetText(const std::string& newText)
    {
        text = newText;
    }
    const std::string& GetText() const
    {
        return text;
    }
};