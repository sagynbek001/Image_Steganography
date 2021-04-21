#pragma once
//the cmath library is included
#include <cmath>

//the maximum size is defined as imageWidth*imageHeight*3/8
//because that number represents the maximum number of characters 
//the input bitmap image can hold

int decode(char*& secretMessageDecoded, unsigned char*** imageData, int imageWidth, int imageHeight) {
	const int sizeMax = (int)imageWidth * imageHeight * 3 / 8;
	//the temporary char array is created dynamically
	char* temp;
	temp = new char[sizeMax];
	//the temp array is filled with 0s 
	for (int i = 0; i < sizeMax; i++) {
		temp[i] = '\0';
	}
	//needed variable are declared and initialized
	int secretMessageSize = 0;
	int bit = 0;
	bool flag = false;
	for (int row = 0; row < imageHeight; row++)
	{
		for (int col = 0; col < imageWidth; col++)
		{
			for (int channel = 0; channel < 3; channel++)
			{
				//each of the first bytes of the image undergo the following process
				//if the LSB of the byte representing the depth of the color (r,g,b) is 1 
				//the current bit of the current character of the secret message is set to 1
				//to do this the bitwise operator OR is used along with the power of 2
				if (imageData[row][col][channel] & 1) temp[secretMessageSize] |= (int)pow(2, bit);
				//bit is incremented
				bit++;
				//if bit is 8, it means that one character has been decoded
				//the bit is set to 0 and the secretMessageSize is incremented
				if (bit == 8) { bit = 0; secretMessageSize++; }

				//when the character decoded is \0 or the image is analyzed entirely
				//the program exits all the loops
				if (secretMessageSize == sizeMax) { flag = true; }
				if (secretMessageSize > 0) {
					if (temp[secretMessageSize - 1] == 0) { flag = true; }
				}
				if (flag) break;
			}
			if (flag) break;
		}
		if (flag) break;
	}

	//the secretMessageDecoded new array with an acual message size
	//is created and the values stored in tem array are copy-pasted
	//to this new array
	secretMessageDecoded = new char[secretMessageSize];
	for (int i = 0; i < secretMessageSize; i++) {
		secretMessageDecoded[i] = temp[i];
	}

	//the temporary pointer is deallocated
	delete[] temp;

	return secretMessageSize;
}