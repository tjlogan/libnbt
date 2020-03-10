#ifndef BYTE_ARRAY_TAG_H
#define BYTE_ARRAY_TAG_H

#include <string>
#include <vector>
#include "base_tag.h"

namespace nbt {
   class ByteArrayTag : public BaseTag {
      private:
         std::vector<char> m_values;

      public:
         ByteArrayTag(std::string name, char values[], int size);
         const std::vector<char> values();
         int size();
         std::string toString();
   };
}

#endif
