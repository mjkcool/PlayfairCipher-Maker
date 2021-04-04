#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <string.h>
using namespace std;
#define ARRAY 64
#define KBSIZE 5

//─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼ ━ ┃ ┏ ┓ ┛ ┗ ┣ ┳ ┫ ┻ ╋ ┠ ┯ ┨ ┷ ┿ ┝ ┰ ┥ ┸ ╂ ┒ ┑ ┚ ┙ ┖ ┕ ┎ ┍ ┞ ┟ ┡ ┢ ┦ ┧ ┩ ┪ ┭ ┮ ┱ ┲ ┵ ┶ ┹ ┺ ┽ ┾ ╀ ╁ ╃ ╄ ╅ ╆ ╇ ╈ ╉ ╊
//Alphabet ASCII 65~90

void removeSpaceAndDupplication(char* key) { //입력받은 문장의 공백을 제거
	int i, index = 0;

	for (i = 0; key[i] != 0; i++) {
		if (key[i] != ' ') {
			key[index] = key[i];
			index++;
		}
	}
	key[index] = 0; //배열 종료
	char newkey[ARRAY]; //중복제거된 문자열
	newkey[0] = key[0];
	int newkeyi = 0;
	for (i = 1; key[i] != 0; i++) { //배열끝까지 반복
		bool exi = false;
		for (int j = 0; j < i; j++) if (key[i] == key[j]) exi = true; //앞서 있는 값이면 체크
		if(exi==false) newkey[++newkeyi] = key[i]; //앞서 없는 값이면 추가.
	}
	newkey[++newkeyi] = 0; //배열 종료
	
	for (i=0; newkey[i] != 0; i++) { 
		key[i] = newkey[i]; //복사~!
	}
	key[i] = 0;
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

	int i, j, keyidx;
	//key값을 대문자로 변환
	for (keyidx = 0; keyidx < len; keyidx++) {
		key[keyidx] = (char)toupper(key[keyidx]);
	}

	removeSpaceAndDupplication(key); //공백 제거
	len = std::strlen(key);


	keyidx = 0;
	int alpbt = 65; //A
	bool qzexist = false;
	for (i = 0; i < KBSIZE; i++) {
		for (j = 0; j < KBSIZE; j++) {
			if (keyidx < len) { //key 대입
				if (key[keyidx] == 81 || key[keyidx] == 90) {
					if (qzexist == false) keyboard[i][j] = key[keyidx];
					else {
						qzexist = true;
					} keyidx++;
				}
				else {
					keyboard[i][j] = key[keyidx++];
				}
			}
			else { //남은 알파벳 대입
				//if Q and Z
				if ((alpbt == 81 || alpbt == 90)) {
					if (qzexist == false) keyboard[i][j] = (char)alpbt;
					alpbt++;
				}
				else {
					//이미 해당알파벳이 key에 존재하는(사용된) 경우
					if (strchr(key, (char)alpbt) == NULL) keyboard[i][j] = (char)alpbt;
					alpbt++;
				}
			}
		}
	}

	for (i = 0; i < KBSIZE; i++) {
		for (j = 0; j < KBSIZE; j++) {
			std::cout << "_"<<keyboard[i][j]<< " ";
		}
		std::cout << "\n";
	}

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