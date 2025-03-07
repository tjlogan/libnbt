#include <memory>
#include <iostream>
#include <iomanip>
#include "libnbt/parser.h"
#include "libnbt/parser_helper.h"

namespace nbt {
   Parser::Parser(std::istream& is) : m_is(is), error(false), errorMsg() {}

   std::vector<std::shared_ptr<BaseTag>> Parser::parse() {
      char tagBuffer;
      std::string name;
      std::vector<std::vector<std::shared_ptr<BaseTag>>*> tagStack;
      std::vector<std::shared_ptr<BaseTag>>* currentCollection = &m_root;

      while(isGood() && m_is.read(&tagBuffer, 1)) {
         if (tagBuffer == TAG_END) {
            error = true;
            errorMsg = "Unpaired End tag encountered";
            break;
         }
         auto tag = readTag((TagType)tagBuffer);
         if (tag != nullptr) {
            m_root.push_back(tag);
         }
      }
      return m_root;
   }

   std::shared_ptr<BaseTag> Parser::parseTag() {
      char tagBuffer;
      std::string name;
      std::shared_ptr<BaseTag> tag;

      m_is.read(&tagBuffer, 1);
      return readTag((TagType)tagBuffer);
   }

   std::vector<std::shared_ptr<BaseTag>> Parser::parseUntilEnd() {
      char tagBuffer;
      std::string name;
      std::shared_ptr<BaseTag> tag;
      std::vector<std::shared_ptr<BaseTag>> collection = std::vector<std::shared_ptr<BaseTag>>();

      m_is.read(&tagBuffer, 1);
      while(isGood() && tagBuffer != TAG_END) {
         tag = readTag((TagType)tagBuffer);
         collection.push_back(tag);
         m_is.read(&tagBuffer, 1);
      }
      return collection;
   }

   std::shared_ptr<BaseTag> Parser::readTag(TagType tagType) {
      std::string name = ParserHelper::read<std::string>(m_is);
      return decodeTag(tagType, name);
   }

   std::shared_ptr<BaseTag> Parser::decodeTag(TagType tagType, const std::string& name) {
      std::shared_ptr<BaseTag> tag;
      switch (tagType) {
         case TAG_BYTE: {
            tag = ParserHelper::readTag<char, ByteTag>(m_is, name);
            break;
         }
         case TAG_SHORT: {
            tag = ParserHelper::readTag<short, ShortTag>(m_is, name);
            break;
         }
         case TAG_INT: {
            tag = ParserHelper::readTag<int, IntTag>(m_is, name);
            break;
         }
         case TAG_LONG: {
            tag = ParserHelper::readTag<long, LongTag>(m_is, name);
            break;
         }
         case TAG_FLOAT: {
            tag = ParserHelper::readTag<float, FloatTag>(m_is, name);
            break;
         }
         case TAG_BYTE_ARRAY: {
            tag = ParserHelper::readArrayTag<char, ByteArrayTag>(m_is, name);
            break;
         }
         case TAG_STRING: {
            tag = ParserHelper::readTag<std::string, StringTag>(m_is, name);
            break;
         }
         case TAG_COMPOUND: {
            auto compoundTag = std::make_shared<CompoundTag>(name);
            compoundTag->children = parseUntilEnd();
            tag = compoundTag;
            break;
         }
         case TAG_LIST: {
            tag = readList(name);
            break;
         }
         default: {
            auto ss = std::stringstream();
            error = true;
            ss << "Unknown tag encountered while parsing: 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (int)tagType);
            errorMsg = ss.str();
         }
      }
      return tag;
   }

   std::shared_ptr<ListTag> Parser::readList(const std::string& name) {
      auto childType = (TagType)ParserHelper::read<char>(m_is);
      auto size = ParserHelper::read<int>(m_is);
      auto listTag = std::make_shared<ListTag>(name, childType);
      std::shared_ptr<BaseTag> childTag;
      for(int i = 0; i < size; i++) {
         childTag = decodeTag(childType, "");
         listTag->children.push_back(childTag);
      }
      return listTag;
   }

   bool Parser::isError() const {
      return error;
   }

   bool Parser::isGood() const {
      return !isError();
   }

   std::string Parser::getErrorMessage() {
      return errorMsg;
   }
}
