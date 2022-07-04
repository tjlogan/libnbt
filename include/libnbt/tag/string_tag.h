#ifndef STRING_TAG_H
#define STRING_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class StringTag : public BaseTag {
      private:
         std::string m_value;
      
      public:
         explicit StringTag(std::string name);
         std::string value() const;
         void setValue(std::string value);
         std::string toString() override;
   };
}

#endif
