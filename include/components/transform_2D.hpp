#pragma once

#include "component.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace game
{
  class Transform2D : public game::Component{
    public:
      glm::vec2 position;
      glm::vec2 scale;
      float rotation;
      glm::mat4 applyTransform();
      Transform2D(game::Entity& parent);

  };
}
