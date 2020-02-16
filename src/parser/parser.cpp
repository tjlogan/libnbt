#include "parser.h"

Parser::Parser(std::istream& is) {
   char* buffer = new char[8];
   is.read(buffer, 8);
   struct Header* header = (Header*)buffer;
   m_version = header->version;
   m_size = header->size;
};

unsigned int Parser::version() {
   return m_version;
};

unsigned int Parser::size() {
   return m_size;
};
