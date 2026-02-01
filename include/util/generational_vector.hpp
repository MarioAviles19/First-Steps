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
        GenVectorHandle add(T element){
          if(!this->freeList.empty())
          {
            uint32_t idx = freeList.back();
            this->freeList.pop_back();

            this->elements[idx] = element; 
            return {idx, this->generations[idx]};
          }
          uint32_t idx = this->elements.size();
          this->elements.push_back(element);
          this->generations.push_back(0);
          return {idx, 0};
  

        }
        void remove(GenVectorHandle handle){
          if(handle.index >= this->elements.size())
          {
            return;
          }
          if(this->generations[handle.index] != handle.generation)
          {
            return;
          }
          this->elements[handle.index] = nullptr;
          this->generations[handle.index]++;
          this->freeList.push_back(handle.index);

        }
        std::vector<T> elements;
      private:
        std::vector<uint32_t> generations;
        std::vector<uint32_t> freeList;
    };
}
