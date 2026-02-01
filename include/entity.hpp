#pragma once

#include "component.hpp"
#include "components/transform_2D.hpp"
#include <memory>
#include <vector>

namespace game{
  
  class Entity
  {
    public:
      game::Transform2D transform;
      Entity();

      template <typename T>
        requires std::derived_from<T, game::Component>
        T& addComponent()
        {
          auto& ptr = components.emplace_back(std::make_unique<T>(*this));
          return static_cast<T&>(*ptr);
        }

    private:
      std::vector<std::unique_ptr<game::Component>> components;
  };
};
