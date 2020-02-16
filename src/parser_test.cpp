#include <gtest/gtest.h>
#include <sstream>
#include "parser/parser.h"

TEST(PARSER, CAN_READ_HEADER) {
   const char binary[] = { 0x08, 0x00, 0x00, 0x00, 0xD2, 0x04, 0x00, 0x00 };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   ASSERT_EQ(8, parser.version());
   ASSERT_EQ(1234, parser.size());
}

TEST(PARSER, CAN_READ_ZEROED_HEADER) {
   const char binary[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
   std::string str(binary, sizeof(binary));
   std::istringstream iss(str);
   Parser parser = Parser(iss);
   ASSERT_EQ(0, parser.version());
   ASSERT_EQ(0, parser.size());
}