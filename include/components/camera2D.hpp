#pragma once
#include "component.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace game
{
  class Camera2D : Component
  {
    public:
      static Camera2D* mainCamera;
      Camera2D();
      ~Camera2D();
      glm::mat4 getCameraMatrix();
  };
}
