#ifndef COMPOUND_TAG_H
#define COMPOUND_TAG_H

#include <string>
#include <memory>
#include <vector>
#include "base_tag.h"

namespace nbt {
   class CompoundTag : public BaseTag {
      public:
         std::vector<std::shared_ptr<BaseTag>> children;

         explicit CompoundTag(std::string name);
         std::string toString() override;
         std::shared_ptr<BaseTag> getTag(std::string name) override;
   };
}

#endif
