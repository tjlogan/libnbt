#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cerrno>
#include "libnbt/parser/tag/tag.h"
#include "libnbt/parser/parser.h"

#pragma pack(push, 1) 
struct Header {
   int version;
   int size;
};
#pragma pack(pop)

int main() {
   std::ifstream fin;
   fin.open("level.dat", std::ios::in | std::ios::binary);

   if (!fin.is_open()) {
      std::cerr << "Error: " << std::strerror(errno) << "\n";
      return 1;
   }

   char* buffer = new char[8];
   fin.read(buffer, 8);
   struct Header* header = (Header*)buffer;

   nbt::Parser parser = nbt::Parser(fin);
   std::cout << "Version: " << header->version << "\n";
   std::cout << "NBT Size: " << header->size << "\n";
   auto result = parser.parse();
   std::cout << result.size() << " tags\n";
   std::cout << result[0]->toString() << "\n";
   
   fin.close();
   return 0;
}