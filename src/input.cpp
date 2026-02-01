#include "input.hpp"
#include <GLFW/glfw3.h>
#include <cstring>
namespace game
{
  bool Input::getKey(int key)
  {
    return keys[key];
  }
  bool Input::getKeyDown(int key)
  {
    return keysDown[key];
  }
  bool Input::getKeyUp(int key)
  {
    return keysUp[key];
  }



  void Input::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    //This function only runs when keys are pressed
    
    if(action == GLFW_PRESS)
    {
      keys[key] = true;
      keysDown[key] = true;
    } 
    else if (action == GLFW_RELEASE) 
    {
      keys[key] = false;
      keysUp[key] = false;

    }
  }
  void Input::refreshState()
  {
    std::memset(keysUp, 0, sizeof(keysUp));
    std::memset(keysDown, 0, sizeof(keysDown));
  }
}
