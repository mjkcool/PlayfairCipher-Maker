#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;
#define ARRAY 64
#define KBSIZE 5

//─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼ ━ ┃ ┏ ┓ ┛ ┗ ┣ ┳ ┫ ┻ ╋ ┠ ┯ ┨ ┷ ┿ ┝ ┰ ┥ ┸ ╂ ┒ ┑ ┚ ┙ ┖ ┕ ┎ ┍ ┞ ┟ ┡ ┢ ┦ ┧ ┩ ┪ ┭ ┮ ┱ ┲ ┵ ┶ ┹ ┺ ┽ ┾ ╀ ╁ ╃ ╄ ╅ ╆ ╇ ╈ ╉ ╊
//Alphabet ASCII 65~90

void eraseSpace(char* key) {
	int i, index = 0;

	for (i = 0; key[i] != 0; i++) {
		if (key[i] != ' ') {
			key[index] = key[i];
			index++;
		}
	}
	key[index] = 0;
}


void encryption() {
	char key[ARRAY];
	char* raw_key;
	char keyboard[KBSIZE][KBSIZE];

	std::cout << "\n┏━━━━ Processing... ━━━━ Encryption ━━━━┓\n┃\n";
	std::cout << "┣━■ Enter your Cipher key\n(*Only in Eng, till " << ARRAY - 1 << " letter include spaces)\n : ";
	std::cin.ignore();
	std::cin.getline(key, ARRAY);
	int len = std::strlen(key);
	raw_key = new char[len + 1];
	strcpy_s(raw_key, len + 1, key);

	eraseSpace(key);
	len = std::strlen(key);

	int i, j, keyidx;
	//Make to uppercase all
	for (keyidx = 0; keyidx < len; keyidx++) {
		key[keyidx] = (char)toupper(key[keyidx]);
	}

	keyidx = 0;
	int alpbt = 65; //A
	for (i = 0; i < KBSIZE; i++) {
		for (j = 0; j < KBSIZE; j++) {
			if (keyidx < len) keyboard[i][j] = (char)toupper(key[keyidx++]);
			else {
				//if Q and Z, I and J
				//if alpbt in key: ++
				keyboard[i][j] = (char)alpbt++;

			}
		}
	}

	//std::cout << key;

	std::cin.clear();
	return;
}

void decryption() {

	return;
}

int main()
{
	std::cout << "Playfair Substitution Cipher Maker\n\n";
	std::cout << "■[enter 'E'] Encryption ■\n";
	std::cout << "■[enter 'D'] Decryption ■\n";

	std::cout << "\nEnter character which you have to do >> ";
	while (true) {
		char process;
		std::cin >> process;
		if (process == 'E') {
			encryption();
			break;
		}
		else if (process == 'D') {
			decryption();
			break;
		}
		else {
			std::cout << "a null character. Enter again >> ";
		}
	}

	return 0;
}