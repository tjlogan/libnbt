#ifndef LONG_TAG_H
#define LONG_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class LongTag : public BaseTag {
      private:
         long m_value;
      
      public:
         explicit LongTag(std::string name);
         long value() const;
         void setValue(long value);
         std::string toString() override;
   };
}

#endif
