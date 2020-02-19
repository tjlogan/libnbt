#include <sstream>
#include "compound_tag.h"

CompoundTag::CompoundTag(std::string name) : BaseTag(name, TAG_COMPOUND) {}

std::string CompoundTag::toString() {
   std::stringstream ss;
   ss << "COMPOUND (" << m_name << "): [" << children.size() << "]";
   for (auto x: children) {
      ss << "\n" << x->toString();
   }
   return ss.str();
}
