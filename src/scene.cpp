#include "scene.hpp"
#include "cereal/archives/json.hpp"
#include "program.hpp"
#include <fstream>
#include <string>


namespace game
{
  Scene::Scene(game::Program* program, std::string id): program(program), id(id){

  }
  Scene::~Scene(){}
  void Scene::save(std::string path)
  {
    std::ofstream filePath(path);

    cereal::JSONOutputArchive archive(filePath);

    this->serialize<cereal::JSONOutputArchive>(archive);
  }
}
