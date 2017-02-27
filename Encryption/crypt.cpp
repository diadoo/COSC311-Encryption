#include "crypt.h"

Encrypt::Encrypt(void) {
	//we need to create all of the key information when the class is constructed
	//using 3 and 7 for testing right now
	p = 5;
	q = 11;
	modulus = p*q;
	totient = (p - 1)*(q - 1);
	//we need code here to get the private key
	// the pvt key isnt working
	priKey = gcd(pubKey, totient);
}

// C function for extended Euclidean Algorithm
//http://www.geeksforgeeks.org/basic-and-extended-euclidean-algorithms/
int Encrypt::gcd(int a, int b){
	if (b == 0)
		return a;

	return gcd(b, a % b);
}

void Encrypt::read(string fileName) {
	ifstream csvFile;
	csvFile.open(fileName.c_str());

	//validate if the file exists
	while (!csvFile.is_open()) {
		cout << "Problem with file name. Please check that the file exists and re-enter file name: " << endl;
		getline(cin, fileName);
		csvFile.open(fileName.c_str());
	}

	string x;
	//read data into vector
	while (getline(csvFile, x)) {
		stringstream ss(x);
		string pass;
		while (getline(ss, pass, ',')) {
			fromFile.push_back(stoi(pass));
		}
	}
}

void Encrypt::encrypt() {
	unsigned long long int calc = 0;
	for (int i = 0; i < fromFile.size(); ++i) {
		calc = pow(fromFile[i], pubKey);
		encryptedMessage.push_back(calc % modulus);
	}

}

void Encrypt::decrypt() {
	unsigned long long int calc = 0;
	for (int i = 0; i < fromFile.size(); ++i) {
		calc = pow(fromFile[i], priKey);
		decryptedMessage.push_back(calc % modulus);
	}

}

void Encrypt::printDecMessage(vector<int> passedMessage) {
	for (int i = 0; i < passedMessage.size(); ++i)
		cout << passedMessage[i] << " ";
	cout << endl;
}

void Encrypt::printASCIIMessage(vector<int> passedMessage) {
	for (int i = 0; i < passedMessage.size(); ++i)
		cout << (char)passedMessage[i];
	cout << endl;
}

void Encrypt::saveMessageToFile(vector<int> saveMessage) {
	ofstream out;
	string filename;

	do {
		cout << "What file would you like to save to?" << endl;
		//cin.ignore();
		getline(cin, filename);
		out.open(filename.c_str());
	} while (!out.is_open());

	for (int i = 0; i < saveMessage.size(); ++i) {
		if (i == saveMessage.size() - 1)
			out << saveMessage[i];
		else
			out << saveMessage[i] << ",";
	}
	out.close();
}