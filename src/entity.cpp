#include "entity.hpp"
#include "component.hpp"
#include <concepts>
#include <memory>
namespace game
{
  Entity::Entity() : transform(*this){

  }
  template <typename T>
    requires std::derived_from<T, game::Component>
    T& Entity::addComponent()
    {
      auto& ptr = components.emplace_back(std::make_unique<T>(*this));
      return static_cast<T&>(ptr);
    }
}
