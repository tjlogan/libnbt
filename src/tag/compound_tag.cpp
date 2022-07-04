#include <sstream>
#include <iostream>
#include "libnbt/tag/compound_tag.h"

namespace nbt {
   CompoundTag::CompoundTag(std::string name) : BaseTag(name, TAG_COMPOUND) {}

   std::string CompoundTag::toString() {
      std::stringstream ss;
      ss << "COMPOUND (" << m_name << "): [" << children.size() << "]";
      for (const auto& x: children) {
         ss << "\n" << x->toString();
      }
      return ss.str();
   }

   std::shared_ptr<BaseTag> CompoundTag::getTag(std::string name) {
      for(auto el: children) {
         if (el->name() == name) {
            return el;
         }
      }
      return nullptr;
   }
}
