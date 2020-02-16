#include <sstream>
#include "list_tag.h"

ListTag::ListTag(std::string name) : BaseTag(name, TAG_LIST) {}
void ListTag::setValue(int value) {
   m_value = value;
}
int ListTag::value() {
   return m_value;
}
std::string ListTag::toString() {
   std::stringstream ss;
   ss << "LIST (" << m_name << "): " << m_value;
   return ss.str();
}
