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

void processForPlainTxt(char *str) {
	int i, newi = 0;
	char newstr[ARRAY];
	
	newstr[0] = str[newi++];
	for (i = 1; str[i] != 0; i++) {
		if (str[i-1] == str[i]) {
			newstr[newi++] = 'X';
		}
		newstr[newi++] = str[i];
	}
	//홀수면 끝에 'X' 대입
	if (std::strlen(newstr)%2==1) {
		newstr[newi++] = 'X';
	}
	newstr[newi] = 0; //종료
	

	//복사
	for (i = 0; newstr[i] != 0; i++) {
		str[i] = newstr[i]; //복사~!
	}
}

void makeBoard(char board[][KBSIZE], char* key, int* len) {
	int i = 0; int j = 0; bool qzexist = false; //Q or Z
	int keyidx;

	for (keyidx = 0; keyidx < *len; keyidx++) //key값 보드에 배치
	{
		if (key[keyidx] == 81 || key[keyidx] == 90) { //if Q or Z
			if (qzexist == false) {
				board[i][j] = key[keyidx];
				qzexist = true;

				if (j >= KBSIZE - 1) {
					i++; j = 0;
				}
				else j++;
			};
		}
		else {
			board[i][j] = key[keyidx];
			if (j >= KBSIZE - 1) {
				i++; j = 0;
			}
			else j++;
		}
	}

	int alpbt = 65; //A
	while (i < KBSIZE && j < KBSIZE) { //보드 나머지 채우기
		//if Q and Z
		if (alpbt == 81 || alpbt == 90) {
			if (qzexist == false) {//Q나 Z가 아직 없으면
				board[i][j] = alpbt;
				qzexist = true;
				if (j >= KBSIZE - 1) {
					i++; j = 0;
				}
				else j++;
			}
		}
		else { //Q와 Z를 제외한 모든 알파벳
			if (!strchr(key, alpbt)) {//해당알파벳이 key에 있지 않은 경우
				board[i][j] = alpbt;
				if (j >= KBSIZE - 1) {
					i++; j = 0;
				}
				else j++;
			}
		}
		alpbt++;
	}

	//암호판 출력
	std::cout << "\n_Cipher board *position of Q and Z is same as one.\n\n";
	for (i = 0; i < KBSIZE; i++) {
		for (j = 0; j < KBSIZE; j++) {
			std::cout << "_" << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}

 void getIndex(char board[][KBSIZE], char c, int* row, int* col) {
	for (int i = 0; i < KBSIZE; i++) {
		for (int j = 0; j < KBSIZE; j++) {
			if (board[i][j] == c) {
				*row = i; *col = j;
			}
		}
	}
}

void encryption() { //암호화 수행 함수
	char key[ARRAY]; //사용될 암호키
	char* raw_key; //암호키 원문
	char plaintxt[ARRAY]; //평문
	char keyboard[KBSIZE][KBSIZE]; //암호판
	char(*keyboardPtr)[5] = keyboard; //암호판 포인터
	

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
	int* lenPtr = &len;
	
	//암호판 제작
	makeBoard(keyboardPtr, key, lenPtr);
	
	//평문 입력
	std::cout << "\nEnter your plain text\n(*Only in Eng, till " << ARRAY - 1 << " letter include spaces)\n : ";
	std::cin.ignore();
	std::cin.getline(plaintxt, ARRAY);


	//암호화
	int txtidx;
	for (txtidx = 0; txtidx < len; txtidx++) { //평문을 대문자로 변환
		plaintxt[txtidx] = (char)toupper(plaintxt[txtidx]);
	}

	int idx;
	//대문자변환
	for (idx = 0; idx < len; idx++) {
		plaintxt[idx] = (char)toupper(plaintxt[idx]);
	}

	removeSpace(plaintxt);//공백제거
	processForPlainTxt(plaintxt); //중복문자&홀수종료 뒤 X 대입
	
	
	/*
	string ciphertxt; //암호문
	int fair_i = 0;
	int r_l = -1, c_l = -1;
	int r_r = -1, c_r = -1;
	int* row_l = &r_l, *row_r = &r_r;
	int* col_l = &c_l, * col_r = &c_r;
	int getRow, getCol;

	while (fair_i< std::strlen(plaintxt)) {
		getIndex(keyboardPtr, plaintxt[fair_i], row_l, col_l);
		getIndex(keyboardPtr, plaintxt[fair_i + 1], row_r, col_r);
		//어차피 같을 일이 없기 때문에 두개를 각각 비교
		//만약 행렬중 하나 인덱스가 같다면
		if (r_l == r_r) {
			int val_l, val_r;
			if (c_l < 4) val_l = c_l + 1; else val_l = 0;
			if (c_r < 4) val_r = c_l + 1; else val_r = 0;
			ciphertxt += keyboard[r_l][val_l];
			ciphertxt += keyboard[r_r][val_r];
		}
		else if (c_l == c_r) {
			int val_l, val_r;
			if (r_l < 4) val_l = r_l + 1; else val_l = 0;
			if (r_r < 4) val_r = r_l + 1; else val_r = 0;
			ciphertxt += keyboard[val_l][c_l];
			ciphertxt += keyboard[val_l][c_r];
		}
		else { //같은 인덱스가 없다면
			int mx_r, mx_c;
			if (r_l < r_r) mx_r = r_r; else mx_r = r_l;
			ciphertxt += keyboard[mx_r][c_l];
			if (c_l < c_r) mx_c = c_r; else mx_c = c_l;
			ciphertxt += keyboard[r_r][mx_c];
		}

		fair_i+=2;
	}
	*/
	std::cout << plaintxt;
	

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