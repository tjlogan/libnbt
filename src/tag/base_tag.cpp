#include <string>
#include "libnbt/tag/base_tag.h"

namespace nbt {
   BaseTag::BaseTag(std::string name, TagType type) : m_name(name), m_type(type) {}

   std::string BaseTag::name() {
      return m_name;
   }

   TagType BaseTag::type() {
      return m_type;
   }

   std::shared_ptr<BaseTag> BaseTag::getTag(std::string) {
      return std::shared_ptr<BaseTag>();
   }
}
