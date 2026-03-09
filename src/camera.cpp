#include "components/camera2D.hpp"

namespace game
{
  Camera2D::Camera2D()
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
}
