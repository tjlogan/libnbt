#include <gtest/gtest.h>
#include "tag/base_tag.h"
#include "tag/byte_tag.h"
#include "tag/int_tag.h"
#include "tag/compound_tag.h"

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

// TEST(StringTag, Type) {
//     BaseTag tag = StringTag("test");
//     ASSERT_EQ(TAG_STRING, tag.type());
// }

TEST(CompoundTag, Type) {
    BaseTag* tag = new CompoundTag("test");
    ASSERT_EQ(TAG_COMPOUND, tag->type());
}

TEST(CompoundTag, ToString) {
    CompoundTag tag = CompoundTag("test");
    ASSERT_EQ("COMPOUND (test)", tag.toString());
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
