// File name: rsacrypto.cpp, CSCI 6600, Due date - 07/02/2019
// Sayali Borase
// 
// Description: The program using RSA Cryptography algorithm
// generates private key public key pair to perform encryption
// and decryption of given input text
//
// Input: Input text in plaintext.txt file
// Output: Public key (d, n) and private key (e, n)
//         Encrypted plaintext (ciphertext)
//         Decrypted ciphertext (original plaintext)


#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <fstream>
#include "rsacrypto.h"
using namespace std;

// default constructor
RSACrypto::RSACrypto()
{
}

// Check if a no. is prime
bool RSACrypto::isPrime(ull_int num)
{
	for (ull_int a = 2; a < num; a++) 
	{
		if (num % a == 0) 
		{
			return false;
		}
	}
	return true;
}

// compute and returns a GCD of two no's.
ull_int RSACrypto::findGCD(ull_int a, ull_int b)
{
	ull_int r1, r2, r;
	int q;
	if (a > b)
	{
		r1 = a;
		r2 = b;
	}
	else
	{
		r1 = b;
		r2 = a;
	}
	while (r2 > 0)
	{
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;
	}
	return r1;
}

// returns modular multiplicative inverse of a no.
ull_int RSACrypto::findModInverse(ull_int a, ull_int b)
{
	a = a % b;
	for (ull_int i = 1; i < b; i++)
	{
		if ((a * i) % b == 1 && i != a)
			return i;
	}
	return 0;
}

// find FastExponention 
ull_int RSACrypto::findT(ull_int a, ull_int m, ull_int n)
{
	ull_int r;
	ull_int y = 1;

	while (m > 0) 
	{
		r = m % 2;
		FastExponention(r, n, &y, &a);
		m = m / 2;
	}
	return y;
}

// to speed up fast exponention calculation
void RSACrypto::FastExponention(ull_int bit, ull_int n, ull_int* y, ull_int* a)
{
	if (bit == 1)
		*y = (*y * (*a)) % n;
	
	*a = (*a) * (*a) % n;
}

// display plaintext and corresponding ciphertext
void RSACrypto::displayEncryptedText()
{
	string text;
	ifstream inFile1, inFile2;
	ull_int value;
	
	inFile1.open("plaintext.txt", ios::in);
	inFile2.open("ciphertext.txt", ios::in);
	
	cout << "Plaintext is: ";
	if(inFile1)
	{
		cout << inFile1.rdbuf();
	}
	cout << endl;
	
	cout << "Ciphertext is: ";
	if(inFile2)
	{
		while(inFile2 >> value)
			cout << value << " ";
	}
	cout << endl;
	
	inFile1.close();
	inFile2.close();
}

// display ciphertext and original recovered plaintext
void RSACrypto::displayDecryptedText()
{
	string text;
	ifstream inFile1, inFile2;
	
	inFile1.open("ciphertext.txt", ios::in);
	inFile2.open("decipher.txt", ios::in);
	
	cout << "Ciphertext is: ";
	if(inFile1)
	{
		ull_int value;
		while(inFile1 >> value)
			cout << value << " ";
	}
	cout << endl << endl;

	cout << "Original plaintext is: ";
	if(inFile2)
	{
		cout << inFile2.rdbuf();
	}
	
	cout << endl;
	
	inFile1.close();
	inFile2.close();
}

// generates a pair of private key and public key
void RSACrypto::KeyGeneration()
{
	int count = 0;
	ull_int arr[500];
	ull_int p, q, totient;      // p, q - prime nos., totient - Euler's Totient function
	int rand_i, rand_j;

	// find prime no's within a given range and store it in array
	for (ull_int currentNum = lower_limit; currentNum <= upper_limit; currentNum++)
	{
		if (isPrime(currentNum))
		{
			arr[count++] = currentNum;
		}
	}

	// random seed
	srand((unsigned int)time(NULL));

	// find random prime no's from an array
	rand_i = rand() % count;
	p = arr[rand_i];

	rand_j = 1 + rand() % (count - 2);
	q = arr[(rand_i + rand_j) % count];

	cout << "Randomly selected prime numbers are: " << p << " " << q << endl << endl;
	
	n = p * q;

	// find Euler's Totient value
	totient = (p - 1) * (q - 1);

	// choose random e such that it is relatively prime to totient
	// 1 < e < totient
	do
	{
		e = rand() % (totient - 2) + 2;
	} while (findGCD(e, totient) != 1);

	// find modular multiplicative inverse of e
	d = findModInverse(e, totient);

	cout << "Generated keys are: " << endl;
	cout << "Public key: " << "(" << e << ", " << n << ")" << endl;
	cout << "Private key: " << "(" << d << ", " << n << ")" << endl;
	
}

// function to encrypt given input text
void RSACrypto::encryptPlaintext()
{

	ifstream inFile;
	ofstream outFile;
	
	char ch;
	
	inFile.open("plaintext.txt", ios::in);
	outFile.open("ciphertext.txt", ios::out);
	
	if (!inFile)
	{
		cerr << "ERROR!" << endl;
		exit(1);
	}
	
	if (!outFile)
	{
		cerr << "ERROR!" << endl;
		exit(1);
	}

	// read plaintext, char by char and write encrypted char into file.
	while (inFile >> noskipws >> ch)
	{
		int value = toascii(ch);		
		int cipher = findT(value, e, n);
		outFile << cipher << " ";
	}
	
	inFile.close();
	outFile.close();
	
	displayEncryptedText();

}

// function to decrypt ciphertext to original plaintext
void RSACrypto::decryptCiphertext()
{

	ifstream inFile;
	ofstream outFile;
	
	ull_int value;
	
	inFile.open("ciphertext.txt", ios::in);
	outFile.open("decipher.txt", ios::out);
	
	if (!inFile)
	{
		cerr << "ERROR!" << endl;
		exit(1);
	}
	
	if (!outFile)
	{
		cerr << "ERROR!" << endl;
		exit(1);
	}
	
	// read ciphertext and write recovered plaintext into file.
	while(inFile >> value)
	{
		int decipher = findT(value, d, n);
		outFile << char(decipher);
	}
	
	inFile.close();
	outFile.close();

	displayDecryptedText();
}
