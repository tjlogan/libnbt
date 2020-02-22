#ifndef SHORT_TAG_H
#define SHORT_TAG_H

#include <string>
#include "base_tag.h"

class ShortTag : public BaseTag {
   private:
      short m_value;
   
   public:
      ShortTag(std::string name);
      short value();
      void setValue(short value);
      std::string toString();
};

#endif
