#include <memory>
#include <iostream>
#include <iomanip>
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

std::vector<std::shared_ptr<BaseTag>> Parser::parse() {
   char tagBuffer;
   std::string name;
   std::vector<std::vector<std::shared_ptr<BaseTag>>*> tagStack;
   std::vector<std::shared_ptr<BaseTag>>* currentCollection = &m_root;

   while(m_is.read(&tagBuffer, 1)) {
      switch (tagBuffer) {
      case TAG_BYTE: {
         name = readString();
         char value = ParserHelper::read<char>(m_is);
         std::shared_ptr<ByteTag> byteTag = std::make_shared<ByteTag>(name);
         byteTag->setValue(value);
         currentCollection->push_back(byteTag);
         break;
      }
      case TAG_INT: {
         name = readString();
         int value = ParserHelper::read<int>(m_is);
         std::shared_ptr<IntTag> intTag = std::make_shared<IntTag>(name);
         intTag->setValue(value);
         currentCollection->push_back(intTag);
         break;
      }
      case TAG_LONG: {
         name = readString();
         long value = ParserHelper::read<long>(m_is);
         std::shared_ptr<LongTag> longTag = std::make_shared<LongTag>(name);
         longTag->setValue(value);
         currentCollection->push_back(longTag);
         break;
      }
      case TAG_STRING: {
         name = readString();
         std::string value = readString();
         std::shared_ptr<StringTag> stringTag = std::make_shared<StringTag>(name);
         stringTag->setValue(value);
         currentCollection->push_back(stringTag);
         break;
      }
      case TAG_COMPOUND: {
         name = readString();
         std::shared_ptr<CompoundTag> compoundTag = std::make_shared<CompoundTag>(name);
         currentCollection->push_back(compoundTag);
         tagStack.push_back(currentCollection);
         currentCollection = &(compoundTag->children);
         break;
      }
      case TAG_END: {
         currentCollection = tagStack.back();
         tagStack.pop_back();
         break;
      }
      default:
         std::cerr << "Unknown tag encountered while parsing: 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (int)tagBuffer) << "\n";
         goto end_loop;
         break;
      }
   }
   end_loop:
   return m_root;
};

std::string Parser::readString() {
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
