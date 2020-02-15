#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cerrno>

#pragma pack(push, 1) 
struct Header {
   int version;
   int size;
};
#pragma pack(pop)

enum TagType {
   TAG_END = 0x00,
   TAG_BYTE = 0x01,
   TAG_INT = 0x03,
   TAG_STRING = 0x08,
   TAG_COMPOUND = 0x0A
};

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
   int int4 = 0;
   while(!fin.eof()) {
      char tagType;
      fin.read(&tagType, 1);

      short nameLength;
      short stringLength;
      std::string str;
      switch (tagType) {
         case TAG_COMPOUND:
            std::cout << "TAG COMPOUND\n";
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            std::cout << "Name Length: " << nameLength << "\n";
            if (nameLength > 0) {
               std::cout << "I can't handle this right now\n";
               return 3;
            }
            break;
         case TAG_BYTE:
            std::cout << "TAG BYTE\n";
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            std::cout << "Name Length: " << nameLength << "\n";
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
               std::cout << "Name: " << str << "\n";
            }
            char value;
            fin.read(&value, 1);
            std::cout << "Value: 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (unsigned int)value) << std::dec << "\n";
            break;
         case TAG_INT:
            std::cout << "TAG INT\n";
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            std::cout << "Name Length: " << nameLength << "\n";
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
               std::cout << "Name: " << str << "\n";
            }
            fin.read(valueBuffer, 4);
            int4 = 0;
            int4 = valueBuffer[3];
            int4 = (int4 << 8) + valueBuffer[2];
            int4 = (int4 << 8) + valueBuffer[1];
            int4 = (int4 << 8) + valueBuffer[0];
            std::cout << "Value: " << int4 << "\n";
            break;
         case TAG_STRING:
            std::cout << "TAG STRING\n";
            fin.read(reinterpret_cast<char*>(&nameLength), 2);
            std::cout << "Name Length: " << nameLength << "\n";
            if (nameLength > 0) {
               char* nameBuffer = new char[nameLength];
               fin.read(nameBuffer, nameLength);
               str.assign(nameBuffer, nameLength);
               std::cout << "Name: " << str << "\n";
            }
            fin.read(reinterpret_cast<char*>(&stringLength), 2);
            std::cout << "Name Length: " << stringLength << "\n";
            if (stringLength > 0) {
               char* stringBuffer = new char[stringLength];
               fin.read(stringBuffer, stringLength);
               str.assign(stringBuffer, stringLength);
               std::cout << "String: " << str << "\n";
            }
            break;

         default:
            std::cout << "UNKNOWN TAG 0x" << std::setfill('0') << std::setw(2) << std::hex << (0xFF & (unsigned int)tagType) << std::dec << "\n";
            return 2;
            break;
      }
   }
   
   fin.close();
   return 0;
}