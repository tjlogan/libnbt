#include <gtest/gtest.h>
#include "tag.h"

TEST(BaseTag, Name) { 
    BaseTag tag = ByteTag("test");
    ASSERT_EQ("test", tag.name());
}
 
TEST(ByteTag, Type) {
    BaseTag tag = ByteTag("test");
    ASSERT_EQ(TAG_BYTE, tag.type());
}

TEST(ByteTag, Value) {
    ByteTag tag = ByteTag("test");
    tag.setValue('x');
    ASSERT_EQ('x', tag.value());
}

TEST(IntTag, Type) {
    BaseTag tag = IntTag("test");
    ASSERT_EQ(TAG_INT, tag.type());
}

TEST(StringTag, Type) {
    BaseTag tag = StringTag("test");
    ASSERT_EQ(TAG_STRING, tag.type());
}

TEST(CompoundTag, Type) {
    BaseTag tag = CompoundTag("test");
    ASSERT_EQ(TAG_COMPOUND, tag.type());
}

TEST(CompoundTag, Value) {
    CompoundTag tag = CompoundTag("test");
    ByteTag byteTag = ByteTag("byte");
    byteTag.setValue('x');
    tag.add(byteTag);
    IntTag intTag = IntTag("int");
    intTag.setValue(123456789);
    tag.add(intTag);
    std::vector<BaseTag> tags = tag.value();

    ASSERT_EQ(tags[0].name(), "byte");
    ASSERT_EQ(tags[1].name(), "int");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}