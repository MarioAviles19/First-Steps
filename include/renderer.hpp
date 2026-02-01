#pragma once

#include "window.hpp"
#include <cstdint>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
namespace game {
  struct IRenderUpdater{
    virtual ~IRenderUpdater() = default;
    virtual void update(float deltaTime) = 0;
    virtual bool getEnabled() const = 0;
  };
  struct UpdaterHandle{
    uint32_t index;
    uint32_t generation;
  };



  class Renderer
  {
    public:
      Renderer(Window* window);
      void render();
      UpdaterHandle addUpdater(IRenderUpdater* updater);
      void removeUpdater(UpdaterHandle handle);
      glm::mat4 orthoProjection;
    private:
      Window* window;
      std::vector<IRenderUpdater*> updaters;
      std::vector<uint32_t> generations;
      std::vector<uint32_t> freeList;
  };
}
