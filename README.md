# libNbt

A library for reading data in the Minecraft Bedrock Named Binary Tag (NBT) format.  Go [here for more details](https://wiki.vg/NBT) on the NBT format.

## Install Gtest

This project makes use of Gtest and it must be installed in order to build.

`sudo apt-get install libgtest-dev`

## Building with CMake

From the project root, do:
```
cmake . -B build
cd build
make && test/runTests
```

### Unsupported Tags

This project in under development and some tags are still unsupported:

* TAG_Double
* TAG_Int_Array
* TAG_Long_Array
