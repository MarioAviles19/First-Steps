
#include "program.hpp"
#include "renderer.hpp"
#include "window.hpp"
namespace game
{
  void Program::init()
  {
    auto win = game::Window(800, 600, "First Steps");
    this->renderer = new game::Renderer(&win);
  }
}
