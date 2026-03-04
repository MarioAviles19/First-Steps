#include "renderer.hpp"
#include "util/generational_vector.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace game{


  Renderer::Renderer(Window* window)
  {
    this->window = window;
    this->updaters = utils::GenerationalVector<renderLoopCallback>();
  }

  void Renderer::render(float deltaTime)
  {
      glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      this->orthoProjection = glm::ortho(0.0f, static_cast<float>(this->window->width),
          static_cast<float>(this->window->height), 0.0f, -1.0f, 1.0f);


    
  }
  utils::GenVectorHandle Renderer::addUpdater(renderLoopCallback updater)
  {
    return updaters.add(updater);
  }

  void Renderer::removeUpdater(utils::GenVectorHandle handle)
  {
    updaters.remove(handle);
  }

}
