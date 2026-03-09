#include "component.hpp"
#include "components/camera2D.hpp"
#include "entity.hpp"

namespace game
{
  Camera2D::Camera2D() : game::Component()
  {
    if(!Camera2D::mainCamera)
    {
      Camera2D::mainCamera = this;
    }
  }
  Camera2D::~Camera2D()
  {
    if(Camera2D::mainCamera == this)
    {
      Camera2D::mainCamera = nullptr;
    }
  }
  glm::mat4 Camera2D::getCameraMatrix()
  {
    return this->entity->transform->getModel();
  }
}
