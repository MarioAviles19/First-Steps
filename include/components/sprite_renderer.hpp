#pragma once
#include "cereal/cereal.hpp"
#include "shader.hpp"
#include "component.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace game
{
  class SpriteRenderer : public Component
  {
    public: 
      glm::vec2 spriteSize = glm::vec2(10.0f, 10.0f);
      glm::vec4 spriteColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
      SpriteRenderer(game::Entity& parent);
      ~SpriteRenderer();

      void DrawSprite(glm::vec4 color); 
      void setShader(Shader& shader);
    private:
      Shader shader;
      unsigned int quadVAO;
      void update(float deltaTime) ;
      bool getEnabled() const ;
      void initRenderData();
      template <class Archive>
        void serialize(Archive& archive)
        {
          archive(CEREAL_NVP(spriteSize), CEREAL_NVP(spriteColor));
        }
  };
}
