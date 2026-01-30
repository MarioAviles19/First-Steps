#pragma once
#include "shader.hpp"
#include "component.hpp"
#include <glm/gtc/matrix_transform.hpp>
class SpriteRenderer : Component
{
  public: 
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(glm::vec4 color, glm::vec2 position, 
        glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotation = 0.0f);
  private:
    Shader shader;
    unsigned int quadVAO;
    void update(float deltaTime) override;
    void initRenderData();
};
