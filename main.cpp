#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "cereal/archives/json.hpp"
#include "program.hpp"
#include "serializer.hpp"
#include "cereal/types/memory.hpp"
#include "entity.hpp"
#include "renderer.hpp"
#include "resource_manager.hpp"
#include "shader.hpp"
#include "components/sprite_renderer.hpp"
#include "window.hpp"
using namespace game;
int main()
{
  auto program = game::Program();

  program.init();

  program.gameloop();

  glfwTerminate();
  return 0;
}


