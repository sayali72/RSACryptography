// File name: RSA.cpp, CSCI 6600, Due date - 07/02/2019
// Name: Sayali Borase
// 
// Description: Main function
//

#include <iostream>
#include "rsacrypto.h"
using namespace std;

int main()
{
	int option;
	RSACrypto R;

	do
	{
		cout << endl;
		cout << "*************RSA Application*************" << endl << endl;
		cout << "Select one option: " << endl;
		cout << "1: Generate keys" << endl;
		cout << "2: Encrypt" << endl;
		cout << "3: Decrypt" << endl;
		cout << "4: Exit " << endl << endl;

		cin >> option; 
		cout << "Option selected: " << option << endl << endl;
 		cin.ignore();

		switch (option)
		{
		// function call to generate private and public keys
		case 1: R.KeyGeneration();           break;
		case 2: R.encryptPlaintext();        break;
		case 3: R.decryptCiphertext();       break;
		case 4: exit(0);					 break;
		default: cout << "Invalid option.";   break;
		}
	} while (option != 4);
	
	return 0;
}
