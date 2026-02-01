#pragma once

#include "component.hpp"
#include <glm/gtc/matrix_transform.hpp>
class Transform2D : public Component{
  public:
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
    glm::mat4 applyTransform();
  

};
