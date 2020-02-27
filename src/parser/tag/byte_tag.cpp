#include <sstream>
#include <iomanip>
#include "libnbt/parser/tag/byte_tag.h"

namespace nbt {
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
}
