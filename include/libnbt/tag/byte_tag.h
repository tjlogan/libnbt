#ifndef BYTE_TAG_H
#define BYTE_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class ByteTag : public BaseTag {
      private:
         char m_value;
      
      public:
         explicit ByteTag(std::string name);
         char value() const;
         void setValue(char value);
         std::string toString() override;
   };
}

#endif
