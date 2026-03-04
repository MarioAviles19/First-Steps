#include "components/sprite_renderer.hpp"
#include "program.hpp"
#include <cereal/types/vector.hpp>
#include "cereal/archives/json.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "input.hpp"
namespace game
{
  std::vector<std::unique_ptr<Entity>> entitiesForTesting;
  void Program::init()
  {
    auto* win = new game::Window(800, 600, "First Steps");
    this->renderer = std::make_shared<Renderer>(win);

    ResourceManager& resourceManager = ResourceManager::GetInstance();
    resourceManager.RegisterResource<Renderer>(renderer);
    std::unique_ptr cube = std::make_unique<Entity>();

    cube->transform->scale = glm::vec2(1.0f, 1.0f);

    
    SpriteRenderer& Renderer1 = cube->addComponent<SpriteRenderer>(); 
    entitiesForTesting.push_back(std::move(cube));

    glfwSetKeyCallback(this->renderer->window->glfwWindow, game::Input::glfwKeyCallback);
  }
  void Program::gameloop()
  {
    float lastTime = 0.0f; 
    while(!glfwWindowShouldClose(this->renderer->window->glfwWindow)){
      float currentTime = glfwGetTime();

      float deltaTime = currentTime - lastTime;

      //renderer clears the screen and swaps buffers
      this->renderer->render(deltaTime);





    }
    cereal::JSONOutputArchive oArchive(std::cout);
    oArchive(entitiesForTesting);



  }
}
