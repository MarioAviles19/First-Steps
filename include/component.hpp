#pragma once
#include "renderer.hpp"
class Component : public IRenderUpdater 
{
  public:
    bool enabled;

    ~Component();
  protected:
    Component();
    UpdaterHandle updateHandle;
    Renderer* renderer;
};
