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
      if (tagBuffer != TAG_END) {
         name = readString();
      }
      switch (tagBuffer) {
      case TAG_BYTE: {
         currentCollection->push_back(readByteTag(name));
         break;
      }
      case TAG_SHORT: {
         short value = ParserHelper::read<short>(m_is);
         std::shared_ptr<ShortTag> shortTag = std::make_shared<ShortTag>(name);
         shortTag->setValue(value);
         currentCollection->push_back(shortTag);
         break;
      }
      case TAG_INT: {
         currentCollection->push_back(readIntTag(name));
         break;
      }
      case TAG_LONG: {
         long value = ParserHelper::read<long>(m_is);
         std::shared_ptr<LongTag> longTag = std::make_shared<LongTag>(name);
         longTag->setValue(value);
         currentCollection->push_back(longTag);
         break;
      }
      case TAG_STRING: {
         std::string value = readString();
         std::shared_ptr<StringTag> stringTag = std::make_shared<StringTag>(name);
         stringTag->setValue(value);
         currentCollection->push_back(stringTag);
         break;
      }
      case TAG_COMPOUND: {
         std::shared_ptr<CompoundTag> compoundTag = std::make_shared<CompoundTag>(name);
         currentCollection->push_back(compoundTag);
         tagStack.push_back(currentCollection);
         currentCollection = &(compoundTag->children);
         break;
      }
      case TAG_FLOAT: {
         float value = ParserHelper::read<float>(m_is);
         std::shared_ptr<FloatTag> floatTag = std::make_shared<FloatTag>(name);
         floatTag->setValue(value);
         currentCollection->push_back(floatTag);
         break;
      }
      case TAG_LIST: {
         TagType childType = (TagType)ParserHelper::read<char>(m_is);
         int size = ParserHelper::read<int>(m_is);
         std::shared_ptr<ListTag> listTag = std::make_shared<ListTag>(name, childType);
         std::shared_ptr<BaseTag> childTag;
         for(int i = 0; i < size; i++) {
            switch (childType) {
            case TAG_BYTE: {
               childTag = readByteTag("");
               break;
            }
            case TAG_INT: {
               childTag = readIntTag("");
               break;
            }
            default:
               std::cerr << "Unhandled child type encountered while parsing list: 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (int)childType) << "\n";
               break;
            }
            listTag->children.push_back(childTag);
         }
         currentCollection->push_back(listTag);
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

std::shared_ptr<ByteTag> Parser::readByteTag(std::string name) {
   char value = ParserHelper::read<char>(m_is);
   std::shared_ptr<ByteTag> byteTag = std::make_shared<ByteTag>(name);
   byteTag->setValue(value);
   return byteTag;
}

std::shared_ptr<IntTag> Parser::readIntTag(std::string name) {
   int value = ParserHelper::read<int>(m_is);
   std::shared_ptr<IntTag> intTag = std::make_shared<IntTag>(name);
   intTag->setValue(value);
   return intTag;
}
