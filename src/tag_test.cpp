#include <gtest/gtest.h>
#include "tag/tag.h"

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

TEST(CompoundTag, EmptyToString) {
    CompoundTag tag = CompoundTag("test");
    ASSERT_EQ("COMPOUND (test): [0]", tag.toString());
}

TEST(CompoundTag, WithOneChild) {
    CompoundTag tag = CompoundTag("test");
    std::shared_ptr<ByteTag> byteTag = std::make_shared<ByteTag>("byte");
    byteTag->setValue('a');
    tag.children.push_back(byteTag);
    ASSERT_EQ("COMPOUND (test): [1]\nBYTE (byte): 0x61", tag.toString());
}

TEST(CompoundTag, WithMultipleChildren) {
    CompoundTag tag = CompoundTag("test");
    std::shared_ptr<ByteTag> byteTag = std::make_shared<ByteTag>("byte");
    byteTag->setValue('a');
    std::shared_ptr<IntTag> intTag = std::make_shared<IntTag>("int");
    intTag->setValue(1);
    tag.children.push_back(byteTag);
    tag.children.push_back(intTag);
    ASSERT_EQ("COMPOUND (test): [2]\nBYTE (byte): 0x61\nINT (int): 1", tag.toString());
}

TEST(CompoundTag, WithNestedCompoundTags) {
    CompoundTag tag = CompoundTag("test");
    std::shared_ptr<CompoundTag> nestedTag = std::make_shared<CompoundTag>("nested");
    std::shared_ptr<ByteTag> byteTag = std::make_shared<ByteTag>("byte");
    byteTag->setValue('a');
    nestedTag->children.push_back(byteTag);
    tag.children.push_back(nestedTag);
    ASSERT_EQ("COMPOUND (test): [1]\nCOMPOUND (nested): [1]\nBYTE (byte): 0x61", tag.toString());
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

TEST(ListTag, Type) {
    BaseTag* tag = new ListTag("test", TAG_BYTE);
    ASSERT_EQ(TAG_LIST, tag->type());
}

TEST(ListTag, Empty) {
    ListTag tag = ListTag("test", TAG_BYTE);
    ASSERT_EQ(0, tag.size());
    ASSERT_EQ("LIST (test): [0]", tag.toString());
}

TEST(ListTag, WithBytes) {
    ListTag tag = ListTag("test", TAG_BYTE);
    auto byteTag = std::make_shared<ByteTag>("");
    byteTag->setValue(0);
    tag.children.push_back(byteTag);
    ASSERT_EQ(1, tag.size());
    ASSERT_EQ(TAG_BYTE, tag.childType());
    ASSERT_EQ("LIST (test): [1]\nBYTE (): 0x00", tag.toString());
}

TEST(ListTag, WithInts) {
    ListTag tag = ListTag("test", TAG_INT);
    auto intTag = std::make_shared<IntTag>("");
    intTag->setValue(1000);
    tag.children.push_back(intTag);
    ASSERT_EQ(1, tag.size());
    ASSERT_EQ(TAG_INT, tag.childType());
    ASSERT_EQ("LIST (test): [1]\nINT (): 1000", tag.toString());
}