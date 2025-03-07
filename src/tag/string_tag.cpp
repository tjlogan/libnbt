#include <sstream>
#include "libnbt/tag/string_tag.h"

namespace nbt {
   StringTag::StringTag(std::string name) : BaseTag(name, TAG_STRING) {}
   void StringTag::setValue(std::string value) {
      m_value = value;
   }
   std::string StringTag::value() const {
      return m_value;
   }
   std::string StringTag::toString() {
      std::stringstream ss;
      ss << "STRING (" << m_name << "): " << m_value;
      return ss.str();
   }
}