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
	int pubKey; //Public key. This is set from the command line
	void read(string fileName);  //read from a file
	void encrypt(); //encryption method
	void decrypt(); //decrypt method
	void printDecMessage(vector<int> passedMessage); //print the message in ints
	void printASCIIMessage(vector<int> passedMessage); //print the string message
	void saveMessageToFile(vector<int> saveMessage);//save the message to a file in ints
	int priKey; //Private key we need to move this to private after testing 
	//i have the pvt key here so i can print it to the command line for testing atm
private:
	//all of these are set in the constructor
	int p, q; 
	int modulus;
	int totient;
	int gcd(int a, int b);
};