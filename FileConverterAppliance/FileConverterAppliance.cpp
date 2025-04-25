#include <iostream>
#include "runningBaseCodec.hpp"

int main(int argc, char* argv[])
{
#define sizeString 13
    const char hw[sizeString] = "Hello World!";
    std::cout << hw << "\n";
    std::cout << base64Codec::encodeByteBlock((const uint8_t*)hw, sizeString - 1) << "\n" << std::endl;

    for (uint16_t i = 1; i < argc; i++) {
        std::cout << "\"" << argv[i] << "\" : \"" << base64Codec::encodeByteBlock((const uint8_t*)argv[i], strlen(argv[i])) << "\"\n";
    }
}

