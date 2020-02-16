#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cerrno>
#include "tag/byte_tag.h"
#include "tag/int_tag.h"
#include "tag/compound_tag.h"
#include "tag/string_tag.h"
#include "tag/long_tag.h"

#pragma pack(push, 1) 
struct Header {
   int version;
   int size;
};
#pragma pack(pop)

int main() {
   std::ifstream fin;
   char* buffer = new char[8];
   fin.open("level.dat", std::ios::in | std::ios::binary);

   if (!fin.is_open()) {
      std::cerr << "Error: " << std::strerror(errno) << "\n";
      return 1;
   }

   fin.read(buffer, 8);
   struct Header* header = (Header*)buffer;
   char* valueBuffer = new char[4];
   while(!fin.eof()) {
      char tagType;
      fin.read(&tagType, 1);

      short nameLength;
      short stringLength;
      std::string str;
      str.assign("");
      switch (tagType) {
         case TAG_COMPOUND: {
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
            }
            CompoundTag tag = CompoundTag(str);
            std::cout << tag.toString() << "\n";
            break;
         }
         case TAG_BYTE: {
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
            }
            ByteTag byteTag = ByteTag(str);
            char value;
            fin.read(&value, 1);
            byteTag.setValue(value);
            std::cout << byteTag.toString() << "\n";
            break;
         }
         case TAG_INT: {
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
            }
            fin.read(valueBuffer, 4);
            int int4 = 0;
            int4 = valueBuffer[3];
            int4 = (int4 << 8) + valueBuffer[2];
            int4 = (int4 << 8) + valueBuffer[1];
            int4 = (int4 << 8) + valueBuffer[0];
            IntTag intTag = IntTag(str);
            intTag.setValue(int4);
            std::cout << intTag.toString() << "\n";
            break;
         }
         case TAG_STRING: {
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
            }
            std::string strValue;
            fin.read(reinterpret_cast<char*>(&stringLength), 2);
            if (stringLength > 0) {
               char* stringBuffer = new char[stringLength];
               fin.read(stringBuffer, stringLength);
               strValue.assign(stringBuffer, stringLength);
            }
            StringTag strTag = StringTag(str);
            strTag.setValue(strValue);
            std::cout << strTag.toString() << "\n";
            break;
         }
         case TAG_LONG: {
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
            }
            fin.read(valueBuffer, 8);
            long int8 = 0;
            int8 = valueBuffer[7];
            int8 = (int8 << 8) + valueBuffer[6];
            int8 = (int8 << 8) + valueBuffer[5];
            int8 = (int8 << 8) + valueBuffer[4];
            int8 = (int8 << 8) + valueBuffer[3];
            int8 = (int8 << 8) + valueBuffer[2];
            int8 = (int8 << 8) + valueBuffer[1];
            int8 = (int8 << 8) + valueBuffer[0];
            LongTag longTag = LongTag(str);
            longTag.setValue(int8);
            std::cout << longTag.toString() << "\n";
            break;
         }
         case TAG_END: {
            std::cout << "END\n";
            break;
         }
         default:
            std::cout << "UNKNOWN TAG 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (unsigned int)tagType) << std::dec << "\n";
            return 2;
            break;
      }
   }
   
   fin.close();
   return 0;
}