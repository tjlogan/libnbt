#include <sstream>
#include "string_tag.h"

StringTag::StringTag(std::string name) : BaseTag(name, TAG_STRING) {}
void StringTag::setValue(std::string value) {
   m_value = value;
}
std::string StringTag::value() {
   return m_value;
}
std::string StringTag::toString() {
   std::stringstream ss;
   ss << "STRING (" << m_name << "): " << m_value;
   return ss.str();
}
