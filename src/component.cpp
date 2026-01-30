#include "component.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include <cassert>

Component::Component()
{
  auto renderer = ResourceManager::GetInstance().GetResource<Renderer>();

  assert(renderer.has_value() && "Resource not registered <Renderer>");
  this->renderer = renderer->get();
  this->updateHandle = this->renderer->addUpdater(this);
}

Component::~Component()
{
  if(this->renderer)
  {
    this->renderer->removeUpdater(this->updateHandle);
  }
}
