#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "sprite_renderer.hpp"
#include "component.hpp"
#include "shader.hpp"
#include "entity.hpp"

namespace game{


  SpriteRenderer::SpriteRenderer(game::Entity& parent) : Component(parent), shader(Shader("shaders/vertex.glsl", "shaders/fragment.glsl"))
  {
    this->initRenderData();
  }
  void SpriteRenderer::setShader(Shader& shader)
  {
    this->shader = shader;
  }

  SpriteRenderer::~SpriteRenderer() 
  {
    glDeleteVertexArrays(1, &this->quadVAO);
  }

  void SpriteRenderer::DrawSprite(glm::vec4 color)
  {
    //prepare transforms
    this->shader.use();
    //orthographic projection for 2D
    this->shader.setMatrix4("projection", this->renderer->orthoProjection);
    glm::mat4 model = this->entity.transform.getModel(this->spriteSize);
    this->shader.setMatrix4("model", model);

    this->shader.setVector3f("spriteColor", glm::vec3(color.x, color.y, color.z));

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
  }

  void SpriteRenderer::initRenderData()
  {
    unsigned int VBO;
    float verts[] = {
      // pos      // tex
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 

      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
  void SpriteRenderer::update(float deltaTime)
  {
    this->DrawSprite(glm::vec4(0.5f, 0.0f, 0.5f, 1.0f));
  }
  bool SpriteRenderer::getEnabled() const
  {
    return this->enabled;
  }
}
