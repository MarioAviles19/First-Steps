#pragma once
#include <GLFW/glfw3.h>
#include <string>

namespace game
{

  class Window
  {
    public:
      static void frameBufferSizeCallback(GLFWwindow* window, int width_, int height_);
      Window(int width, int height, std::string title);
      ~Window();
      GLFWwindow* GetWindow();
      void onFrameBufferResize(int width_, int height_);
      int width;
      int height;
      GLFWwindow* glfwWindow;
    private:
  };
}
