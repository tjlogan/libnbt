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

std::vector<std::shared_ptr<BaseTag> > Parser::parse() {
   char tagBuffer;
   std::string name;
   while(m_is.read(&tagBuffer, 1)) {
      switch (tagBuffer) {
      case TAG_BYTE: {
         name = readName();
         char value = ParserHelper::read<char>(m_is);
         std::shared_ptr<ByteTag> byteTag = std::make_shared<ByteTag>(name);
         byteTag->setValue(value);
         m_root.push_back(byteTag);
         break;
      }
      case TAG_INT: {
         name = readName();
         int value = ParserHelper::read<int>(m_is);
         std::shared_ptr<IntTag> intTag = std::make_shared<IntTag>(name);
         intTag->setValue(value);
         m_root.push_back(intTag);
         break;
      }
      case TAG_LONG: {
         name = readName();
         long value = ParserHelper::read<long>(m_is);
         std::shared_ptr<LongTag> longTag = std::make_shared<LongTag>(name);
         longTag->setValue(value);
         m_root.push_back(longTag);
         break;
      }
      case TAG_STRING: {
         name = readName();
         std::string value = readName();
         std::shared_ptr<StringTag> stringTag = std::make_shared<StringTag>(name);
         stringTag->setValue(value);
         m_root.push_back(stringTag);
         break;
      }
      default:
         goto end_loop;
         break;
      }
   }
   end_loop:
   return m_root;
};

std::string Parser::readName() {
   short nameLength;
   std::string name;
   m_is.read(reinterpret_cast<char*>(&nameLength), 2);
   if (nameLength > 0) {
      std::unique_ptr<char[]> nameBuffer(new char[nameLength]);
      m_is.read(nameBuffer.get(), nameLength);
      return name.assign(nameBuffer.get(), nameLength);
   }
   return name;
}
