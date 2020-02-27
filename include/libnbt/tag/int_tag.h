#ifndef INT_TAG_H
#define INT_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class IntTag : public BaseTag {
      private:
         int m_value;
      
      public:
         IntTag(std::string name);
         int value();
         void setValue(int value);
         std::string toString();
   };
}

#endif
