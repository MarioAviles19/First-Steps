#pragma once

#include "components/transform_2D.hpp"

namespace game{
  
  class Entity
  {
    public:
      game::Transform2D transform;
      Entity();
  };
};
