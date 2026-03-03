#pragma once

#include "cereal/access.hpp"
#include "cereal/cereal.hpp"
#include "component.hpp"
#include "components/transform_2D.hpp"
#include <memory>
#include <vector>

namespace game{
  
  class Entity
  {
    public:
      std::unique_ptr<game::Transform2D> transform;
      Entity();

      template <typename T>
        requires std::derived_from<T, game::Component>
        T& addComponent()
        {
          auto& ptr = components.emplace_back(std::make_unique<T>(*this));
          return static_cast<T&>(*ptr);
        }
   template <class Archive>
        void serialize(Archive& archive)
        {
          archive(CEREAL_NVP(*transform));
        }

      //TODO: add removeComponent function
    private:
      friend class cereal::access;
         std::vector<std::unique_ptr<game::Component>> components;
  };
};
