#include <cstdio>
#include <iostream>
#include <string>
#include "crypt.h"


/*
ITEMS LEFT TO FINISH

******Item #1******************************
	The private key is not working as an example
	p = 5
	q = 11
	Private key = 7
	The public key should be 23
	http://www.muppetlabs.com/~breadbox/txt/rsa.html
	However the private key using these numbers is coming out 40
	It def in the gcd function but Im not sure where.

******Item #2******************************
	After the private key is working we need to pick 2 primes and
	assign them to p and q in the crypt.cpp file. There is a list below.

******Item #3******************************
	We need a message and then encrypt it.
	The encrypt function is working so this is not a real issue.

******Item #4******************************
	The largest item left is to decrypt the other groups message. There are some ideas here
	http://www.muppetlabs.com/~breadbox/txt/rsa.html
	https://0day.work/how-i-recovered-your-private-key-or-why-small-keys-are-bad/
	We already have all of the primes up to three digits listed in a vector below
	and there arnt that many.
	Some thoughts I was having about this
	We can brute force every combination and see if the message has any of the below and throw them away:
		no vowels
		three consonants in a row
		puncation
		captial letters
	After this we could display the messages left one by one and the pvt key with each message
*/



using namespace std;

int main(int argc, char** argv)
{
	//list of all three digit primes
	vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };

	//note that the public key is not set and based on an email from the 
	//professor we should likely choose a larger public key like 19 or more
	if (argc < 4)  // take your filename.csv, action and public key
	{
		cout << "Useage:encryption filename E|D K" << endl;
		cout << "filename: This is a comma delimited file with the message in integers" << endl;
		cout << "E: Action to be performed:" << endl;
		cout << "	E - This will encrypt the file" << endl;
		cout << "	D - This will decrypt the file" << endl;
		cout << "K: Public key to be entered" << endl;
		exit(0);
	}
	//filename and action to be done
	char Action;
	string fileName;

	Action = *argv[2];
	fileName = argv[1];

	Encrypt E; //create class
	E.pubKey= atoi(argv[3]); //get the parameter to encrypt or decrypt
	E.read(fileName);  //read the CSV file
	cout << "Private key for testing " << E.priKey << endl;
	cout << "Public key for testing " << E.pubKey << endl;
	

	if (Action == 'E') {
		cout << "Encrypting the following message..." << endl;
		E.printASCIIMessage(E.fromFile); //print readable message
		E.encrypt();  //encrpyt the message
		cout << "From: ";
		E.printDecMessage(E.fromFile);//print int message
		cout << "To: ";
		E.printDecMessage(E.encryptedMessage);//print encrypted int message
		E.saveMessageToFile(E.encryptedMessage);//save message to file
	}
	if (Action =='D') {
		cout << "Decrypting the following code..." << endl;
		cout << "From: ";
		E.printDecMessage(E.fromFile);//print encrypted int message
		E.decrypt();  //decrypt the message
		cout << "To: ";
		E.printDecMessage(E.decryptedMessage);//print newly decrypted message
		cout << "The message is : ";
		E.printASCIIMessage(E.decryptedMessage);//print readable message
	}
}