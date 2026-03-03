#include "entity.hpp"
#include "component.hpp"
namespace game
{
  Entity::Entity() : transform(){
    transform->entity = this;
  }
  }
