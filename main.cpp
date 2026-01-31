#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "renderer.hpp"
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

float uSpeed = 1.0f;
glm::vec2 objPos(0.0f, 0.0f);
//TODO: create an actual input handler class
class _input : public IRenderUpdater{
  public:
    GLFWwindow* win;
    SpriteRenderer* sprite;
  _input(GLFWwindow* window, SpriteRenderer* sprite) : win(window), sprite(sprite){
    
  }
  void update(float deltaTime) override
  {
    processInput(this->win);
  }
  bool getEnabled() const override
  {
    return true;
  }
  void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){

        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        this->sprite->position.x += 1.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        this->sprite->position.x -= 1.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        this->sprite->position.y -= 1.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        this->sprite->position.y += 1.0f;
    }
}
};
int main()
{

    auto gameWin = new Window(800, 900, "First Steps");
    ResourceManager& resourceManager = ResourceManager::GetInstance();
    auto renderer = std::make_shared<Renderer>(gameWin);

    Shader triangleShader("shaders/vertex.glsl", "shaders/fragment.glsl");
    float angle = 0.0f;
    float lastTime = 0.0f;

    resourceManager.RegisterResource<Renderer>(renderer);
    auto src = resourceManager.GetResource<Renderer>();
    std::cout << "Has Value: " << src.has_value() << std::endl;
    SpriteRenderer* Renderer1 = new SpriteRenderer(triangleShader);

    _input* inputs_temp = new _input(gameWin->glfwWindow, Renderer1);
    renderer->addUpdater(inputs_temp);
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

    renderer->render();

    glfwTerminate();
    return 0;
}


