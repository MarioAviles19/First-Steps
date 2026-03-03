
#include "program.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include "window.hpp"
#include <memory>
namespace game
{
  void Program::init()
  {
    auto win = game::Window(800, 600, "First Steps");
    this->renderer = std::make_shared<Renderer>(&win);

    ResourceManager& resourceManager = ResourceManager::GetInstance();
    resourceManager.RegisterResource<Renderer>(renderer);
  }
}
