#pragma once
#include <cstdint>
#include <vector>
namespace utils
{

  struct GenVectorHandle{
    uint32_t index;
    uint32_t generation;
  };
    template <typename T>
    class GenerationalVector{
      public:
        GenerationalVector();
        GenVectorHandle add(T* element);
        void remove(GenVectorHandle handle);
      private:
        std::vector<T*> elements;
        std::vector<uint32_t> generations;
        std::vector<uint32_t> freeList;
    };
}
