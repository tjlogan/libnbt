#ifndef FLOAT_TAG_H
#define FLOAT_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class FloatTag : public BaseTag {
      private:
         float m_value;
      
      public:
         FloatTag(std::string name);
         float value();
         void setValue(float value);
         std::string toString();
   };
}

#endif
