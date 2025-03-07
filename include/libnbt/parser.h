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
         std::vector<std::shared_ptr<BaseTag>> parseUntilEnd();
         std::shared_ptr<ListTag> readList(const std::string& name);
         std::shared_ptr<BaseTag> readTag(TagType type);
         std::shared_ptr<BaseTag> decodeTag(TagType tagType, const std::string& name);
         bool error;
         std::string errorMsg;

      public:
         explicit Parser(std::istream& is);
         std::vector<std::shared_ptr<BaseTag>> parse();
         std::shared_ptr<BaseTag> parseTag();
         bool isGood() const;
         bool isError() const;
         std::string getErrorMessage();
   };
}

#endif
