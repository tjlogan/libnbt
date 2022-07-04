#include <sstream>
#include "libnbt/tag/tag.h"

namespace nbt {
   ByteArrayTag::ByteArrayTag(std::string name, char values[], int size) : BaseTag(name, TAG_BYTE_ARRAY) {
      m_values = std::vector<char>(values, values + size);
   }

   std::vector<char> ByteArrayTag::values() const {
      return m_values;
   }

   int ByteArrayTag::size() {
      return m_values.size();
   }

   std::string ByteArrayTag::toString() {
      std::stringstream ss;
      ss << "BYTE_ARRAY (" << m_name << "): [" << size() << "]";
      return ss.str();
   }
}
