#ifndef BYTE_TAG_H
#define BYTE_TAG_H

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
