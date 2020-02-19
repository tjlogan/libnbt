#ifndef PARSER_H
#define PARSER_H 

#include <istream>
#include <vector>
#include <memory>
#include "../tag/tag.h"

#pragma pack(push, 1) 
struct Header {
   int version;
   int size;
};
#pragma pack(pop)

class Parser {
   private:
      std::istream& m_is;
      unsigned int m_version;
      unsigned int m_size;
      std::vector<std::shared_ptr<BaseTag>> m_root;

      std::string readString();
      int readInt();
      long readLong();

   public:
      Parser(std::istream& is);
      unsigned int version();
      unsigned int size();
      std::vector<std::shared_ptr<BaseTag>> parse();
};

namespace ParserHelper {
   template <typename T>
   T read(std::istream& is) {
      std::unique_ptr<char[]> valueBuffer(new char[sizeof(T)]);
      is.read(valueBuffer.get(), sizeof(T));
      T value = valueBuffer[sizeof(T) - 1];
      for(int i = (int)sizeof(T) - 2; i >= 0; i--) {
         value = (value << 8) + valueBuffer[i];
      }
      return value;
   };
}
#endif
