#include "crypt.h"

Encrypt::Encrypt(void) {
	//the key information is created here when the class is constructed

	//switch p and q to some random large prime
	//using 5 and 11 for testing right now
	p = 5;
	q = 11;
	modulus = p*q;
	totient = (p - 1)*(q - 1);
	// the pvt key isnt working
	priKey = gcd(pubKey, totient);
}

int Encrypt::gcd(int a, int b){
	//ive seen several different versions of this
	//code online but we are not getting the correct
	//private key from it
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

void Encrypt::read(string fileName) {
	//this function reads in a file 
	//and saves the numbers to a vector 
	//called fromFile
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
		//strip out commas
		while (getline(ss, pass, ',')) {
			fromFile.push_back(stoi(pass));
		}
	}
}

void Encrypt::encrypt() {
	//this function encrypts the message and saves it to encryptedMessage
	//this is the form m^e mod n as shown in the notes
	unsigned long long int calc = 0;
	for (int i = 0; i < fromFile.size(); ++i) {
		//m^e
		calc = pow(fromFile[i], pubKey);
		//mod n
		encryptedMessage.push_back(calc % modulus);
	}

}

void Encrypt::decrypt() {
	//this function encrypts the message and saves it to decryptedMessage
	//this is the form c^d mod n as shown in the notes
	unsigned long long int calc = 0;
	for (int i = 0; i < fromFile.size(); ++i) {
		//c^d
		calc = pow(fromFile[i], priKey);
		//mod n
		decryptedMessage.push_back(calc % modulus);
	}

}

void Encrypt::printDecMessage(vector<int> passedMessage) {
	//this prints the decmial numnbers of a message
	//with spaces in between
	//just pass it the message vector to save
	for (int i = 0; i < passedMessage.size(); ++i)
		cout << passedMessage[i] << " ";
	cout << endl;
}

void Encrypt::printASCIIMessage(vector<int> passedMessage) {
	//this prints the ASCII numnbers of a message
	//all in one line since spaces are apart of the message
	//just pass it the message vector to save
	for (int i = 0; i < passedMessage.size(); ++i)
		cout << (char)passedMessage[i];
	cout << endl;
}

void Encrypt::saveMessageToFile(vector<int> saveMessage) {
	//this function saves a string of ints to a file
	//just pass it the message vector to save
	ofstream out;
	string filename;

	do {
		cout << "What file would you like to save to?" << endl;
		getline(cin, filename);
		out.open(filename.c_str());
	} while (!out.is_open());

	for (int i = 0; i < saveMessage.size(); ++i) {
		if (i == saveMessage.size() - 1)
			//dont put a comma after the last item
			out << saveMessage[i];
		else
			out << saveMessage[i] << ",";
	}
	out.close();
}