#include <iostream>
#include <glad/glad.h>
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include <string>
void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
  auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
  if(self)
  {
    self->onFrameBufferResize(width, height);
  }
}
void Window::onFrameBufferResize(int width_, int height_)
{
  this->width = width_;
  this->height = height_;
  glViewport(0, 0, width, height);
}
Window::Window(int width, int height, const std::string title) : width(width), height(height)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  this->glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  int w, h;
  glfwGetFramebufferSize(this->glfwWindow, &w, &h);
  assert(("Failed to create GLFW window" && this->glfwWindow != NULL));

  std::cout << "w: " << w << "H: " << h << std::endl;
  glfwMakeContextCurrent(this->glfwWindow);
  glfwSwapInterval(1);
  assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

  glViewport(0,0, width, height);
  glfwSetWindowUserPointer(this->glfwWindow, this);
  glfwSetFramebufferSizeCallback(this->glfwWindow,Window::frameBufferSizeCallback); 
}
Window::~Window(){

}
