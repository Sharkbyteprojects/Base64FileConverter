#include "runningBaseCodec.hpp"
#include <exception>

#define base64mask 0b111111U
#define Charidx (base64mask + 1)
const uint8_t tableOfContents[Charidx] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};


class stringModules {
private:
	std::string worker;
	char n[2]{ 0, 0 };
public:
	stringModules(std::string wo = "") :worker(wo) {}
	void append(uint8_t cha) {
		n[0] = static_cast<char>(cha);
		worker += n;
	}
	void finishBase64StringCorrecture() {
		for (char i = 0; i < worker.length() % 4; i++){
			append('=');
		}
	}
	std::string returnStr() {
		return worker;
	}
};

#define selectorValueCalculation(xn) (16U - 6U) - (xn)

std::string base64Codec::encodeByteBlock(const uint8_t* block, size_t len)
{
	uint8_t encodeWalking[2]{ 0,0 }; uint16_t walcD = 0;

	stringModules outputMani;

	uint8_t processedPart = 0,
		tmp_value = 0;
	size_t tmp_shiftValue = 0;

	size_t lenBased = binToBase_Size(len);

	bool tmp_cmpOK[2]{ 0, 0 };
	for (size_t i = 0, bitCounter = 0; i < lenBased; i++) {
		tmp_cmpOK[0] = (bitCounter < len);
		tmp_cmpOK[1] = (bitCounter + 1 < len);
		if (!tmp_cmpOK[0] && !tmp_cmpOK[1]) {
			break;
		}

		encodeWalking[0] = tmp_cmpOK[0] ? block[bitCounter] : 0;
		encodeWalking[1] = tmp_cmpOK[1] ? block[bitCounter + 1] : 0;
		walcD = (((uint16_t)encodeWalking[0]) << 8) | encodeWalking[1];

		tmp_shiftValue = selectorValueCalculation(processedPart);
		tmp_value = (uint8_t)((walcD >> tmp_shiftValue) & base64mask);

		if (tmp_value > base64mask) // Should be impossible to apply
			throw - 2;

		outputMani.append(tableOfContents[tmp_value]);

		processedPart += 6;
		if (processedPart >= 8) {
			processedPart -= 8;
			bitCounter += 1;
		}
	}
	
	outputMani.finishBase64StringCorrecture();
	return outputMani.returnStr();
}

void base64Codec::decodeByteBlock(const uint8_t* block, size_t len, std::shared_ptr<uint8_t[]>& OUT_outputVal, size_t out_len, bool recountBase /* = false */)
{
   size_t localLen = len; //localLen replaces len
   if (recountBase) {
       localLen = 0;
       for (size_t i = 0; i < len; i++) {
           if (block[i] == '=') {
               localLen++;
               break;
           }
           for (uint8_t in = 0; in < Charidx; in++) {
               if (block[i] == tableOfContents[in]) {
                   localLen++;
                   break;
               }
           }
       }
   }

   size_t assumedmaxOutLen = base64Codec::estimate_baseToBin_Size(localLen);
   OUT_outputVal = std::shared_ptr<uint8_t[]>(new uint8_t[assumedmaxOutLen]);
   //TODO: decode
}

size_t base64Codec::estimate_baseToBin_Size(size_t size)
{
	if (size % 4 != 0)
		throw - 1;
	return (size / 4) * 3;
}

size_t base64Codec::binToBase_Size(size_t size)
{
	size_t snrDiv = size / 3;
	if (size % 3 != 0)
		snrDiv++;
	snrDiv *= 4;
	return snrDiv;
}
