#include <sstream>
#include "int_tag.h"

IntTag::IntTag(std::string name) : BaseTag(name, TAG_INT) {}
void IntTag::setValue(int value) {
   m_value = value;
}
int IntTag::value() {
   return m_value;
}
std::string IntTag::toString() {
   std::stringstream ss;
   ss << "INT (" << m_name << "): " << m_value;
   return ss.str();
}
