#ifndef BYTE_TAG
#define BYTE_TAG 

#include <string>
#include "base_tag.h"

class ByteTag : public BaseTag {
   private:
      char m_value;
   
   public:
      ByteTag(std::string name);
      char value();
      void setValue(char value);
      std::string toString();
};

#endif
