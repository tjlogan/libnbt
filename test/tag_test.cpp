#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <gtest/gtest.h>
#include "libnbt/tag/tag.h"

TEST(BaseTag, Name) { 
    nbt::BaseTag* tag = new nbt::ByteTag("test");
    ASSERT_EQ("test", tag->name());
}

TEST(BaseTag, GetTag) {
    auto compoundTag = new nbt::CompoundTag("test");
    auto childTag = new nbt::ByteTag("child");
    childTag->setValue(10);
    compoundTag->children.push_back(std::shared_ptr<nbt::ByteTag>(childTag));
    nbt::BaseTag* tag = compoundTag;

    auto byteTag = tag->getTag<nbt::ByteTag>("child");
    ASSERT_EQ(10, byteTag->value());
}

TEST(BaseTag, GetTag_NotFound) {
    auto compoundTag = new nbt::CompoundTag("test");
    auto childTag = new nbt::ByteTag("child");
    childTag->setValue(10);
    compoundTag->children.push_back(std::shared_ptr<nbt::ByteTag>(childTag));
    nbt::BaseTag* tag = compoundTag;

    auto byteTag = tag->getTag<nbt::ByteTag>("not found");
    ASSERT_EQ(nullptr, byteTag);
}

TEST(BaseTag, GetTag_WrongClass) {
    auto compoundTag = new nbt::CompoundTag("test");
    auto childTag = new nbt::ByteTag("child");
    childTag->setValue(10);
    compoundTag->children.push_back(std::shared_ptr<nbt::ByteTag>(childTag));
    nbt::BaseTag* tag = compoundTag;

    auto byteTag = tag->getTag<nbt::IntTag>("child");
    ASSERT_EQ(nullptr, byteTag);
}

TEST(BaseTag, GetValueOrDefault) {
   auto compoundTag = new nbt::CompoundTag("test");
   auto childTag = new nbt::ByteTag("child");
   childTag->setValue(10);
   compoundTag->children.push_back(std::shared_ptr<nbt::ByteTag>(childTag));
   nbt::BaseTag* tag = compoundTag;

   auto byte = tag->getValueOrDefault<nbt::ByteTag>("child", 42);
   ASSERT_EQ(byte, 10);
}

TEST(BaseTag, GetValueOrDefault_NameNotFound) {
   auto compoundTag = new nbt::CompoundTag("test");
   auto childTag = new nbt::ByteTag("child");
   childTag->setValue(10);
   compoundTag->children.push_back(std::shared_ptr<nbt::ByteTag>(childTag));
   nbt::BaseTag* tag = compoundTag;

   auto byte = tag->getValueOrDefault<nbt::ByteTag>("not-found", 42);
   ASSERT_EQ(byte, 42);
}

