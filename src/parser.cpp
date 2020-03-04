#include <memory>
#include <iostream>
#include <iomanip>
#include "libnbt/parser.h"
#include "libnbt/parser_helper.h"

namespace nbt {
   Parser::Parser(std::istream& is) : m_is(is) {};

   std::vector<std::shared_ptr<BaseTag>> Parser::parse() {
      char tagBuffer;
      std::string name;
      std::vector<std::vector<std::shared_ptr<BaseTag>>*> tagStack;
      std::vector<std::shared_ptr<BaseTag>>* currentCollection = &m_root;

      while(m_is.read(&tagBuffer, 1)) {
         if (tagBuffer != TAG_END) {
            name = ParserHelper::read<std::string>(m_is);
         }
         switch (tagBuffer) {
         case TAG_BYTE: {
            currentCollection->push_back(ParserHelper::readTag<char, ByteTag>(m_is, name));
            break;
         }
         case TAG_SHORT: {
            currentCollection->push_back(ParserHelper::readTag<short, ShortTag>(m_is, name));
            break;
         }
         case TAG_INT: {
            currentCollection->push_back(ParserHelper::readTag<int, IntTag>(m_is, name));
            break;
         }
         case TAG_LONG: {
            currentCollection->push_back(ParserHelper::readTag<long, LongTag>(m_is, name));
            break;
         }
         case TAG_FLOAT: {
            currentCollection->push_back(ParserHelper::readTag<float, FloatTag>(m_is, name));
            break;
         }
         case TAG_STRING: {
            currentCollection->push_back(ParserHelper::readTag<std::string, StringTag>(m_is, name));
            break;
         }
         case TAG_COMPOUND: {
            std::shared_ptr<CompoundTag> compoundTag = std::make_shared<CompoundTag>(name);
            currentCollection->push_back(compoundTag);
            tagStack.push_back(currentCollection);
            currentCollection = &(compoundTag->children);
            break;
         }
         case TAG_LIST: {
            TagType childType = (TagType)ParserHelper::read<char>(m_is);
            int size = ParserHelper::read<int>(m_is);
            auto listTag = std::make_shared<ListTag>(name, childType);
            std::shared_ptr<BaseTag> childTag;
            for(int i = 0; i < size; i++) {
               switch (childType) {
               case TAG_BYTE: {
                  childTag = ParserHelper::readTag<char, ByteTag>(m_is, "");
                  break;
               }
               case TAG_INT: {
                  childTag = ParserHelper::readTag<int, IntTag>(m_is, "");
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
            if (!tagStack.empty()) {
               currentCollection = tagStack.back();
               tagStack.pop_back();
            } else {
               std::cerr << "Unpaired End tag encountered\n";
            }
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

   std::shared_ptr<BaseTag> Parser::parseTag() {
      char tagBuffer;
      std::string name;
      std::shared_ptr<BaseTag> tag;

      m_is.read(&tagBuffer, 1);
      if (tagBuffer != TAG_END) {
         name = ParserHelper::read<std::string>(m_is);
      }
      switch (tagBuffer) {
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
            TagType childType = (TagType)ParserHelper::read<char>(m_is);
            int size = ParserHelper::read<int>(m_is);
            auto listTag = std::make_shared<ListTag>(name, childType);
            std::shared_ptr<BaseTag> childTag;
            for(int i = 0; i < size; i++) {
               switch (childType) {
                  case TAG_BYTE: {
                     childTag = ParserHelper::readTag<char, ByteTag>(m_is, "");
                     break;
                  }
                  case TAG_INT: {
                     childTag = ParserHelper::readTag<int, IntTag>(m_is, "");
                     break;
                  }
                  default:
                     std::cerr << "Unhandled child type encountered while parsing list: 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (int)childType) << "\n";
                     break;
               }
               listTag->children.push_back(childTag);
            }
            tag = listTag;
            break;
         }
      }
      return tag;
   }

   std::vector<std::shared_ptr<BaseTag>> Parser::parseUntilEnd() {
      char tagBuffer;
      std::string name;
      std::shared_ptr<BaseTag> tag;
      std::vector<std::shared_ptr<BaseTag>> collection;

      m_is.read(&tagBuffer, 1);
      while(tagBuffer != TAG_END) {
         name = ParserHelper::read<std::string>(m_is);
         switch (tagBuffer) {
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
               TagType childType = (TagType)ParserHelper::read<char>(m_is);
               int size = ParserHelper::read<int>(m_is);
               auto listTag = std::make_shared<ListTag>(name, childType);
               std::shared_ptr<BaseTag> childTag;
               for(int i = 0; i < size; i++) {
                  switch (childType) {
                     case TAG_BYTE: {
                        childTag = ParserHelper::readTag<char, ByteTag>(m_is, "");
                        break;
                     }
                     case TAG_INT: {
                        childTag = ParserHelper::readTag<int, IntTag>(m_is, "");
                        break;
                     }
                     default:
                        std::cerr << "Unhandled child type encountered while parsing list: 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (int)childType) << "\n";
                        break;
                  }
                  listTag->children.push_back(childTag);
               }
               tag = listTag;
               break;
            }
         }
         collection.push_back(tag);
         m_is.read(&tagBuffer, 1);
      }
      return collection;
   }
}
