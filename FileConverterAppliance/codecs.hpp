#ifndef AOE_COD
#include <stdint.h>

class coder {
	virtual uint16_t encodeByteBlock(uint16_t);
	virtual uint16_t decodeByteBlock(uint16_t);
};

#define AOE_COD
#endif
