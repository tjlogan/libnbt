#ifndef FLOAT_TAG_H
#define FLOAT_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class FloatTag : public BaseTag {
      private:
         float m_value;
      
      public:
         explicit FloatTag(std::string name);
         float value() const;
         void setValue(float value);
         std::string toString() override;
   };
}

#endif
