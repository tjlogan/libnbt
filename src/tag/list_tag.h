#ifndef LIST_TAG
#define LIST_TAG 

#include <string>
#include "base_tag.h"

class ListTag : public BaseTag {
   private:
      int m_value;
   
   public:
      ListTag(std::string name);
      int value();
      void setValue(int value);
      std::string toString();
};

#endif
