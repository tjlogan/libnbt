#include <gtest/gtest.h>
#include <sstream>
#include "parser/parser.h"

TEST(ParserTests, CanReadHeader) {
   const char binary[] = { '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00' };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   ASSERT_EQ(8, parser.version());
   ASSERT_EQ(1234, parser.size());
}

TEST(ParserTests, CanReadZeroedHeader) {
   const char binary[] = { '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00' };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   ASSERT_EQ(0, parser.version());
   ASSERT_EQ(0, parser.size());
}

TEST(ParserTests, ShouldReturnEmptyIfNoTags) {
   const char binary[] = { '\x08','\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00' };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(0, tags.size());
}

TEST(ParserTests, CanParseByteTag) {
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x01', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\xAA'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("BYTE (Test): 0xaa", tags[0]->toString());
}

TEST(ParserTests, CanParseIntTag) {
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x03', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x04', '\x03', '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("INT (Test.): 16909060", tags[0]->toString());
}


TEST(ParserTests, CanParseLongTag) {
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x04', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x08', '\x07', '\x06', '\x05', '\x04', '\x03', '\x02', '\x01'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("LONG (Test.): 72623859790382856", tags[0]->toString());
}

TEST(ParserTests, CanParseString) {
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x08', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x06', '\x00',   'S',    't',    'r',    'i',    'n',    'g'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("STRING (Test.): String", tags[0]->toString());
}

TEST(ParserTests, CanParseEmptyCompound) {
   // Compound Tag immediately followed by an End Tag
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x0A', '\x04', '\x00', '\x54', '\x65', '\x73', '\x74', '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("COMPOUND (Test): [0]", tags[0]->toString());
}

TEST(ParserTests, CanParseCompoundWithMultipleTags) {
   // Compound Tag with an Int and String Tag followed by an End Tag
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04', '\x08', '\x01', '\x00',   'S',
      '\x05', '\x00',   'H',    'e',    'l',    'l',    'o',  '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("COMPOUND (Test.): [2]\nINT (.INT.): 67305985\nSTRING (S): Hello", tags[0]->toString());
}

TEST(ParserTests, CanParseNestedCompound) {
   // Compound Tag with a Compound Tag with an Int Tag followed by End Tags
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x0A', '\x05', '\x00',   'N',    'E',    'S',    'T',    '.',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04', '\x00'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("COMPOUND (Test.): [1]\nCOMPOUND (NEST.): [1]\nINT (.INT.): 67305985", tags[0]->toString());
}

TEST(ParserTests, CanParseCompoundWithChildAndSibling) {
   // Compound Tag with a Byte Tag followed by an End Tag and Int Tag
   const char binary[] = {
      '\x08', '\x00', '\x00', '\x00', '\xD2', '\x04', '\x00', '\x00',
      '\x0A', '\x05', '\x00', '\x54', '\x65', '\x73', '\x74', '\x2E',
      '\x01', '\x03', '\x00',   'B',    'Y',    'T',  '\xFF', '\x00',
      '\x03', '\x05', '\x00',   '.',    'I',    'N',    'T',    '.',
      '\x01', '\x02', '\x03', '\x04'
   };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   std::vector<std::shared_ptr<BaseTag>> tags = parser.parse();
   ASSERT_EQ(2, tags.size());
   ASSERT_EQ("COMPOUND (Test.): [1]\nBYTE (BYT): 0xff\nINT (.INT.): 67305985", tags[0]->toString());
}

TEST(ParserTests, WillThrowErrorIfCompoundTagIsNotEnded) {
   // Compound Tag with no End Tag
   // TODO: Really throw an error?  Or close and set and error flag?
}