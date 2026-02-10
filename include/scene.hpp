#pragma once

#include "entity.hpp"
#include "program.hpp"
#include <string>
namespace game
{
  struct SceneData{

    std::vector<game::Entity> entities;
  };

  class Scene
  {
    public:
      Scene(game::Program* program);
      ~Scene();
      std::string id;
      void load(bool startEnabled = true);
      void destroy();
      bool enabled;

    private:
      game::Program* program;
      game::SceneData data;
  };
}
