#ifndef LONG_TAG_H
#define LONG_TAG_H

#include <string>
#include "base_tag.h"

class LongTag : public BaseTag {
   private:
      long m_value;
   
   public:
      LongTag(std::string name);
      long value();
      void setValue(long value);
      std::string toString();
};

#endif
