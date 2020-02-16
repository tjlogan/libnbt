#include <gtest/gtest.h>
#include "tag/base_tag.h"
#include "tag/byte_tag.h"
#include "tag/int_tag.h"
#include "tag/compound_tag.h"
#include "tag/string_tag.h"
#include "tag/long_tag.h"

TEST(BaseTag, Name) { 
    BaseTag* tag = new ByteTag("test");
    ASSERT_EQ("test", tag->name());
}
 
TEST(ByteTag, Type) {
    BaseTag* tag = new ByteTag("test");
    ASSERT_EQ(TAG_BYTE, tag->type());
}

TEST(ByteTag, Value) {
    ByteTag tag = ByteTag("test");
    tag.setValue('x');
    ASSERT_EQ('x', tag.value());
}

TEST(ByteTag, ToString) {
    ByteTag tag = ByteTag("test");
    tag.setValue('x');
    ASSERT_EQ("BYTE (test): 0x78", tag.toString());
}

TEST(ByteTag, ToString_Negative) {
    ByteTag tag = ByteTag("test");
    tag.setValue(-1);
    ASSERT_EQ("BYTE (test): 0xff", tag.toString());
}

TEST(IntTag, Type) {
    BaseTag* tag = new IntTag("test");
    ASSERT_EQ(TAG_INT, tag->type());
}

TEST(IntTag, Value) {
    IntTag tag = IntTag("test");
    tag.setValue(1025);
    ASSERT_EQ(1025, tag.value());
}

TEST(IntTag, Value_Negative) {
    IntTag tag = IntTag("test");
    tag.setValue(-1025);
    ASSERT_EQ(-1025, tag.value());
}

TEST(IntTag, ToString) {
    IntTag tag = IntTag("test");
    tag.setValue(1025);
    ASSERT_EQ("INT (test): 1025", tag.toString());
}

TEST(IntTag, ToString_Negative) {
    IntTag tag = IntTag("test");
    tag.setValue(-1025);
    ASSERT_EQ("INT (test): -1025", tag.toString());
}

TEST(StringTag, Type) {
    BaseTag* tag = new StringTag("test");
    ASSERT_EQ(TAG_STRING, tag->type());
}

TEST(StringTag, Value) {
    StringTag tag = StringTag("test");
    tag.setValue("my string value");
    ASSERT_EQ("my string value", tag.value());
}

TEST(StringTag, ToString) {
    StringTag tag = StringTag("test");
    tag.setValue("testing");
    ASSERT_EQ("STRING (test): testing", tag.toString());
}

TEST(CompoundTag, Type) {
    BaseTag* tag = new CompoundTag("test");
    ASSERT_EQ(TAG_COMPOUND, tag->type());
}

TEST(CompoundTag, ToString) {
    CompoundTag tag = CompoundTag("test");
    ASSERT_EQ("COMPOUND (test)", tag.toString());
}

TEST(LongTag, Type) {
    BaseTag* tag = new LongTag("test");
    ASSERT_EQ(TAG_LONG, tag->type());
}

TEST(LongTag, Value) {
    LongTag tag = LongTag("test");
    tag.setValue(4147483647);
    ASSERT_EQ(4147483647, tag.value());
}

TEST(LongTag, Value_Negative) {
    LongTag tag = LongTag("test");
    tag.setValue(-4147483647);
    ASSERT_EQ(-4147483647, tag.value());
}

TEST(LongTag, ToString) {
    LongTag tag = LongTag("test");
    tag.setValue(4147483647);
    ASSERT_EQ("LONG (test): 4147483647", tag.toString());
}

TEST(LongTag, ToString_Negative) {
    LongTag tag = LongTag("test");
    tag.setValue(-4147483647);
    ASSERT_EQ("LONG (test): -4147483647", tag.toString());
}
// TEST(CompoundTag, Value) {
//     CompoundTag tag = CompoundTag("test");
//     ByteTag byteTag = ByteTag("byte");
//     byteTag.setValue('x');
//     tag.add(byteTag);
//     IntTag intTag = IntTag("int");
//     intTag.setValue(123456789);
//     tag.add(intTag);
//     std::vector<BaseTag> tags = tag.value();

//     ASSERT_EQ(tags[0].name(), "byte");
//     ASSERT_EQ(tags[1].name(), "int");
// }
