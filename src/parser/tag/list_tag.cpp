#include <sstream>
#include "libnbt/parser/tag/list_tag.h"

namespace nbt {
   ListTag::ListTag(std::string name, TagType childType) : BaseTag(name, TAG_LIST) {
      m_childType = childType;
   }

   int ListTag::size() {
      return children.size();
   }

   TagType ListTag::childType() {
      return m_childType;
   }

   std::string ListTag::toString() {
      std::stringstream ss;
      ss << "LIST (" << m_name << "): [" << children.size() << "]";
      for (auto x: children) {
         ss << "\n" << x->toString();
      }
      return ss.str();
   }
}
