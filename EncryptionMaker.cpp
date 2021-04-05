#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <string.h>
#include<vector>
using namespace std;
#define ARRAY 64
#define KBSIZE 5

//─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼ ━ ┃ ┏ ┓ ┛ ┗ ┣ ┳ ┫ ┻ ╋ ┠ ┯ ┨ ┷ ┿ ┝ ┰ ┥ ┸ ╂ ┒ ┑ ┚ ┙ ┖ ┕ ┎ ┍ ┞ ┟ ┡ ┢ ┦ ┧ ┩ ┪ ┭ ┮ ┱ ┲ ┵ ┶ ┹ ┺ ┽ ┾ ╀ ╁ ╃ ╄ ╅ ╆ ╇ ╈ ╉ ╊
//Alphabet ASCII 65~90

void removeSpace(char* str) { //입력받은 문장의 공백을 제거
	int i, index = 0;

	for (i = 0; str[i] != 0; i++) {
		if (str[i] != ' ') {
			str[index] = str[i];
			index++;
		}
	}
	str[index] = 0; //배열 종료
	
}

void removeDupplication(char* str) {
	int i;
	char newkey[ARRAY]; //중복제거된 문자열
	newkey[0] = str[0];
	int newkeyi = 0;
	for (i = 1; str[i] != 0; i++) { //배열끝까지 반복
		bool exi = false;
		for (int j = 0; j < i; j++) if (str[i] == str[j]) exi = true; //앞서 있는 값이면 체크
		if (exi == false) newkey[++newkeyi] = str[i]; //앞서 없는 값이면 추가.
	}
	newkey[++newkeyi] = 0; //배열 종료

	for (i = 0; newkey[i] != 0; i++) {
		str[i] = newkey[i]; //복사~!
	}
	str[i] = 0;
}

void makeBoard(char* board) {
	//https://dojang.io/mod/page/view.php?id=312
}

void encryption() { //암호화 수행 함수
	char key[ARRAY]; //사용될 암호키
	char* raw_key; //암호키 원문
	char plaintxt[ARRAY];
	char keyboard[KBSIZE][KBSIZE]; //암호판

	std::cout << "\n━━━━ Processing... ━━━━ Encryption ━━━━━\n\n";
	std::cout << "Enter your Cipher key\n(*Only in Eng, till " << ARRAY - 1 << " letter include spaces)\n : ";
	std::cin.ignore(); 
	std::cin.getline(key, ARRAY); //암호키 입력
	int len = std::strlen(key);
	raw_key = new char[len+1];
	strcpy_s(raw_key, len + 1, key);

	int i, j, keyidx;
	//key값을 대문자로 변환
	for (keyidx = 0; keyidx < len; keyidx++) {
		key[keyidx] = (char)toupper(key[keyidx]);
	}

	removeSpace(key); //공백 제거
	removeDupplication(key);
	len = std::strlen(key);
	
	
	i = 0; j = 0; bool qzexist = false; //Q or Z
	
	for (keyidx = 0; keyidx < len; keyidx++) //key값 보드에 배치
	{
		if (key[keyidx] == 81 || key[keyidx] == 90) { //if Q or Z
			if (qzexist == false) {
				keyboard[i][j] = key[keyidx];
				qzexist = true;
				
				if (j >= KBSIZE - 1) {
					i++; j = 0;
				}else j++;
			};
		}
		else {
			keyboard[i][j] = key[keyidx];
			if (j >= KBSIZE - 1) {
				i++; j = 0;
			}
			else j++;
		}
	}
	
	int alpbt = 65; //A
	while (i<KBSIZE && j<KBSIZE) { //보드 나머지 채우기
		//if Q and Z
		if (alpbt == 81 || alpbt == 90) {
			if (qzexist == false) {//Q나 Z가 아직 없으면
				keyboard[i][j] = alpbt;
				qzexist = true;
				if (j >= KBSIZE - 1) {
					i++; j = 0;
				}
				else j++;
			}
		}
		else { //Q와 Z를 제외한 모든 알파벳
			if (!strchr(key, alpbt)) {//해당알파벳이 key에 있지 않은 경우
				keyboard[i][j] = alpbt;
				if (j >= KBSIZE - 1) {
					i++; j = 0;
				}
				else j++;
			}
		}
		alpbt++;
	}

	//암호판 출력
	//std::cout << "\nInput key
	std::cout << "\n_Cipher board *position of Q and Z is same as one.\n\n";
	for (i = 0; i < KBSIZE; i++) {
		for (j = 0; j < KBSIZE; j++) {
			std::cout << "_"<<keyboard[i][j]<< " ";
		}
		std::cout << "\n";
	}

	
	std::cout << "\nEnter your plain text\n(*Only in Eng, till " << ARRAY - 1 << " letter include spaces)\n : ";
	std::cin.ignore();
	std::cin.getline(plaintxt, ARRAY);
	//암호화
	int txtidx;
	for (txtidx = 0; txtidx < len; txtidx++) { //대문자로 변환
		plaintxt[txtidx] = (char)toupper(plaintxt[txtidx]);
	}
	removeSpace(plaintxt);//공백제거


	


	std::cin.clear();
	return;
}

void decryption() { //복호화 수행 함수

	return;
}

void fileEncryption() {

}

void fileDecryption() {

}

int main()
{
	std::cout << "Playfair Substitution Cipher Maker\n\n";
	std::cout << "■[enter 1] Input encryption ■\n";
	std::cout << "■[enter 2] Input decryption ■\n";
	std::cout << "■[enter 3] .txt file Encryption ■\n";
	std::cout << "■[enter 4] .txt file Decryption ■\n";

	std::cout << "\nEnter character which you have to do >> ";
	while (true) {
		char process;
		std::cin >> process;
		if (process == '1') {
			encryption();
			break;
		}
		else if (process == '2') {
			decryption();
			break;
		}
		else if (process == '4') {
			fileEncryption();
			break;
		}
		else if (process == '5') {
			fileDecryption();
			break;
		}
		else {
			std::cout << "this is invalid number to process order. Enter again >> ";
		}
	}

	return 0;
}