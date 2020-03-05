#include <gtest/gtest.h>
#include <sstream>
#include "libnbt/parser.h"

TEST(ParseTests, ShouldReturnEmptyIfNoTags) {
   const char binary[] = {};
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(0, tags.size());
}

TEST(ParseTests, CanParseByteTag) {
   const char binary[] = {
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xAA'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("BYTE (Test): 0xaa", tags[0]->toString());
}

TEST(ParseTests, CanParseIntTag) {
   const char binary[] = {
      '\x03', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x04', '\x03', '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("INT (Test.): 16909060", tags[0]->toString());
}

TEST(ParseTests, CanParseIntTagNegative) {
   const char binary[] = {
      '\x03', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x18', '\xFC', '\xFF', '\xFF'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("INT (Test.): -1000", tags[0]->toString());
}

TEST(ParseTests, CanParseShortTag) {
   const char binary[] = {
      '\x02', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("SHORT (Test.): 258", tags[0]->toString());
}

TEST(ParseTests, CanParseShortTagNegative) {
   const char binary[] = {
      '\x02', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\xFE', '\xFE'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("SHORT (Test.): -258", tags[0]->toString());
}

TEST(ParseTests, CanParseLongTag) {
   const char binary[] = {
      '\x04', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x08', '\x07', '\x06', '\x05', '\x04', '\x03', '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("LONG (Test.): 72623859790382856", tags[0]->toString());
}

TEST(ParseTests, CanParseLongTagNegative) {
   const char binary[] = {
      '\x04', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x00', '\x36', '\x65', '\xC4', '\xFF', '\xFF', '\xFF', '\xFF'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("LONG (Test.): -1000000000", tags[0]->toString());
}

TEST(ParseTests, CanParseString) {
   const char binary[] = {
      '\x08', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x06', '\x00',   'S',    't',    'r',    'i',    'n',    'g'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("STRING (Test.): String", tags[0]->toString());
}

TEST(ParseTests, CanParseEmptyCompound) {
   // Compound Tag immediately followed by an End Tag
   const char binary[] = {
      '\x0A', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("COMPOUND (Test): [0]", tags[0]->toString());
}

TEST(ParseTests, CanParseCompoundWithMultipleTags) {
   // Compound Tag with an Int and String Tag followed by an End Tag
   const char binary[] = {
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04', '\x08', '\x01', '\x00',   'S',
      '\x05', '\x00',   'H',    'e',    'l',    'l',    'o',  '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("COMPOUND (Test.): [2]\nINT (.INT.): 67305985\nSTRING (S): Hello", tags[0]->toString());
}

TEST(ParseTests, CanParseNestedCompound) {
   // Compound Tag with a Compound Tag with an Int Tag followed by End Tags
   const char binary[] = {
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x0A', '\x05', '\x00',   'N',    'E',    'S',    'T',    '.',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04', '\x00', '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("COMPOUND (Test.): [1]\nCOMPOUND (NEST.): [1]\nINT (.INT.): 67305985", tags[0]->toString());
}

TEST(ParseTests, CanParseCompoundWithChildAndSibling) {
   // Compound Tag with a Byte Tag followed by an End Tag and Int Tag
   const char binary[] = {
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x01', '\x03', '\x00',   'B',    'Y',    'T',  '\xFF', '\x00',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(2, tags.size());
   ASSERT_EQ("COMPOUND (Test.): [1]\nBYTE (BYT): 0xff", tags[0]->toString());
   ASSERT_EQ("INT (.INT.): 67305985", tags[1]->toString());
}

TEST(ParseTests, CanParseListofBytes) {
   // List tag of 3 Bytes 
   const char binary[] = {
      '\x09', '\x05', '\x00',   'L',    'I',    'S',    'T',   '.',
      '\x01', '\x03', '\x00', '\x00', '\x00', '\x01', '\x02', '\x03',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("LIST (LIST.): [3]\nBYTE (): 0x01\nBYTE (): 0x02\nBYTE (): 0x03", tags[0]->toString());
}

TEST(ParseTests, CanParseListOfInts) {
   // List tag of 2 Ints
   const char binary[] = {
      '\x09', '\x05', '\x00',   'L',    'I',    'S',    'T',   '.',
      '\x03', '\x02', '\x00', '\x00', '\x00', '\x64', '\x00', '\x00',
      '\x00', '\xC8', '\x00', '\x00', '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("LIST (LIST.): [2]\nINT (): 100\nINT (): 200", tags[0]->toString());
}

TEST(ParseTests, CanParseFloatTag) {
   const char binary[] = {
      '\x05', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x55', '\x55', '\x55', '\x55'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   auto floatTag = std::dynamic_pointer_cast<nbt::FloatTag>(tags[0]);
   ASSERT_EQ(14660154687488, floatTag->value());
   ASSERT_EQ("FLOAT (Test.): 1.46602e+13", tags[0]->toString());
}

TEST(ParseTests, CanParseFloatTagNegative) {
   const char binary[] = {
      '\x05', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x55', '\x55', '\x55', '\xD5'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   auto floatTag = std::dynamic_pointer_cast<nbt::FloatTag>(tags[0]);
   ASSERT_EQ(-14660154687488, floatTag->value());
   ASSERT_EQ("FLOAT (Test.): -1.46602e+13", tags[0]->toString());
}

TEST(ParseTagTests, CanParseSingleByteTag) {
   // Three Byte Tags
   const char binary[] = {
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xAA',
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xBB',
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xCC',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::shared_ptr<nbt::BaseTag> tag = parser.parseTag();
   auto byteTag = std::dynamic_pointer_cast<nbt::ByteTag>(tag);
   ASSERT_NE(nullptr, byteTag);
   ASSERT_EQ('\xAA', byteTag->value());
}

TEST(ParseTagTests, CanParseMultipleSingleTags) {
   // Three Byte Tags
   const char binary[] = {
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xAA',
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xBB',
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xCC',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto tag1 = std::dynamic_pointer_cast<nbt::ByteTag>(parser.parseTag());
   auto tag2 = std::dynamic_pointer_cast<nbt::ByteTag>(parser.parseTag());
   ASSERT_NE(nullptr, tag1);
   ASSERT_NE(nullptr, tag2);
   ASSERT_EQ('\xAA', tag1->value());
   ASSERT_EQ('\xBB', tag2->value());
}

TEST(ParseTagTests, CanParseSingleIntTag) {
   const char binary[] = {
      '\x03', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x04', '\x03', '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto intTag = std::dynamic_pointer_cast<nbt::IntTag>(parser.parseTag());
   ASSERT_NE(nullptr, intTag);
   ASSERT_EQ(16909060, intTag->value());
}

TEST(ParseTagTests, CanParseSingleShortTag) {
   const char binary[] = {
      '\x02', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto shortTag = std::dynamic_pointer_cast<nbt::ShortTag>(parser.parseTag());
   ASSERT_NE(nullptr, shortTag);
   ASSERT_EQ(258, shortTag->value());
}

TEST(ParseTagTests, CanParseSingleLongTag) {
   const char binary[] = {
      '\x04', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x08', '\x07', '\x06', '\x05', '\x04', '\x03', '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto longTag = std::dynamic_pointer_cast<nbt::LongTag>(parser.parseTag());
   ASSERT_NE(nullptr, longTag);
   ASSERT_EQ(72623859790382856, longTag->value());
}

TEST(ParseTagTests, CanParseSingleFloatTag) {
   const char binary[] = {
      '\x05', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x55', '\x55', '\x55', '\x55'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto floatTag = std::dynamic_pointer_cast<nbt::FloatTag>(parser.parseTag());
   ASSERT_NE(nullptr, floatTag);
   ASSERT_EQ(14660154687488, floatTag->value());
}

TEST(ParseTagTests, CanParseSingleStringTag) {
   const char binary[] = {
      '\x08', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x06', '\x00',   'S',    't',    'r',    'i',    'n',    'g'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto stringTag = std::dynamic_pointer_cast<nbt::StringTag>(parser.parseTag());
   ASSERT_NE(nullptr, stringTag);
   ASSERT_EQ("String", stringTag->value());
}

TEST(ParseTagTests, CanParseSingleCompoundTag) {
   // Compound Tag with an Int and String Tag followed by an End Tag
   const char binary[] = {
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04', '\x08', '\x01', '\x00',   'S',
      '\x05', '\x00',   'H',    'e',    'l',    'l',    'o',  '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto compoundTag = std::dynamic_pointer_cast<nbt::CompoundTag>(parser.parseTag());
   ASSERT_NE(nullptr, compoundTag);
   ASSERT_EQ(2, compoundTag->children.size());
   ASSERT_EQ(nbt::TAG_INT, compoundTag->children[0]->type());
   ASSERT_EQ(nbt::TAG_STRING, compoundTag->children[1]->type());
}

TEST(ParseTagTests, CanParseSingleNestedCompound) {
   // Compound Tag with a Compound Tag with two Int Tags followed by End Tags
   const char binary[] = {
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x0A', '\x05', '\x00',   'N',    'E',    'S',    'T',    '.',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '1',
      '\x01', '\x02', '\x03', '\x04',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '2',
      '\x01', '\x02', '\x03', '\x04', '\x00', '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto compoundTag = std::dynamic_pointer_cast<nbt::CompoundTag>(parser.parseTag());
   ASSERT_NE(nullptr, compoundTag);
   ASSERT_EQ(1, compoundTag->children.size());
   auto nestedCompoundTag = std::dynamic_pointer_cast<nbt::CompoundTag>(compoundTag->children[0]);
   ASSERT_EQ(2, nestedCompoundTag->children.size());
   ASSERT_EQ(".INT1", nestedCompoundTag->children[0]->name());
   ASSERT_EQ(".INT2", nestedCompoundTag->children[1]->name());
}

TEST(ParseTagTests, CanParseSingleListOfBytes) {
   // List tag of 3 Bytes
   const char binary[] = {
      '\x09', '\x05', '\x00',   'L',    'I',    'S',    'T',   '.',
      '\x01', '\x03', '\x00', '\x00', '\x00', '\x01', '\x02', '\x03',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto listTag = std::dynamic_pointer_cast<nbt::ListTag>(parser.parseTag());
   ASSERT_NE(nullptr, listTag);
   ASSERT_EQ(3, listTag->children.size());
}

TEST(ParseTagTests, CanParseSingleCompoundTagWithList) {
   // Compound Tag with a List Tag with two Byte Tags followed by an End Tag
   const char binary[] = {
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x09', '\x05', '\x00',   'L',    'I',    'S',    'T',   '.',
      '\x01', '\x02', '\x00', '\x00', '\x00', '\x01', '\x02', '\x00',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   auto compoundTag = std::dynamic_pointer_cast<nbt::CompoundTag>(parser.parseTag());
   ASSERT_NE(nullptr, compoundTag);
   ASSERT_EQ(1, compoundTag->children.size());
   ASSERT_EQ(nbt::TAG_LIST, compoundTag->children[0]->type());
   auto listTag = std::dynamic_pointer_cast<nbt::ListTag>(compoundTag->children[0]);
   ASSERT_EQ(2, listTag->size());
   ASSERT_EQ(nbt::TAG_BYTE, listTag->childType());
}

TEST(ParseErrorTests, NoErrorStateOnCreation){
   const char binary[] = {
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xAA'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   ASSERT_EQ(false, parser.isError());
   ASSERT_EQ(true, parser.isGood());
   ASSERT_EQ(true, parser.getErrorMessage().empty());
}

TEST(ParseErrorTests, WillSetErrorStateOnUnpairedEndTag) {
   // Compound Tag immediately followed by two End Tags then another compound tag
   const char binary[] = {
      '\x0A', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\x00',
      '\x00', '\x0A', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(true, parser.isError());
   ASSERT_EQ(false, parser.isGood());
   ASSERT_EQ("Unpaired End tag encountered", parser.getErrorMessage());
   ASSERT_EQ(1, tags.size());
}

TEST(ParseErrorTests, WillSetErrorStateOnUnknownTag) {
   // Compound Tag, but the tag type is or'ed with 0x10;
   const char binary[] = {
      '\x1A', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\x00',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(true, parser.isError());
   ASSERT_EQ(false, parser.isGood());
   ASSERT_EQ("Unknown tag encountered while parsing: 0x1a", parser.getErrorMessage());
   ASSERT_EQ(0, tags.size());
}

TEST(ParseErrorTests, WillSetErrorStateOnUnsupportedListTag) {
   // List tag of 1 Short
   const char binary[] = {
      '\x09', '\x05', '\x00',   'L',    'I',    'S',    'T',   '.',
      '\x02', '\x01', '\x00', '\x00', '\x00', '\x01', '\x02',
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   auto parser = nbt::Parser(iss);
   std::vector<std::shared_ptr<nbt::BaseTag>> tags = parser.parse();
   ASSERT_EQ(true, parser.isError());
   ASSERT_EQ(false, parser.isGood());
   ASSERT_EQ("Unhandled child type encountered while parsing list: 0x02", parser.getErrorMessage());
   ASSERT_EQ(1, tags.size());
}
