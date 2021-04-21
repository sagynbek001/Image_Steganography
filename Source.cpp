/*-------------------------------------------------------------------------*/
/* Name: Sagynbek Talgatuly Student Number: st4121                         */
/* Date: November 13. 2020                                                 */
/* Program: Source.cpp                                                     */
/* Description: This program encodes a secret message provided by the user */
/*				into the bitmap image using LSB steganography and decodes  */
/*				the secret message hidden in the bitmap image displaying   */
/*				it on the console.   									   */
/*-------------------------------------------------------------------------*/


//including all the needed libraries and header files
#include <iostream>
#include "BitmapHelper.h"
#include "Encode.h"
#include "Decode.h"

using namespace std;

//prototype for the ReadInputFunction, which will be used to 
//read the input from the user and store it in the char array dynamically
//this function will use pointer pointing to a char array as an argument
int ReadTheInput(char*& input); 

int main() {
	//declaring the necessary pointers and variables
	unsigned char*** imageData;
	int imageWidth, imageHeight;
	char* fileName;
	char* newFileName;
	char* secretMessageToEncode;
	char* secretMessageDecoded;

	//Introduction message for the user
	cout << "Dear User!												" << endl;
	cout << "Please, read the user's guide provided in the report	" << endl;
	cout << "Note:	Make sure that the bitmap images you will input " << endl;
	cout << "	passes the validation process and the names of 		" << endl; 
	cout << "	the bitmap images you will input have the same 		" << endl;
	cout << "	format as the examples in the user's guide.			" << endl << endl;

	int selection;
	do {
		cout << endl;
		//displaying the main menu
		cout << "Enter 1 to encode a BMP file" << endl;
		cout << "Enter 2 to decode a BMP file" << endl;
		cout << "Enter -1 to exit the program" << endl;

		//reading the choice of the user
		cin >> selection;
		//if the choice is 1 then the encoding process begins
		if (selection == 1) {
			//corresponding messages are shown
			cout << "You have selected to encode a BMP file" << endl;
			cout << "Please, enter the name of the BMP file to encode the secret message" << endl;
			cout << "Do not forget to include .bmp" << endl;
			//the filename is read using the reading function
			ReadTheInput(fileName);
			//the provided ReadBitmapImage is called and it's return value is assigned to variable OK
			bool ok = ReadBitmapImage(fileName, imageData, imageWidth, imageHeight);
			//if the validation has not succeeded then the error message is displayed and the program
			//returns to the main menu, otherwise it will continue the encoding process
			if (!ok) { cout << "Please, start the process again" << endl; continue; }
			//if validation is successful then the user is prompted to input the secret message
			cout << "The " << fileName << " was successfully read by the program" << endl;
			cout << "To proceed, please, enter your secret message that needs to be encoded" << endl;
			//the secret message is read by the reading function and its size is assigned to a variable
			//because it will be used in the next operations
			//the maximum size of the input is the following, because it represents the maximum number
			//of characters that the bitmap image provided can store
			int size = ReadTheInput(secretMessageToEncode);
			//the secret message is encoded into the bitmap image
			//the imageData is altered according to the secret message
			encode(secretMessageToEncode, size, imageData, imageWidth, imageHeight);
			cout << "Please, enter the name of the new encoded BMP file" << endl;
			cout << "Do not forget to include .bmp" << endl;
			//when the encoding process is completer, the program asks for the name
			//of the new encoded bitmap image to be saved
			//the name is stored in a dynamically allocated memory pointed by newFileName
			ReadTheInput(newFileName);
			//the new encoded BMP file is created and save using the provided function WriteBitmapImage
			WriteBitmapImage(newFileName, imageData, imageWidth, imageHeight);
			cout << "The new encoded BMP file was created and saved with a name " << newFileName << endl;
			//the memory allocated dynamically for the imageData, 
			//fileName, newFileName, and secretMessageToEncode is released
			ReleaseMemory(imageData, imageHeight, imageWidth);
			delete[] fileName;
			delete[] newFileName;
			delete[] secretMessageToEncode;
		}
		//if the choice is 2 then the decoding process begins
		else if (selection == 2) {
			//corresponding messages are shown
			cout << "You have selected to decode a BMP file" << endl;
			cout << "Please, enter the name of the BMP file to decode the secret message" << endl;
			cout << "Do not forget to include .bmp" << endl;
			//the filename is read using the reading function
			ReadTheInput(fileName);
			//the provided ReadBitmapImage is called and it's return value is assigned to variable OK
			bool ok = ReadBitmapImage(fileName, imageData, imageWidth, imageHeight);
			//if the validation has not succeeded then the error message is displayed and the program
			//returns to the main menu, otherwise it will continue the encoding process
			if (!ok) { cout << "Please, start the process again" << endl; continue; }
			//if the validation is successful then the program starts decoding the image
			//the received secret message is stored in the dynamically allocated memory
			//pointed by secretMessageDecoded
			cout << "The " << fileName << " was successfully read by the program" << endl;
			decode(secretMessageDecoded, imageData, imageWidth, imageHeight);
			//after the decoding process is completed, the secret message is displayed
			cout << "The secret message was decoded from " << fileName << " successfully" << endl;
			cout << "The secret message is:" << endl;
			cout << secretMessageDecoded << endl;
			//lastly, all the allocated memory is released
			ReleaseMemory(imageData, imageHeight, imageWidth);
			delete[] fileName;
			delete[] secretMessageDecoded;
		}
		//if the choice is -1 then the program is exited
		else if (selection == -1) break;
		//if none of the options are chosen, then the error message is displayed
		//and the user is prompted to choose again
		else cout << endl << "Invalid input, please, try again";
	} while (selection != -1);
	return 0;
}
//the below is the definition of the special read function
//this function is used to read the input character by character and to 
//save the input in the dynamically allocated char array
int ReadTheInput(char*& input) {
	//defining the maximum length og the secret message
    #define max 10000000
	//creating temporary char array dynamically with the provided maximum size
	char* temp;
	temp = new char[max];
	//the needed variables are declared and initialized
	char byte;
	int inputSize = 0;
	bool flag = false;
		//reading the character from the console and assigning it to the current
		//element of the temporary array
		//it is worth noting that the size of the input is also counted
		do {
			cin.get(byte);
			if (byte != '\n') { temp[inputSize] = byte; inputSize++; flag = true; }
		} while (!flag || byte != '\n');

		inputSize++;

		//the memory fot the input pointer is dynamically allocated with 
		//an actual size of the input 
		//the values stored in the temp is copy-pasted to the input array
		input = new char[inputSize];
		for (int i = 0; i < inputSize - 1; i++) {
			input[i] = temp[i];
		}
		input[inputSize - 1] = '\0';

		//when the input array is filled, the temporary array is simply deleted
		delete[] temp;

		return inputSize;
}

