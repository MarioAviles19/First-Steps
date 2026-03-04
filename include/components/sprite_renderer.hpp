#pragma once
#include "cereal/cereal.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "component.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace game
{
  class SpriteRenderer : public Component
  {
    public: 
      glm::vec2 spriteSize = glm::vec2(40.0f, 40.0f);
      glm::vec4 spriteColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
      SpriteRenderer();
      ~SpriteRenderer();

      void DrawSprite(game::Renderer* renderer); 
      void setShader(Shader& shader);
    private:
      friend class game::Program;
      Shader shader;
      unsigned int quadVAO;
      void update(float deltaTime);
      void start();
      bool getEnabled() const ;
      void initRenderData();
      game::Renderer* renderer;
      template <class Archive>
        void serialize(Archive& archive)
        {
          archive(CEREAL_NVP(spriteSize), CEREAL_NVP(spriteColor));
        }
  };
}
