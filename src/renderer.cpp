#include "renderer.hpp"
#include "util/generational_vector.hpp"
#include <GLFW/glfw3.h>

namespace game{


  Renderer::Renderer(Window* window)
  {
    this->window = window;
    this->updaters = utils::GenerationalVector<renderLoopCallback>();
  }

  void Renderer::render(float deltaTime)
  {
    float lastTime = 0.0f; 
    //TODO: pull the loop out of this function so the game loop can be exposed
    //for things like refreshing the input state
    while(!glfwWindowShouldClose(this->window->glfwWindow)){

      glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      //input
      this->orthoProjection = glm::ortho(0.0f, static_cast<float>(this->window->width),
          static_cast<float>(this->window->height), 0.0f, -1.0f, 1.0f);

      float currentTime = glfwGetTime();

      float deltaTime = currentTime - lastTime;

      for(int i = 0; i < this->updaters.elements.size(); i++)
      {
        if(!this->updaters.elements.at(i)){continue;}

        if(this->updaters.elements.at(i))
        {
          this->updaters.elements[i](deltaTime);
        }
      }

      glfwSwapBuffers(this->window->glfwWindow);
      glfwPollEvents();
    }
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