TEST(BaseTag, GetValueOrDefault_WrongClass) {
   auto compoundTag = new nbt::CompoundTag("test");
   auto childTag = new nbt::ByteTag("child");
   childTag->setValue(10);
   compoundTag->children.push_back(std::shared_ptr<nbt::ByteTag>(childTag));
   nbt::BaseTag* tag = compoundTag;

   auto byte = tag->getValueOrDefault<nbt::IntTag>("not-found", 42);
   ASSERT_EQ(byte, 42);
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

TEST(ByteTag, GetTag) {
    auto tag = nbt::ByteTag("test");
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
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

TEST(IntTag, GetTag) {
    auto tag = nbt::IntTag("test");
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
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

TEST(ShortTag, GetTag) {
    auto tag = nbt::ShortTag("test");
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
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

TEST(StringTag, GetTag) {
    auto tag = nbt::StringTag("test");
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
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

TEST(CompoundTag, GetTagWithMultipleChildren) {
    auto tag = nbt::CompoundTag("test");
    auto byteTag = std::make_shared<nbt::ByteTag>("byte");
    byteTag->setValue('a');
    auto intTag = std::make_shared<nbt::IntTag>("int");
    intTag->setValue(1);
    tag.children.push_back(byteTag);
    tag.children.push_back(intTag);

    auto retrievedTag = (nbt::IntTag*)(tag.getTag("int").get());
    ASSERT_EQ(retrievedTag->value(), 1);
}

TEST(CompoundTag, GetTagWithNestedCompoundTags) {
    auto tag = nbt::CompoundTag("test");
    auto nestedTag = std::make_shared<nbt::CompoundTag>("nested");
    auto byteTag = std::make_shared<nbt::ByteTag>("byte");
    byteTag->setValue('a');
    nestedTag->children.push_back(byteTag);
    tag.children.push_back(nestedTag);

    auto retrievedTag = (nbt::ByteTag*)(tag.getTag("nested")->getTag("byte").get());
    ASSERT_EQ(retrievedTag->value(), 'a');
}

TEST(CompoundTag, GetTagNotFound) {
    auto tag = nbt::CompoundTag("test");
    auto byteTag = std::make_shared<nbt::ByteTag>("byte");
    tag.children.push_back(byteTag);

    auto retrievedTag = (nbt::ByteTag*)(tag.getTag("not byte").get());
    ASSERT_EQ(retrievedTag, nullptr);
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

TEST(LongTag, GetTag) {
    auto tag = nbt::LongTag("test");
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
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

TEST(ListTag, GetTag) {
    auto tag = nbt::ListTag("test", nbt::TAG_INT);
    auto intTag = std::make_shared<nbt::IntTag>("int1");
    intTag->setValue(1000);
    tag.children.push_back(intTag);
    auto intTag2 = std::make_shared<nbt::IntTag>("int2");
    intTag2->setValue(2000);
    tag.children.push_back(intTag2);

    auto retrievedTag = (nbt::IntTag*)(tag.getTag("int2").get());
    ASSERT_EQ(retrievedTag->value(), 2000);
}

TEST(ListTag, GetTagNotFound) {
    auto tag = nbt::ListTag("test", nbt::TAG_INT);
    auto intTag = std::make_shared<nbt::IntTag>("int1");
    intTag->setValue(1000);
    tag.children.push_back(intTag);

    auto retrievedTag = (nbt::IntTag*)(tag.getTag("int2").get());
    ASSERT_EQ(retrievedTag, nullptr);
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

TEST(FloatTag, GetTag) {
    auto tag = nbt::FloatTag("test");
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
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

TEST(ByteArrayTag, Type) {
    nbt::BaseTag* tag = new nbt::ByteArrayTag("test", {}, 0);
    ASSERT_EQ(nbt::TAG_BYTE_ARRAY, tag->type());
}

TEST(ByteArrayTag, Empty) {
    auto tag = nbt::ByteArrayTag("test", {}, 0);
    ASSERT_EQ(0, tag.size());
    ASSERT_EQ(0, tag.values().size());
}

TEST(ByteArrayTag, Value) {
    char array[] {1, 2, 3, 4, 5};
    auto tag = nbt::ByteArrayTag("test", array, 5);
    ASSERT_EQ(5, tag.size());
    ASSERT_EQ(5, tag.values().size());

    for (int i = 0; i < tag.values().size(); i++) {
        ASSERT_EQ(array[i], tag.values()[i]) << "Values differ at index " << i;
    }
}

TEST(ByteArrayTag, GetTag) {
    char array[] {1, 2, 3, 4, 5};
    auto tag = nbt::ByteArrayTag("test", array, 5);
    ASSERT_EQ(nullptr, tag.getTag("anything").get());
}

TEST(ByteArrayTag, ToString) {
    char array[] {1, 2, 3, 4, 5};
    auto tag = nbt::ByteArrayTag("test", array, 5);

    ASSERT_EQ("BYTE_ARRAY (test): [5]", tag.toString());
}

#pragma clang diagnostic pop