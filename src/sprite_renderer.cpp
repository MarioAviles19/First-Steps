#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "components/sprite_renderer.hpp"
#include "component.hpp"
#include "shader.hpp"
#include "entity.hpp"
#include "resource_manager.hpp"
namespace game{


  SpriteRenderer::SpriteRenderer() : Component(), shader(Shader("shaders/vertex.glsl", "shaders/fragment.glsl"))
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

  void SpriteRenderer::DrawSprite(game::Renderer* renderer)
  {
    //prepare transforms
    this->shader.use();
    //orthographic projection for 2D
    this->shader.setMatrix4("projection", renderer->orthoProjection);
    assert(this->entity->transform);
    glm::mat4 model = this->entity->transform->getModel(this->spriteSize);
    this->shader.setMatrix4("model", model);

    this->shader.setVector3f("spriteColor", glm::vec3(spriteColor.x, spriteColor.y, spriteColor.z));

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
  void SpriteRenderer::start()
  {
    auto& resourceManager = ResourceManager::GetInstance();
    auto rendererRef = resourceManager.GetResource<game::Renderer>();
    assert(rendererRef.has_value());
    this->renderer = rendererRef->get();
  }
  void SpriteRenderer::update(float deltaTime)
  {
    this->DrawSprite(renderer);
  }
  bool SpriteRenderer::getEnabled() const
  {
    return this->enabled;
  }
}
