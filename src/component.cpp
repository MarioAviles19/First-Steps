#include "component.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include <cassert>
#include <iostream>

Component::Component()
{
  auto& resourceManager = ResourceManager::GetInstance();
  auto renderer = resourceManager.GetResource<Renderer>();
  std::cout << "Comp has value: " << renderer.has_value() << std::endl;
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
bool Component::getEnabled() const {return this->enabled;}
