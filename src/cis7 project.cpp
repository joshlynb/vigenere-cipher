

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;


class vigenereCipher {

	public: 

		void setMessage(string msg)
		{
			this->message = msg;
		}

		string getMessage()
		{
			return message;
		}

		void setKeyword(string keyword)
		{
				this->key = keyword;
			
		}

		string getKeyword()
		{
			return key;
		}

		string transformMessage()
		{
			//Removes all elements from the string that are not alphabetical characters
			message.erase(remove_if(begin(message), end(message), 
				[](unsigned char c) {
					return not isalpha(c);}), end(message));

			//Transforms all lowercase letters to uppercase
			if (any_of(message.begin(), message.end(), ::islower))
				transform(message.begin(), message.end(), message.begin(), ::toupper);

			return message;
		}


		
		string generateKey()
		{

			int count = 0; //iterator to count keyword element
			string k; //transformed key
			string msg = transformMessage(); 
			int messageSize = transformMessage().size();

			//Transform lowercase letters of keyword to uppercase
			if (any_of(key.begin(), key.end(), ::islower))
				transform(key.begin(), key.end(), key.begin(), ::toupper);

			//If key length is less or equal to message length, add keyword onto the key until key length is equal to message length
				if (k.size() <= messageSize) {
					for (int i = 0; k.size() < messageSize; i++) {

						if (count < key.size()) {
							k.push_back(key[count]);
							count++;
						}
						else
							count = 0;
					}

				}

			//If key length is greater than message length, erase the last letter of the key until key length is equal to message length
			if (key.size() > messageSize) {
				for (int i = 0; messageSize < k.size(); i++)
					k.pop_back();
			}

			return k;
		}



		string encryptMessage()
		{
			string encryptedMessage;
			string ASCIImsg = transformMessage();
			string ASCIIkey = generateKey();
			int messageSize = transformMessage().size();

			for (int i = 0; i < messageSize; i++) {
					if(isupper(ASCIImsg[i]))
					//Converting [A-Z] to numbers [0-25]
					encryptedMessage.push_back(((ASCIImsg[i] + ASCIIkey[i]) % 26) + 'A');
			}

			return encryptedMessage;
		}

		string decryptMessage()
		{
			string decryptedMessage;
			string ASCIImsg = encryptMessage();
			string ASCIIkey = generateKey();
			int messageSize = transformMessage().size();

			for (int i = 0; i < messageSize; i++) {
				if (isupper(ASCIImsg[i]))
					//Converting [A-Z] to numbers [0-25]
					decryptedMessage.push_back(((ASCIImsg[i] - ASCIIkey[i]+26) % 26) + 'A');
			}

			return decryptedMessage;
		}



	private:
		string message;
		string key;
};

bool isValidString(string input) {
	//Checks if all elements in the string are alphabetical characters
	return all_of(input.begin(), input.end(), isalpha);
}



int main() {

	string m;
	string k;
	vigenereCipher text;

	
		cout << "What is the message you want to encrypt?: ";
		getline(cin, m);
		text.setMessage(m);


	cout << "What is your keyword?: ";

	//Loop to validate user input for key
	for (;;) {
	

		cin >> k;
		text.setKeyword(k);

		if (!isValidString(text.getKeyword())) {
			cout << "Keyword can only contain alphabetical characters. Please enter a valid keyword: ";
			cin.clear();
		}
		else
			break;
	}
	
	//Output encrypted and decrypted message
	cout << "Your message encrypted is: " << text.encryptMessage() << endl;
	cout << "Your message decrypted is: " << text.decryptMessage();


	return 0;
}



