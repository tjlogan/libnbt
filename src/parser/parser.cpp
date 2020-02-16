#include <memory>
#include "parser.h"
#include "../tag/tag.h"

Parser::Parser(std::istream& is) : m_is(is) {
   char* buffer = new char[8];
   m_is.read(buffer, 8);
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

std::vector<BaseTag*> Parser::parse() {
   char tagBuffer;
   short nameLength;
   std::string name;
   while(m_is.read(&tagBuffer, 1)) {
      switch (tagBuffer) {
      case TAG_BYTE: {
         m_is.read(reinterpret_cast<char*>(&nameLength), 2);
         if (nameLength > 0) {
            std::unique_ptr<char[]> nameBuffer(new char[nameLength]);
            m_is.read(nameBuffer.get(), nameLength);
            name.assign(nameBuffer.get(), nameLength);
         }
         ByteTag* byteTag = new ByteTag(name);
         char value;
         m_is.read(&value, 1);
         byteTag->setValue(value);
         m_root.push_back(byteTag);
         break;
      }
      default:
         break;
      }
   }
   return m_root;
};