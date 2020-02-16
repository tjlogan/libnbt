#ifndef BASE_TAG
#define BASE_TAG 

enum TagType {
   TAG_END = 0x00,
   TAG_BYTE = 0x01,
   TAG_INT = 0x03,
   TAG_LONG = 0x04,
   TAG_STRING = 0x08,
   TAG_COMPOUND = 0x0A
};
 
class BaseTag {
   protected:
      BaseTag(std::string name, TagType type);
      std::string m_name;
      TagType m_type;

   public:
      std::string name();
      TagType type();
      virtual std::string toString() = 0;
};

#endif
