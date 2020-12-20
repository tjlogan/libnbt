#include <gtest/gtest.h>

uint32_t createBitMask(int size) {
   return size > 32 ? 0 :  ((uint64_t)1 << size) - 1;
}

TEST(BitTest, ShouldCreateBitMasks) {
   EXPECT_EQ(0b0, createBitMask(0));
   EXPECT_EQ(0b1, createBitMask(1));
   EXPECT_EQ(0b11, createBitMask(2));
   EXPECT_EQ(0b111, createBitMask(3));
   EXPECT_EQ(0b1111, createBitMask(4));
   EXPECT_EQ(0b11111, createBitMask(5));
   EXPECT_EQ(0b111111, createBitMask(6));
   EXPECT_EQ(0b1111111, createBitMask(7));
   EXPECT_EQ(0b11111111, createBitMask(8));
   EXPECT_EQ(0b111111111, createBitMask(9));
   EXPECT_EQ(0b1111111111, createBitMask(10));
   EXPECT_EQ(0b11111111111, createBitMask(11));
   EXPECT_EQ(0b111111111111, createBitMask(12));
   EXPECT_EQ(0b1111111111111, createBitMask(13));
   EXPECT_EQ(0b11111111111111, createBitMask(14));
   EXPECT_EQ(0b111111111111111, createBitMask(15));
   EXPECT_EQ(0b1111111111111111, createBitMask(16));
   EXPECT_EQ(0b11111111111111111, createBitMask(17));
   EXPECT_EQ(0b111111111111111111, createBitMask(18));
   EXPECT_EQ(0b1111111111111111111, createBitMask(19));
   EXPECT_EQ(0b11111111111111111111, createBitMask(20));
   EXPECT_EQ(0b111111111111111111111, createBitMask(21));
   EXPECT_EQ(0b1111111111111111111111, createBitMask(22));
   EXPECT_EQ(0b11111111111111111111111, createBitMask(23));
   EXPECT_EQ(0b111111111111111111111111, createBitMask(24));
   EXPECT_EQ(0b1111111111111111111111111, createBitMask(25));
   EXPECT_EQ(0b11111111111111111111111111, createBitMask(26));
   EXPECT_EQ(0b111111111111111111111111111, createBitMask(27));
   EXPECT_EQ(0b1111111111111111111111111111, createBitMask(28));
   EXPECT_EQ(0b11111111111111111111111111111, createBitMask(29));
   EXPECT_EQ(0b111111111111111111111111111111, createBitMask(30));
   EXPECT_EQ(0b1111111111111111111111111111111, createBitMask(31));
   EXPECT_EQ(0b11111111111111111111111111111111, createBitMask(32));
   EXPECT_EQ(0b0, createBitMask(33));
}
