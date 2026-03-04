#pragma once
#include "renderer.hpp"
#include "util/generational_vector.hpp"
#include "cereal/access.hpp"
namespace game{
  class Entity;
  class Component 
  {
    public:
      bool enabled = true;
      Entity* entity;
      bool getEnabled() const {return this->enabled;}
      virtual void update(float deltaTime){}
      virtual void start() {}

      ~Component();
    protected:
      Component();
      friend class cereal::access;
  };
};
