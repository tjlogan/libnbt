#include <sstream>
#include "libnbt/tag/tag.h"

namespace nbt {
   FloatTag::FloatTag(std::string name) : BaseTag(name, TAG_FLOAT) {}
   void FloatTag::setValue(float value) {
      m_value = value;
   }
   float FloatTag::value() {
      return m_value;
   }
   std::string FloatTag::toString() {
      std::stringstream ss;
      ss << "FLOAT (" << m_name << "): " << m_value;
      return ss.str();
   }
}
