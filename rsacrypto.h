// File name: rsacrypto.h, CSCI 6600, Due date - 07/02/2019
// Name: Sayali Borase
// 
// Description: This file contains RSACrypto class declaration
//

#ifndef RSACRYPTO_H
#define RSACRYPTO_H
using namespace std;

typedef unsigned long long int ull_int;

const ull_int lower_limit = 300; // range to randomly select primary no.
const ull_int upper_limit = 700;

class RSACrypto
{
public:
	// default constructor
	RSACrypto();
	void KeyGeneration();
	void encryptPlaintext();
	void decryptCiphertext();

private:
	// e - public key, d - private key
	ull_int e, d, n;
	
	bool isPrime(ull_int);
	ull_int findGCD(ull_int, ull_int);
	ull_int findModInverse(ull_int, ull_int);
	ull_int findT(ull_int, ull_int, ull_int);
	void FastExponention(ull_int, ull_int, ull_int*, ull_int*);
	void displayEncryptedText();    //display ciphertext
	void displayDecryptedText();    // display original plaintext
};
#endif
