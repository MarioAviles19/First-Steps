#pragma once

#include "util/generational_vector.hpp"
#include "window.hpp"
#include <functional>
#include <glm/gtc/matrix_transform.hpp>
namespace game {
  struct IRenderUpdater{
    virtual ~IRenderUpdater() = default;
    virtual void update(float deltaTime) = 0;
    virtual bool getEnabled() const = 0;
  };
  //TODO: this should take in pure functions rather than classes.
  //Because all components need to be able to be added to the update loop
  //but not all need to be able to be added to the render loop
  typedef std::function<void (float)> renderLoopCallback;
  class Renderer
  {
    public:
      Renderer(Window* window);
      void render(float deltaTime);
      utils::GenVectorHandle addUpdater(renderLoopCallback updater);
      void removeUpdater(utils::GenVectorHandle handle);
      glm::mat4 orthoProjection;
    private:
      Window* window;
      utils::GenerationalVector<renderLoopCallback> updaters;
  };
}
