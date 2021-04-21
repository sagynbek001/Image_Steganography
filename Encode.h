#pragma once
bool encode(const char* secretMessageToEncode, int size, unsigned char***& imageData, int imageWidth, int imageHeight) {
	//the needed variables are declared and initialized
	int i = 0;
	int bit = 0;
	bool flag = false;
	for (int row = 0; row < imageHeight; row++)
		{
			for (int col = 0; col < imageWidth; col++)
			{
				for (int channel = 0; channel < 3; channel++)
				{
					//each of the first bytes of the image undergo the following process
					//if the current bit of the current character of the secret message is 1
					//and the LSB of the byte representing the depth of the color (r,g,b) is 0 
					//then the LSB of this byte is altered using the masking with OR 1 operation
					if ((secretMessageToEncode[i] >> bit) & 1) 
					{
						if ((int)imageData[row][col][channel] % 2 == 0) imageData[row][col][channel] |= 1;
						
					}
					//if the current bit of the current character of the secret message is 0
					//and the LSB of the byte representing the depth of the color (r,g,b) is 1
					//then the LSB of this byte is altered using the masking with & 254 operation
					else if ((int)imageData[row][col][channel] % 2 == 1)
					{
						imageData[row][col][channel] &= 254;
					}
					//incrementing bit by 1
					bit++;
					//if bit is 8, it means that one character has been encoded
					//the bit is set to 0 and the i
					//which represents the number of characters encoded is incremented
					if (bit == 8) { bit = 0; i++; }
					//if the i equals to size, it means that all the characters are
					//encoded and we need to exit the all loops
					//for that the flag is used
					if (i == size) flag = true;
					if (flag) break;
				}
				if (flag) break;
			}
			if (flag) break;
		}
	return flag;
}

	
