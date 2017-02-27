#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "bigInt.h"

using namespace std;

class Encrypt{
public:
	Encrypt();
	vector<int> fromFile; //the message
	vector<int> decryptedMessage;
	vector<int> encryptedMessage;
	//set to 19 as the global rule -Tom we have it set to read in public key from inline parameters
	int pubKey; //Public key
	void read(string fileName);  //read from a file
	void encrypt(); //encryption with P and Q, print to standard out
	void decrypt(); //decrypt method, print to standard out
	void printDecMessage(vector<int> passedMessage);
	void printASCIIMessage(vector<int> passedMessage);
	void saveMessageToFile(vector<int> saveMessage);
	int priKey; //Private key we need to move this to private after testing
private:
	int p, q; // we need to set these here to our two three digit primes
	int modulus;
	int totient;
	int gcd(int a, int b);
};