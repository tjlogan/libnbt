#ifndef BASE_TAG_H
#define BASE_TAG_H

#include <memory>

namespace nbt {
   enum TagType {
      TAG_END = 0x00,
      TAG_BYTE = 0x01,
      TAG_SHORT = 0x02,
      TAG_INT = 0x03,
      TAG_LONG = 0x04,
      TAG_FLOAT = 0x05,
      TAG_BYTE_ARRAY = 0x07,
      TAG_STRING = 0x08,
      TAG_LIST = 0x09,
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
         // Given a name, returns a shared pointer to the first tag found with a matching name.
         // Returns a shared null pointer if the name was not found.
         virtual std::shared_ptr<BaseTag> getTag(std::string name);
         // Given a name, returns the a pointer to the first tag found with a matching name as the type T.
         // Returns nullptr if the name was not found or it wasn't able to cast to type T.
         template <typename T>
         T* getTag(std::string name);
         virtual std::string toString() = 0;
   };

   template <typename T>
   T* BaseTag::getTag(std::string name) {
      return dynamic_cast<T*>(this->getTag(name).get());
   }
}

#endif
