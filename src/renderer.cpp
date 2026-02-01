#include "renderer.hpp"
#include <GLFW/glfw3.h>
#include <cstdint>

namespace game{


  Renderer::Renderer(Window* window)
  {
    this->window = window;
  }

  void Renderer::render()
  {
    float lastTime = 0.0f; 
    while(!glfwWindowShouldClose(this->window->glfwWindow)){

      glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      //input
      this->orthoProjection = glm::ortho(0.0f, static_cast<float>(this->window->width),
          static_cast<float>(this->window->height), 0.0f, -1.0f, 1.0f);

      float currentTime = glfwGetTime();

      float deltaTime = currentTime - lastTime;

      for(int i = 0; i < this->updaters.size(); i++)
      {
        if(!this->updaters.at(i)){continue;}

        if(this->updaters.at(i)->getEnabled())
        {
          this->updaters.at(i)->update(deltaTime);
        }
      }

      glfwSwapBuffers(this->window->glfwWindow);
      glfwPollEvents();
    }
  }
  UpdaterHandle Renderer::addUpdater(IRenderUpdater* updater)
  {
    if(!this->freeList.empty())
    {
      uint32_t idx = freeList.back();
      this->freeList.pop_back();

      this->updaters[idx] = updater; 
      return {idx, this->generations[idx]};
    }
    uint32_t idx = this->updaters.size();
    this->updaters.push_back(updater);
    this->generations.push_back(0);
    return {idx, 0};
  }

  void Renderer::removeUpdater(UpdaterHandle handle)
  {
    if(handle.index >= this->updaters.size())
    {
      return;
    }
    if(this->generations[handle.index] != handle.generation)
    {
      return;
    }
    this->updaters[handle.index] = nullptr;
    this->generations[handle.index]++;
    this->freeList.push_back(handle.index);
  }
}
