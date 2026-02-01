#pragma once

#include "util/generational_vector.hpp"
#include "window.hpp"
#include <cstdint>
#include <glm/gtc/matrix_transform.hpp>
namespace game {
  struct IRenderUpdater{
    virtual ~IRenderUpdater() = default;
    virtual void update(float deltaTime) = 0;
    virtual bool getEnabled() const = 0;
  };

  class Renderer
  {
    public:
      Renderer(Window* window);
      void render(float deltaTime);
      utils::GenVectorHandle addUpdater(IRenderUpdater* updater);
      void removeUpdater(utils::GenVectorHandle handle);
      glm::mat4 orthoProjection;
    private:
      Window* window;
      utils::GenerationalVector<IRenderUpdater*> updaters;
  };
}
