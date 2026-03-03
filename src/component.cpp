#include "component.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include <cassert>

namespace game
{


  Component::Component()
  {
    auto& resourceManager = ResourceManager::GetInstance();
    auto renderer = resourceManager.GetResource<Renderer>();
    assert(renderer.has_value() && "Resource not registered <Renderer>");
    this->renderer = renderer->get();
  }

  Component::~Component()
  {
    if(this->renderer)
    {
      this->renderer->removeUpdater(this->updateHandle);
    }
  }
}
