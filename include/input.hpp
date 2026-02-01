#include <GLFW/glfw3.h>
namespace game
{
  class Input {
    public:
      static void refreshState();
      static bool getKeyDown(int key);
      static bool getKeyUp(int key);
      static bool getKey(int key);
      static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    private:
      static bool keys[1024];
      static bool keysUp[1024];
      static bool keysDown[1024];
      
  };
}
