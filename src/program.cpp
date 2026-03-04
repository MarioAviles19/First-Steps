
#include "program.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "input.hpp"
namespace game
{
  std::string cheese = "cheese";
  void Program::init()
  {
      std::cout << cheese << std::endl;
    auto* win = new game::Window(800, 600, "First Steps");
    this->renderer = std::make_shared<Renderer>(win);

    ResourceManager& resourceManager = ResourceManager::GetInstance();
    resourceManager.RegisterResource<Renderer>(renderer);
    glfwSetKeyCallback(this->renderer->window->glfwWindow, game::Input::glfwKeyCallback);
    cheese = "gouda";
  }
  void Program::gameloop()
  {
    float lastTime = 0.0f; 
    while(!glfwWindowShouldClose(this->renderer->window->glfwWindow)){
      float currentTime = glfwGetTime();

      float deltaTime = currentTime - lastTime;

      //renderer clears the screen and swaps buffers
      this->renderer->render(deltaTime);





      //glfwSwapBuffers(this->renderer->window->glfwWindow);
      //glfwPollEvents();
    }


  }
}
