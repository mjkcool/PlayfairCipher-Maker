#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
using namespace std;
#define ARRAY 64
#define KBSIZE 5

//─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼ ━ ┃ ┏ ┓ ┛ ┗ ┣ ┳ ┫ ┻ ╋ ┠ ┯ ┨ ┷ ┿ ┝ ┰ ┥ ┸ ╂ ┒ ┑ ┚ ┙ ┖ ┕ ┎ ┍ ┞ ┟ ┡ ┢ ┦ ┧ ┩ ┪ ┭ ┮ ┱ ┲ ┵ ┶ ┹ ┺ ┽ ┾ ╀ ╁ ╃ ╄ ╅ ╆ ╇ ╈ ╉ ╊
//Alphabet ASCII 65~90

void eraseSpace(char* key) { //입력받은 문장의 공백을 제거
	int i, index = 0;

	for (i = 0; key[i] != 0; i++) {
		if (key[i] != ' ') {
			key[index] = key[i];
			index++;
		}
	}
	key[index] = 0; //배열 종료
}


void encryption() { //암호화 수행 함수
	char key[ARRAY]; //사용될 암호키
	char* raw_key; //암호키 원문
	char keyboard[KBSIZE][KBSIZE]; //암호판

	std::cout << "\n┏━━━━ Processing... ━━━━ Encryption ━━━━┓\n┃\n";
	std::cout << "┣━■ Enter your Cipher key\n(*Only in Eng, till " << ARRAY - 1 << " letter include spaces)\n : ";
	std::cin.ignore(); 
	std::cin.getline(key, ARRAY); //암호키 입력
	int len = std::strlen(key);
	raw_key = new char[len + 1];
	strcpy_s(raw_key, len + 1, key);

	eraseSpace(key); //공백 제거
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
				if (alpbt == 81 || alpbt == 90) {

				}
				//if alpbt in key: ++
				
				keyboard[i][j] = (char)alpbt++;
				
			}
		}
	}

	//std::cout << key;

	std::cin.clear();
	return;
}

void decryption() { //복호화 수행 함수

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