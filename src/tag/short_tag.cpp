#include <sstream>
#include "short_tag.h"

namespace nbt {
   ShortTag::ShortTag(std::string name) : BaseTag(name, TAG_SHORT) {}
   void ShortTag::setValue(short value) {
      m_value = value;
   }
   short ShortTag::value() {
      return m_value;
   }
   std::string ShortTag::toString() {
      std::stringstream ss;
      ss << "SHORT (" << m_name << "): " << m_value;
      return ss.str();
   }
}
