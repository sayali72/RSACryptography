	1. rsacrypto.h -- This file contains class declaration
	2. rsacrypto.cpp -- This file contains the implementation details
	3. RSA -- This file contains the main(). This file begins the program execution.
	4. makefile -- A utility to run and compile the program

This program makes use of switch case to allow user to select options as below:
	1. Generate keys
		Input: require no input
		Output: display random selected primary nos. (p and q) and display generated public key (e, n) and private key (d, n)

	2. Encryption
		Input: takes input text (to be encrypted) from file plaintext.txt
		Output: perform encryption and display ciphertext, also write to file ciphertext.txt

	3. Decryption
		Input: takes ciphertext from file ciphertext.txt
		Output: perform decryption and display original recovered plaintext, also write to file decipher.txt

	4. Exit
		Exit the program


Steps to build and run the program (on ranger):
		make //To compile the program
		RSA // To run the program (executable)
 


Note: Header file mention the range of numbers within which primary no. is selected.
      This range can be altered as per requirement. 
      Current settings generate minimum 16-bit length keys.
      Run the program multiple times to generate multiple unique keys.
      Recovered ciphertext does not contain spaces as that of original input text
