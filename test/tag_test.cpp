#include <gtest/gtest.h>
#include "libnbt/parser/tag/tag.h"

TEST(BaseTag, Name) { 
    nbt::BaseTag* tag = new nbt::ByteTag("test");
    ASSERT_EQ("test", tag->name());
}
 
TEST(ByteTag, Type) {
    nbt::BaseTag* tag = new nbt::ByteTag("test");
    ASSERT_EQ(nbt::TAG_BYTE, tag->type());
}

TEST(ByteTag, Value) {
    auto tag = nbt::ByteTag("test");
    tag.setValue('x');
    ASSERT_EQ('x', tag.value());
}

TEST(ByteTag, ToString) {
    auto tag = nbt::ByteTag("test");
    tag.setValue('x');
    ASSERT_EQ("BYTE (test): 0x78", tag.toString());
}

TEST(ByteTag, ToString_Negative) {
    auto tag = nbt::ByteTag("test");
    tag.setValue(-1);
    ASSERT_EQ("BYTE (test): 0xff", tag.toString());
}

TEST(IntTag, Type) {
    nbt::BaseTag* tag = new nbt::IntTag("test");
    ASSERT_EQ(nbt::TAG_INT, tag->type());
}

TEST(IntTag, Value) {
    auto tag = nbt::IntTag("test");
    tag.setValue(1025);
    ASSERT_EQ(1025, tag.value());
}

TEST(IntTag, Value_Negative) {
    auto tag = nbt::IntTag("test");
    tag.setValue(-1025);
    ASSERT_EQ(-1025, tag.value());
}

TEST(IntTag, ToString) {
    auto tag = nbt::IntTag("test");
    tag.setValue(1025);
    ASSERT_EQ("INT (test): 1025", tag.toString());
}

TEST(IntTag, ToString_Negative) {
    auto tag = nbt::IntTag("test");
    tag.setValue(-1025);
    ASSERT_EQ("INT (test): -1025", tag.toString());
}

TEST(ShortTag, Type) {
    nbt::BaseTag* tag = new nbt::ShortTag("test");
    ASSERT_EQ(nbt::TAG_SHORT, tag->type());
}

TEST(ShortTag, Value) {
    auto tag = nbt::ShortTag("test");
    tag.setValue(1025);
    ASSERT_EQ(1025, tag.value());
}

TEST(ShortTag, Value_Negative) {
    auto tag = nbt::ShortTag("test");
    tag.setValue(-1025);
    ASSERT_EQ(-1025, tag.value());
}

TEST(ShortTag, ToString) {
    auto tag = nbt::ShortTag("test");
    tag.setValue(1025);
    ASSERT_EQ("SHORT (test): 1025", tag.toString());
}

TEST(ShortTag, ToString_Negative) {
    auto tag = nbt::ShortTag("test");
    tag.setValue(-1025);
    ASSERT_EQ("SHORT (test): -1025", tag.toString());
}

TEST(StringTag, Type) {
    nbt::BaseTag* tag = new nbt::StringTag("test");
    ASSERT_EQ(nbt::TAG_STRING, tag->type());
}

TEST(StringTag, Value) {
    auto tag = nbt::StringTag("test");
    tag.setValue("my string value");
    ASSERT_EQ("my string value", tag.value());
}

TEST(StringTag, ToString) {
    auto tag = nbt::StringTag("test");
    tag.setValue("testing");
    ASSERT_EQ("STRING (test): testing", tag.toString());
}

TEST(CompoundTag, Type) {
    nbt::BaseTag* tag = new nbt::CompoundTag("test");
    ASSERT_EQ(nbt::TAG_COMPOUND, tag->type());
}

TEST(CompoundTag, EmptyToString) {
    auto tag = nbt::CompoundTag("test");
    ASSERT_EQ("COMPOUND (test): [0]", tag.toString());
}

TEST(CompoundTag, WithOneChild) {
    auto tag = nbt::CompoundTag("test");
    auto byteTag = std::make_shared<nbt::ByteTag>("byte");
    byteTag->setValue('a');
    tag.children.push_back(byteTag);
    ASSERT_EQ("COMPOUND (test): [1]\nBYTE (byte): 0x61", tag.toString());
}

