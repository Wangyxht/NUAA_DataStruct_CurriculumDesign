#ifndef BITS_16_H_
#define BITS_16_H_

#include<iostream>
#include<fstream>
 
class bits_8 {
private:
	unsigned char bits_ = 0;
public:
	void operator+=(unsigned short bit);
	bits_8& operator<<(unsigned short bit);
	bits_8& operator>>(unsigned short bit);
	void SetBit(unsigned short bit, unsigned short loc);
	void Write(std::ofstream& fileOut);
	void Read(std::ifstream& fileIn);
	unsigned short GetLowBit();
	unsigned short GetHighBit();
	
};


#endif