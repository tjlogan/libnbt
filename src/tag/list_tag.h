#ifndef LIST_TAG_H
#define LIST_TAG_H

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
