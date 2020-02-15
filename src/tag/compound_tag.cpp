#include <sstream>
#include "compound_tag.h"

CompoundTag::CompoundTag(std::string name) : BaseTag(name, TAG_COMPOUND) {}
void CompoundTag::setValue(int value) {
   m_value = value;
}
int CompoundTag::value() {
   return m_value;
}
std::string CompoundTag::toString() {
   std::stringstream ss;
   ss << "COMPOUND (" << m_name << ")";
   return ss.str();
}
