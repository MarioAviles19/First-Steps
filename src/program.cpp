#include "components/sprite_renderer.hpp"
#include "program.hpp"
#include <cereal/types/vector.hpp>
#include "cereal/archives/json.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include "cereal/types/memory.hpp"
#include "serializer.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
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
    resourceManager.RegisterResource<game::Renderer>(renderer);
    std::unique_ptr cube = std::make_unique<Entity>();

    cube->transform->scale = glm::vec2(1.0f, 1.0f);

    
    SpriteRenderer& renderer1 = cube->addComponent<SpriteRenderer>(); 
    renderer1.spriteSize = glm::vec2(50.0f, 50.0f);
    renderer1.spriteColor = glm::vec4(0.4f, 0.0f, 0.5f, 1.0f);
    entitiesForTesting.push_back(std::move(cube));

    glfwSetKeyCallback(this->renderer->window->glfwWindow, game::Input::glfwKeyCallback);
  }
  void Program::gameloop()
  {
    float lastTime = 0.0f; 
      for(int i = 0; i < entitiesForTesting.size(); i++)
      {
        for (const auto& comp : entitiesForTesting[i]->components)
        {
          comp->start();
        }
      }
      entitiesForTesting[0]->transform->getModel();
    while(!glfwWindowShouldClose(this->renderer->window->glfwWindow)){

      float currentTime = glfwGetTime();

      float deltaTime = currentTime - lastTime;
      lastTime = currentTime;

      //renderer clears the screen and swaps buffers
      this->renderer->render(deltaTime);


      for(int i = 0; i < entitiesForTesting.size(); i++)
      {
        for (const auto& comp : entitiesForTesting[i]->components)
        {
          comp->update(deltaTime);
        }
      }
      //Make sure input is working correctly
      if(game::Input::getKey(GLFW_KEY_W))
      {
        entitiesForTesting[0]->transform->position.y -= 50.0f * deltaTime;
      }
      if(game::Input::getKey(GLFW_KEY_A))
      {
        entitiesForTesting[0]->transform->position.x -= 50.0f * deltaTime;
      }
      if(game::Input::getKey(GLFW_KEY_S))
      {
        entitiesForTesting[0]->transform->position.y += 50.0f * deltaTime;
      }
      if(game::Input::getKey(GLFW_KEY_D))
      {
        entitiesForTesting[0]->transform->position.x += 50.0f * deltaTime;
      }
      std::cout << deltaTime << std::endl;
      glfwSwapBuffers(this->renderer->window->glfwWindow);
      glfwPollEvents();


    }
    cereal::JSONOutputArchive oArchive(std::cout);
    oArchive(entitiesForTesting);



  }
}
