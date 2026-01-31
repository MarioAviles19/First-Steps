#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "resource_manager.hpp"
#include "shader.hpp"
#include "sprite_renderer.hpp"
#include "window.hpp"

float triangle[] = {
  //Vertex data    
  0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 
  0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
  -0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 1.0f,
};
unsigned int indices[] = {
  0, 1, 3,
  1, 2, 3
};

auto gameWin = std::make_shared<Window>(800, 900, "First Steps");
float uSpeed = 1.0f;
glm::vec2 objPos(0.0f, 0.0f);
void processInput(GLFWwindow *window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
    
    glfwSetWindowShouldClose(window, true);

  }
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    objPos.x += 1.0f;
  }
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    objPos.x -= 1.0f;
  }
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    objPos.y -= 1.0f;
  }
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    objPos.y += 1.0f;
  }
}
void render(GLFWwindow* window, unsigned int VAO){
    int i = 0;
    Shader triangleShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    float angle = 0.0f;
    float lastTime = 0.0f;
    SpriteRenderer* Renderer1 = new SpriteRenderer(triangleShader);
    SpriteRenderer* Renderer2 = new SpriteRenderer(triangleShader);
    triangleShader.use();
    while(!glfwWindowShouldClose(window))
    {

      //input
      processInput(window);

      // rendering commands here
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      int w;
      int h;
      glfwGetFramebufferSize(window, &w, &h);

      float currentTime = glfwGetTime();

      float deltaTime = currentTime - lastTime;
      lastTime = currentTime;
      angle += deltaTime * uSpeed * 2.0f;
      triangleShader.use();
      triangleShader.setMatrix4("projection", projection);

      Renderer1->DrawSprite(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f), objPos, glm::vec2(40.0f, 40.0f));
      // check and call events & swap buffers
      glfwSwapBuffers(window);
      glfwPollEvents();

    }
}

int main()
{
  
  ResourceManager::GetInstance().RegisterResource<Window>(gameWin, "tag");


  std::optional<std::shared_ptr<Window>> win = ResourceManager::GetInstance().GetResource<Window>("tag");

  if(win.has_value())
  {
    //win.value()->onFrameBufferResize(1000, 1700);
  }
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  //Element Buffer Object
  unsigned int EBO;
  glGenBuffers(1, &EBO);



  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_DYNAMIC_DRAW);


  // 1. bind Vertex Array Object
  glBindVertexArray(VAO);
  // 2. copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
  // 3. then set our vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  render(gameWin->glfwWindow, VAO);

  glfwTerminate();
  return 0;
}


