#include "crypt.h"

Encrypt::Encrypt(void) {
	//the key information is created here when the class is constructed
	vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };
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
	int i,j;
	for(i=0;i<primes.size();i++)
	{
		if((primes[i]*pubKey % totient) == 1)//the key is a potential private key
		{
			for (j=0; j < fromFile.size(); j++) 
			{
				calc = (int) pow((double) fromFile[i], (double) primes[i]);
				calc = calc % modulus;
				if( (calc <= 'z' && calc >='a') || calc == ' ')//still a valid message
				{
					decryptedMessage.push_back(calc);
				}
				else//it isnt a message;
				{
					decryptedMessage.resize(0);
					break;
				}
			}
			if(decryptedMessage.size() != 0)
			{
				for (j=0; j < decryptedMessage.size(); j++)
				{printf("%c",decryptedMessage[j]);}
				printf("\n");
			}
		}
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
