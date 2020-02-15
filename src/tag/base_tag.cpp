#include <string>
#include <sstream>
#include <iomanip>
#include "base_tag.h"

BaseTag::BaseTag(std::string name, TagType type) : m_name(name), m_type(type) {}

std::string BaseTag::name() {
   return m_name;
}

TagType BaseTag::type() {
   return m_type;
}

ByteTag::ByteTag(std::string name) : BaseTag(name, TAG_BYTE) {}
void ByteTag::setValue(char value) {
   m_value = value;
}
char ByteTag::value() {
   return m_value;
}
std::string ByteTag::toString() {
   std::stringstream ss;
   ss << "BYTE (" << m_name << "): 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (int)m_value);
   return ss.str();
}

// IntTag::IntTag(std::string name) : BaseTag(name, TAG_INT) {}
// void IntTag::setValue(int value) {
//    m_value = value;
// }
// int IntTag::value() {
//    return m_value;
// }
// StringTag::StringTag(std::string name) : BaseTag(name, TAG_STRING) {};
// CompoundTag::CompoundTag(std::string name) : BaseTag(name, TAG_COMPOUND) {
//    m_value = std::vector<BaseTag>();
// };
// void CompoundTag::add(BaseTag tag) {
//    m_value.push_back(tag);
// };
// std::vector<BaseTag> CompoundTag::value() {
//    return m_value;
// }