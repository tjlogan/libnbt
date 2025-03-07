#include <sstream>
#include "libnbt/tag/long_tag.h"

namespace nbt {
   LongTag::LongTag(std::string name) : BaseTag(name, TAG_LONG) {}
   void LongTag::setValue(long value) {
      m_value = value;
   }
   long LongTag::value() const {
      return m_value;
   }
   std::string LongTag::toString() {
      std::stringstream ss;
      ss << "LONG (" << m_name << "): " << m_value;
      return ss.str();
   }
}
