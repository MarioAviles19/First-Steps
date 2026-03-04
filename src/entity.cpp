#include "entity.hpp"
#include "component.hpp"
#include <memory>
namespace game
{
  Entity::Entity() : transform(std::make_unique<Transform2D>()){
    transform->entity = this;
  }
  }
