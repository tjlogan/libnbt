#ifndef COMPOUND_TAG
#define COMPOUND_TAG 

#include <string>
#include "base_tag.h"

class CompoundTag : public BaseTag {
   private:
      int m_value; // TODO: leaving value alone for now
   
   public:
      CompoundTag(std::string name);
      int value();
      void setValue(int value);
      std::string toString();
};

#endif
