#include <stdint.h>
#include <string>

namespace base64Codec  {
	std::string encodeByteBlock(const uint8_t* block, size_t len); // can throw a error on code corruption
	void decodeByteBlock(const uint8_t * block, size_t len, uint8_t* OUT_outputVal, size_t out_len, bool recountBase = false); //Wants a previously allocated and nulled array as outputVal
	size_t estimate_baseToBin_Size(size_t); // throws -1
	size_t binToBase_Size(size_t);
};
