#include <iostream>
#include "runningBaseCodec.hpp"

int main(int argc, char* argv[])
{
#define sizeString 13
    const char hw[sizeString] = "Hello World!";
    std::cout << hw << "\n";
    std::cout << base64Codec::encodeByteBlock((const uint8_t*)hw, sizeString - 1) << std::endl;
}

