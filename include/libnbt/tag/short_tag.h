#ifndef SHORT_TAG_H
#define SHORT_TAG_H

#include <string>
#include "base_tag.h"

namespace nbt {
   class ShortTag : public BaseTag {
      private:
         short m_value;
      
      public:
         explicit ShortTag(std::string name);
         short value() const;
         void setValue(short value);
         std::string toString() override;
   };
}

#endif
