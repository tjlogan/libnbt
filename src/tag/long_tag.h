#ifndef LONG_TAG
#define LONG_TAG 

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
