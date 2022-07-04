#ifndef LIST_TAG_H
#define LIST_TAG_H

#include <string>
#include <vector>
#include <memory>
#include "base_tag.h"

namespace nbt {
   class ListTag : public BaseTag {
      private:
         TagType m_childType;
      
      public:
         std::vector<std::shared_ptr<BaseTag>> children;

         ListTag(std::string name, TagType childType);
         TagType childType();
         int size();
         std::string toString() override;
         std::shared_ptr<BaseTag> getTag(std::string name) override;
   };
}

#endif
