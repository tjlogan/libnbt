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
         std::shared_ptr<ByteTag> readByteTag(std::string name);
         std::shared_ptr<IntTag> readIntTag(std::string name);

      public:
         Parser(std::istream& is);
         std::vector<std::shared_ptr<BaseTag>> parse();
   };

   namespace ParserHelper {
      template <typename T>
      T read(std::istream& is) {
         std::unique_ptr<char[]> valueBuffer(new char[sizeof(T)]);
         T result;
         is.read(valueBuffer.get(), sizeof(T));
         std::copy(reinterpret_cast<const char*>(&valueBuffer[0]),
                  reinterpret_cast<const char*>(&valueBuffer[sizeof(T)]),
                  reinterpret_cast<char*>(&result));
         return result;
      };
   }
}
#endif
