#ifndef PARSER_H
#define PARSER_H 

#include <istream>

#pragma pack(push, 1) 
struct Header {
   int version;
   int size;
};
#pragma pack(pop)

class Parser {
   private:
      unsigned int m_version;
      unsigned int m_size;

   public:
      Parser(std::istream& is);
      unsigned int version();
      unsigned int size();
};

#endif
