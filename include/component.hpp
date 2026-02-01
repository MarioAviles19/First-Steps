#pragma once
#include "renderer.hpp"
class Component : public IRenderUpdater 
{
  public:
    bool enabled;
    bool getEnabled() const override;
    ~Component();
  protected:
    Component();
    UpdaterHandle updateHandle;
    Renderer* renderer;
};