TEST(CompoundTag, WithMultipleChildren) {
    auto tag = nbt::CompoundTag("test");
    auto byteTag = std::make_shared<nbt::ByteTag>("byte");
    byteTag->setValue('a');
    auto intTag = std::make_shared<nbt::IntTag>("int");
    intTag->setValue(1);
    tag.children.push_back(byteTag);
    tag.children.push_back(intTag);
    ASSERT_EQ("COMPOUND (test): [2]\nBYTE (byte): 0x61\nINT (int): 1", tag.toString());
}

TEST(CompoundTag, WithNestedCompoundTags) {
    auto tag = nbt::CompoundTag("test");
    auto nestedTag = std::make_shared<nbt::CompoundTag>("nested");
    auto byteTag = std::make_shared<nbt::ByteTag>("byte");
    byteTag->setValue('a');
    nestedTag->children.push_back(byteTag);
    tag.children.push_back(nestedTag);
    ASSERT_EQ("COMPOUND (test): [1]\nCOMPOUND (nested): [1]\nBYTE (byte): 0x61", tag.toString());
}

TEST(LongTag, Type) {
    nbt::BaseTag* tag = new nbt::LongTag("test");
    ASSERT_EQ(nbt::TAG_LONG, tag->type());
}

TEST(LongTag, Value) {
    auto tag = nbt::LongTag("test");
    tag.setValue(4147483647);
    ASSERT_EQ(4147483647, tag.value());
}

TEST(LongTag, Value_Negative) {
    auto tag = nbt::LongTag("test");
    tag.setValue(-4147483647);
    ASSERT_EQ(-4147483647, tag.value());
}

TEST(LongTag, ToString) {
    auto tag = nbt::LongTag("test");
    tag.setValue(4147483647);
    ASSERT_EQ("LONG (test): 4147483647", tag.toString());
}

TEST(LongTag, ToString_Negative) {
    auto tag = nbt::LongTag("test");
    tag.setValue(-4147483647);
    ASSERT_EQ("LONG (test): -4147483647", tag.toString());
}

TEST(ListTag, Type) {
    nbt::BaseTag* tag = new nbt::ListTag("test", nbt::TAG_BYTE);
    ASSERT_EQ(nbt::TAG_LIST, tag->type());
}

TEST(ListTag, Empty) {
    auto tag = nbt::ListTag("test", nbt::TAG_BYTE);
    ASSERT_EQ(0, tag.size());
    ASSERT_EQ("LIST (test): [0]", tag.toString());
}

TEST(ListTag, WithBytes) {
    auto tag = nbt::ListTag("test", nbt::TAG_BYTE);
    auto byteTag = std::make_shared<nbt::ByteTag>("");
    byteTag->setValue(0);
    tag.children.push_back(byteTag);
    ASSERT_EQ(1, tag.size());
    ASSERT_EQ(nbt::TAG_BYTE, tag.childType());
    ASSERT_EQ("LIST (test): [1]\nBYTE (): 0x00", tag.toString());
}

TEST(ListTag, WithInts) {
    auto tag = nbt::ListTag("test", nbt::TAG_INT);
    auto intTag = std::make_shared<nbt::IntTag>("");
    intTag->setValue(1000);
    tag.children.push_back(intTag);
    ASSERT_EQ(1, tag.size());
    ASSERT_EQ(nbt::TAG_INT, tag.childType());
    ASSERT_EQ("LIST (test): [1]\nINT (): 1000", tag.toString());
}

TEST(FloatTag, Type) {
    nbt::BaseTag* tag = new nbt::FloatTag("test");
    ASSERT_EQ(nbt::TAG_FLOAT, tag->type());
}

TEST(FloatTag, Value) {
    auto tag = nbt::FloatTag("test");
    tag.setValue(3.140625);
    ASSERT_EQ(3.140625, tag.value());
}

TEST(FloatTag, Value_Negative) {
    auto tag = nbt::FloatTag("test");
    tag.setValue(-3.140625);
    ASSERT_EQ(-3.140625, tag.value());
}

TEST(FloatTag, ToString) {
    auto tag = nbt::FloatTag("test");
    tag.setValue(3.140625);
    ASSERT_EQ("FLOAT (test): 3.14062", tag.toString());
}

TEST(FloatTag, ToString_Negative) {
    auto tag = nbt::FloatTag("test");
    tag.setValue(-3.140625);
    ASSERT_EQ("FLOAT (test): -3.14062", tag.toString());
}