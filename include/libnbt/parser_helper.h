#include <istream>
#include <memory>

namespace nbt {
   namespace ParserHelper {
      template <typename T>
      T read(std::istream& is) {
         std::unique_ptr<char[]> valueBuffer(new char[sizeof(T)]);
         T result;
         is.read(valueBuffer.get(), sizeof(T));
         std::copy(reinterpret_cast<const char*>(&valueBuffer[0]),
                  reinterpret_cast<const char*>(&valueBuffer[sizeof(T)]),
                  reinterpret_cast<char*>(&result));
         return result;
      };

      template <>
      std::string read(std::istream& is) {
         short nameLength;
         std::string name;
         is.read(reinterpret_cast<char*>(&nameLength), 2);
         if (nameLength > 0) {
            std::unique_ptr<char[]> nameBuffer(new char[nameLength]);
            is.read(nameBuffer.get(), nameLength);
            return name.assign(nameBuffer.get(), nameLength);
         }
         return name;
      }

      template <typename T, class U>
      std::shared_ptr<U> readTag(std::istream& is, std::string name) {
         T value = read<T>(is);
         std::shared_ptr<U> tag = std::make_shared<U>(name);
         tag->setValue(value);
         return tag;
      }
   }
}
