#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cereal/cereal.hpp>

namespace cereal {

  template<class Archive>
    void serialize(Archive& archive, glm::vec3& v)
    {
      archive(
          cereal::make_nvp("x", v.x),
          cereal::make_nvp("y", v.y),
          cereal::make_nvp("z", v.z)
          );
    }
  template<class Archive>
    void serialize(Archive& archive, glm::vec2& v)
    {
      archive(
          cereal::make_nvp("x", v.x),
          cereal::make_nvp("y", v.y)
          );
    }


}
