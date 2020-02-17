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
   std::vector<BaseTag*> tags = parser.parse();
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
   std::vector<BaseTag*> tags = parser.parse();
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
   std::vector<BaseTag*> tags = parser.parse();
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
   std::vector<BaseTag*> tags = parser.parse();
   ASSERT_EQ(1, tags.size());
   ASSERT_EQ("LONG (Test.): 72623859790382856", tags[0]->toString());
}