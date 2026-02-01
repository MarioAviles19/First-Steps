#include "components/transform_2D.hpp"
#include "component.hpp"
#include <glm/fwd.hpp>

namespace game
{
  Transform2D::Transform2D(game::Entity& parent) : game::Component(parent){

  };
  glm::mat4 Transform2D::getModel()
  {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(scale, 1.0f));

    return model;
  }
}
