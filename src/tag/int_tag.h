#ifndef INT_TAG
#define INT_TAG 

#include <string>
#include "base_tag.h"

class IntTag : public BaseTag {
   private:
      int m_value;
   
   public:
      IntTag(std::string name);
      int value();
      void setValue(int value);
      std::string toString();
};

#endif
