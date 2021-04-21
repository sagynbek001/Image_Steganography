//**************************************************************//
//** Author: Muhammad Hassan Jamil                             **//
//** Date Created: August 22, 2020                            **//
//** A helper header file to read and write 24 bit Bitmap     **//
//** image files and load them into 3 channels R, G and B (2D)**//
//** arrays. Header also has a utility function to free up    **//
//** memory from R,G,B arrays                                 **//
//** For more information on Bitmap headers and file format   **//
//** visit Wiki page                                          **//         
//** https://en.wikipedia.org/wiki/BMP_file_format            **//
//**************************************************************//

#pragma pack(push, 2) //pack struct members to 2 bytes alignment
#include <fstream>

using namespace std;

class BMPFILEHEADER {
public:
	uint16_t bmpFileH_Type;       // signature (file type)
	uint32_t bmpFileH_Size;       // image file size in bytes
	uint16_t bmpFileH_Reserved1;  // reserved
	uint16_t bmpFileH_Reserved2;  // reserved
	uint32_t bmpFileH_DataOffset; // start of pixel array
};

class BMPINFOHEADER {
public:
	uint32_t bmpInfo_Size;         // header size
	uint32_t bmpInfo_Width;        // image width
	uint32_t bmpInfo_Height;       // image height
	uint16_t bmpInfo_Planes;       // number of color plane
	uint16_t bmpInfo_BitsPerPixel; // bits per pixel
	uint32_t bmpInfo_Compression;  // compression
	uint32_t bmpInfo_ImageSize;    // image size
	uint32_t bmpInfo_HPxlPerMeter; // horizontal resolution
	uint32_t bmpInfo_YPxlPerMeter; // vertical resolution
	uint32_t bmpInfo_ClrUsed;      // colors in color table
	uint32_t bmpInfo_ClrImportant; // important color count
};

BMPFILEHEADER bitmapFileHeader;
BMPINFOHEADER bitmapInfoHeader;

const int BYTES_PER_PIXEL = 3; /// red, green, & blue

bool ReadBitmapImage(const char* fileName, unsigned char***& imageData, int& imageWidth, int& imageHeight) {

	ifstream imageFile;
	//open file in binary mode
	imageFile.open(fileName, ios::in | ios::binary);

	if (!imageFile.fail()) {

		//read bmp file header
		imageFile.read((char*)&bitmapFileHeader, sizeof(BMPFILEHEADER));
		uint32_t fileType = bitmapFileHeader.bmpFileH_Type & 0xFFFF;
		//0x4d42 is assigned to bitmap image file
		if (fileType != 0x4d42) {
			std::cerr << "The file is not a Bitmap image file" << endl;
			return false;
		}

		//read bmp info header
		imageFile.read((char*)&bitmapInfoHeader, sizeof(BMPINFOHEADER));

		uint16_t bitsPerPixel = bitmapInfoHeader.bmpInfo_BitsPerPixel & 0xFF;
		//Check bits per pixel
		if (bitsPerPixel != 24) {
			cerr << "Bitmap is not a 24 bit image" << endl;
			return false;
		}

		imageWidth = bitmapInfoHeader.bmpInfo_Width;
		imageHeight = bitmapInfoHeader.bmpInfo_Height;

		//Dynamically allocate memory for image data
		imageData = new unsigned char** [imageHeight];
		for (int row = 0; row < imageHeight; row++)
		{
			imageData[row] = new unsigned char* [imageWidth];
			for (int col = 0; col < imageWidth; col++)
			{
				imageData[row][col] = new unsigned char[3];
			}
		}

		//get data offset from header
		uint32_t offset = bitmapFileHeader.bmpFileH_DataOffset;

		//seek pointer to data offset
		imageFile.seekg(offset, imageFile.beg);

		int padding = 0;
		int paddingLength = 0;

		//Check if we need to read padding as well
		if (imageWidth % 4 != 0) {
			uint32_t rowLength = imageWidth * BYTES_PER_PIXEL;
			uint32_t requiredPadding = rowLength;
			while (requiredPadding % 4 != 0) {
				requiredPadding++;
			}
			paddingLength = (requiredPadding - rowLength);
		}

		for (int row = 0; row < imageHeight; row++)
		{
			for (int col = 0; col < imageWidth; col++)
			{
				//default order b,g,r
				for (int channel = 0; channel < 3; channel++)
				{
					imageFile.read((char*)&imageData[row][col][channel], sizeof(char));
				}
			}
			//if stride is not multiple of 4, take care of padding
			if (imageWidth % 4 != 0) {
				//read and discard padding
				imageFile.read((char*)&padding, paddingLength);
			}
		}
		imageFile.close();
		return true;
	}
	else {
		std::cout << "Failed to open the Image file" << endl;
		return false;
	}
	return false;
}

bool WriteBitmapImage(const char* fileName, unsigned char*** imageData, int imageWidth, int imageHeight) {

	unsigned char padding[3] = { 0, 0, 0 };
	//row length should be multiple of 4
	int paddingSize = (4 - (imageWidth * BYTES_PER_PIXEL) % 4) % 4;

	//open file in binary mode
	ofstream imageFile(fileName, ios::out | ios::binary);

	if (!imageFile.fail()) {
		//Write headers into the bitmap
		imageFile.write((char*)&bitmapFileHeader, sizeof(BMPFILEHEADER));
		imageFile.write((char*)&bitmapInfoHeader, sizeof(BMPINFOHEADER));

		for (int row = 0; row < imageHeight; row++)
		{
			for (int col = 0; col < imageWidth; col++) {
				for (int channel = 0; channel < 3; channel++)
				{
					imageFile.write((char*)&imageData[row][col][channel], sizeof(char));
				}
			}
			//write padding
			imageFile.write((char*)padding, paddingSize);
		}
		imageFile.close();
		return true;
	}
	std::cout << "Bitmap fail to write to disk" << endl;
	return false;
}

//Release image data memory allocated dynamically
// TO BE COMPLETED
void ReleaseMemory(unsigned char*** imageData, int imageHeight, int imageWidth) {
	
	for (int row = 0; row < imageHeight; row++)
	{
		for (int col = 0; col < imageWidth; col++)
		{
			//memory used by the content pointed by each of 
			//the imageData[row][col] is deallocated
			delete[] imageData[row][col];
		}
		//memory used by the content pointed by each of 
		//the imageData[row] is deallocated
		delete[] imageData[row];
	}	
	//memory used by the content pointed by each of 
	//the imageData is deallocated
	delete[] imageData;

}

#pragma pack(pop)
