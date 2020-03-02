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

      template <typename T, class U>
      std::shared_ptr<U> readTag(std::istream& is, std::string name) {
         T value = read<T>(is);
         std::shared_ptr<U> tag = std::make_shared<U>(name);
         tag->setValue(value);
         return tag;
      }
   }
}
