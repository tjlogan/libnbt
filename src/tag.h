#include <vector>
#include <memory>

enum TagType {
   TAG_END = 0x00,
   TAG_BYTE = 0x01,
   TAG_INT = 0x03,
   TAG_STRING = 0x08,
   TAG_COMPOUND = 0x0A
};
 
class BaseTag {
   private:
      std::string m_name;
      TagType m_type;

   protected:
      BaseTag(std::string name, TagType type);

   public:
      std::string name();
      TagType type();
};

class ByteTag : public BaseTag {
   private:
      char m_value;
   
   public:
      ByteTag(std::string name);
      char value();
      void setValue(char value);
};

class IntTag : public BaseTag {
   private:
      int m_value;
   
   public:
      IntTag(std::string name);
      int value();
      void setValue(int value);
};

class StringTag : public BaseTag {
   private:
      std::string m_value;
   
   public:
      StringTag(std::string name);
      std::string value();
};

class CompoundTag : public BaseTag {
   private:
      std::vector<BaseTag> m_value;
   
   public:
      CompoundTag(std::string name);
      void add(BaseTag tag);
      std::vector<BaseTag> value();
};
