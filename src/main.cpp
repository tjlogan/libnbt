#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <cerrno>
#include "tag/tag.h"
#include "parser/parser.h"

int main() {
   std::ifstream fin;
   fin.open("level.dat", std::ios::in | std::ios::binary);

   if (!fin.is_open()) {
      std::cerr << "Error: " << std::strerror(errno) << "\n";
      return 1;
   }

   nbt::Parser parser = nbt::Parser(fin);
   std::cout << "Version: " << parser.version() << "\n";
   std::cout << "NBT Size: " << parser.size() << "\n";
   auto result = parser.parse();
   std::cout << result.size() << " tags\n";
   std::cout << result[0]->toString() << "\n";
   
   fin.close();
   return 0;
}