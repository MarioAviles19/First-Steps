#pragma once

#include "renderer.hpp"
#include <memory>
namespace game
{
  class Program 
  {
    public:
      void init();
      void gameloop();
      std::shared_ptr<game::Renderer> renderer;
    private:


  };
}
