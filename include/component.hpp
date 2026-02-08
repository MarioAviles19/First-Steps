#pragma once
#include "renderer.hpp"
#include "util/generational_vector.hpp"
namespace game{
  class Entity;
  class Component 
  {
    public:
      bool enabled = true;
      Entity& entity;
      bool getEnabled() const {return this->enabled;}
      void update(float deltaTime){}
      void start() {};
      ~Component();
    protected:
      Component(game::Entity& parent);
      utils::GenVectorHandle updateHandle;
      Renderer* renderer;
  };
};
