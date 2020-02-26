#include <sstream>
#include "long_tag.h"

namespace nbt {
   LongTag::LongTag(std::string name) : BaseTag(name, TAG_LONG) {}
   void LongTag::setValue(long value) {
      m_value = value;
   }
   long LongTag::value() {
      return m_value;
   }
   std::string LongTag::toString() {
      std::stringstream ss;
      ss << "LONG (" << m_name << "): " << m_value;
      return ss.str();
   }
}
