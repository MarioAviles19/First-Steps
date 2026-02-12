#pragma once

#include "cereal/access.hpp"
#include "cereal/cereal.hpp"
#include "entity.hpp"
#include "program.hpp"
#include <string>
namespace game
{

  class Scene
  {
    public:
      Scene(game::Program* program, std::string id);
      ~Scene();
      std::string id;
      void load(bool startEnabled = true);
      void save(std::string path);
      void destroy();
      bool enabled;

    private:
      friend class cereal::access;
      template<class Archive>
        void serialize(Archive& archive)
        {
          archive(CEREAL_NVP(entities), CEREAL_NVP(id));
        }
      game::Program* program;
      std::vector<game::Entity> entities;
  };
}
