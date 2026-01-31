#pragma once
#include <memory>
#include <iostream>
#include <optional>
#include <string>
#include <typeindex>
#include <unordered_map>

struct ResourceKey {
  std::type_index type;
  std::string tag;

  bool operator==(const ResourceKey& other) const{
    return type == other.type && tag == other.tag;
  }
};
struct ResourceKeyHash {
  std::size_t operator()(const ResourceKey& key) const {
    std::size_t h1 = std::hash<std::type_index>{}(key.type);
    std::size_t h2 = std::hash<std::string>{}(key.tag);
    return h1 ^ (h2 << 1);
  }
};

class ResourceManager{

  public:
    ResourceManager(){};
    static ResourceManager& GetInstance(){
      static ResourceManager instance;

      return instance;
    }
    template<typename T>
      void RegisterResource(std::shared_ptr<T> resource, std::string tag = ""){
        auto existing = this->GetInstance().GetResource<T>(tag);

        assert(!existing.has_value());

        ResourceKey key{std::type_index(typeid(T)), std::move(tag)};
        this->resources[key] = resource;

      }


    template<typename T>
      std::optional<std::shared_ptr<T>> GetResource(std::string tag = ""){
        ResourceKey key{std::type_index(typeid(T)), std::move(tag)};

        auto res = this->resources.find(key); 
        if(res == this->resources.end()){
          std::cout << "Could not find resource" << std::endl;

          return std::nullopt;
        }
        return (std::shared_ptr<T>)std::static_pointer_cast<T>(res->second);

      }

    void operator=(const ResourceManager&) = delete;
    ResourceManager(const ResourceManager&) = delete;
  private:
    std::unordered_map<ResourceKey, std::shared_ptr<void>, ResourceKeyHash> resources;
};
