#ifndef STRING_TAG
#define STRING_TAG 

#include <string>
#include "base_tag.h"

class StringTag : public BaseTag {
   private:
      std::string m_value;
   
   public:
      StringTag(std::string name);
      std::string value();
      void setValue(std::string value);
      std::string toString();
};

#endif
