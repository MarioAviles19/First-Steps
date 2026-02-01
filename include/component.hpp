#pragma once
#include "renderer.hpp"
#include "util/generational_vector.hpp"
namespace game{
  class Entity;
  class Component : public game::IRenderUpdater 
  {
    public:
      bool enabled = true;
      Entity& entity;
      bool getEnabled() const override;
      void update(float deltaTime) override;
      ~Component();
    protected:
      Component(game::Entity& parent);
      utils::GenVectorHandle updateHandle;
      Renderer* renderer;
  };
};
