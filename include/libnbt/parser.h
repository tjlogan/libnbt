#ifndef PARSER_H
#define PARSER_H 

#include <istream>
#include <vector>
#include <memory>
#include "tag/tag.h"

namespace nbt {
   class Parser {
      private:
         std::istream& m_is;
         std::vector<std::shared_ptr<BaseTag>> m_root;

         std::string readString();

      public:
         Parser(std::istream& is);
         std::vector<std::shared_ptr<BaseTag>> parse();
   };
}
#endif
