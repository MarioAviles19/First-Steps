#pragma once

#include "renderer.hpp"
#include <memory>
namespace game
{
  class Program 
  {
    public:
      void init();

      std::shared_ptr<game::Renderer> renderer;
    private:


  };
}
