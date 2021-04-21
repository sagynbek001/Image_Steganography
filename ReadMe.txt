The User’s Guide
1. To execute the program, the user needs to compile and run the code found in the file named Source.cpp
2. The user is prompted to choose among Encode, Decode, and Exit options by entering 1, 2 or -1 correspondingly. 
It is assumed that the user enters an integer. If none of the options are met the error message is displayed, and the menu is shown again.
• If the Encode option was selected, the user will be prompted to enter the name of the bitmap image. It is assumed that the image is 
stored in the project folder with the Source.cpp and has the exact same format of name as the next examples. Examples: “NYUAD.bmp”, “Earth.bmp”. 
Entering empty name is impossible. The extension .bmp, its existence, and its bit value (should be 24 bit) will be validated. In case validation 
fails, the corresponding message will be displayed, and the program will return to the main menu. If the validation succeeds, the program will 
display the corresponding message and the user will be prompted to enter the secret message to be encoded. It is assumed that the secret message 
is a single line and again, empty secret message is impossible. Lastly, after entering the secret message, the user will be asked to enter 
the name for the new encoded bitmap image. It is assumed that the name format is the same as of the examples above. The new encoded bitmap 
image will be created and saved.
• If the Decode option was selected, the user will be prompted to enter the name of the bitmap image. It is assumed that the image is 
stored in the project folder with the Source.cpp and has the exact same format of name as the next examples. Examples: “NYUAD.bmp”, “Earth.bmp”. 
The extension .bmp, its existence, and its bit value (should be 24 bit) will be validated. In case validation fails, the corresponding message 
will be displayed, and the program will return to the main menu. If the validation succeeds, the program will display the confirming message and 
the secret message will be decoded and displayed on the console.
• If the Exit option was selected, the program will be exited.
3. After the chosen analysis are completed the step 2 will be repeated until exit option is chosen.
Note: The maximum number of input characters is 10000000.