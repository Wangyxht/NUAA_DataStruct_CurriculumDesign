#include "Bits8.h"

void bits_8::operator+=(unsigned short bit)
{
	if (bit == 0) {
		bits_ = bits_ << 1;
	}
	else if (bit == 1) {
		bits_ = bits_ << 1;
		bits_ += 1;
	}
	else {
		throw "Invalid!";
	}

}

bits_8& bits_8::operator<<(unsigned short bit)
{
	bits_ = bits_ << bit;
	return *this;
}

bits_8& bits_8::operator>>(unsigned short bit)
{
	bits_ = bits_ >> bit;
	return *this;
}

void bits_8::SetBit(unsigned short bit, unsigned short loc)
{
	if (bit == 0 || bit == 1) {
		bit = bit << loc;
		bits_ = bits_ | bit;
	}
	else {
		throw "Invalid!";
	}
}

void bits_8::Write(std::ofstream& fileOut)
{
	fileOut.write(reinterpret_cast<char*>(&bits_), sizeof(bits_));
	bits_ = 0;
}

void bits_8::Read(std::ifstream& fileIn)
{
	fileIn.read(reinterpret_cast<char*>(&bits_), sizeof(bits_));
}

unsigned short bits_8::GetLowBit()
{
	return 0x01 & bits_;
}

unsigned short bits_8::GetHighBit()
{
	unsigned int bit= 0x80 & bits_;
	bit = bit >> 7;

	return bit;
}
