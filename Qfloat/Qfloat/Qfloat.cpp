﻿#include "Qfloat.h"
Qfloat::Qfloat() {
	for (int i = 0; i < 4; i++)						// khởi tạo Qfloat với giá trị 0
		this->data[i] = 0;
}
Qfloat::Qfloat(const Qfloat &p) {
	for (int i = 0; i < 4; i++) 					// copy từng byte của p vào Qfloat
		this->data[i] = p.data[i];
}
Qfloat::~Qfloat() {}
int Qfloat::SetBit(int i, bool type) {				// set bit 1 tai vi tri i
	if (type != 0) {
		this->data[i / 32] = this->data[i / 32] | (1 << (31 - i % 32));
	}
	return this->data[i / 32];
}
int Qfloat::GetBit(int i) {							// lấy bit tại vị trí i
	return (this->data[i / 32] >> (31 - i % 32)) & 1;
}
void Qfloat::ScanQfloat() {
	string s;
	fflush(stdin);
	getline(cin, s);
	*this = Qfloat(s);
}
void Qfloat::PrintQfloat() {
	for (int i = 0; i < 128; i++) {
		cout << GetBit(i);
		if (i == 0)
			cout << " ";
		if (i == 15)
			cout << " ";
	}
}
Qfloat::Qfloat(string s) {
	for (int i = 0; i < 4; i++) {					// khởi tạo Qfloat với giá trị 0 
		this->data[i] = 0;
	}
	string integer, decimal;						// integer chứa phần nguyên, decimal chứa phần thập phân
	int len = s.length();							// độ dài tham số chuỗi 
	int i = 0;										// biến đếm dùng cho vòng lặp
	if (s[0] == '-') {								// nếu là số âm
		SetBit(0, 1);								// thì set bit 1 tại vị trí 0
		i++;										// tăng biến đếm đến vị trí tiếp theo
	}
	// tách integer và decimal
	for (i; i < len; i++) {							// chuyển phần nguyên vào integer
		if (s[i] != '.') {
			integer += s[i];
		}
		else {
			break;									// nếu gặp dấu . thì ngừng
		}
	}
	i++;
	for (; i < len; i++) {							// chuyển phần thập phân vào decimal
		decimal += s[i];
	}
	string integer_bin = IntegerToBinary(integer);	// chuyển integer sang nhị phân
	//----
	cout << integer_bin; // chưa reverse
}
string Qfloat::IntegerToBinary(string s) {			// chưa reverse
	string result;
	while (s != "0") {								// chia tới khi s = 0
		int len = s.length();
		if ((s[len - 1] - '0') % 2 == 0) {			// chia hết cho 2
			result += '0';
		}
		else {										// không chia hết cho 2
			result += '1';
		}
		s = this->Div2String(s);					// chia chuỗi cho 2, đã xử lý trường hợp nhập 000x.
	}
	if (result.empty()) {							
		result = "0";
	}
	return result; 
}


string Qfloat::Div2String(string s) {
	string result;									// chuỗi lưu kết quả
	int	dividend = 0;								// số bị chia
	int	len = s.length();							//  chiều dài chuỗi
	for (int i = 0; i < len; i++) {
		if (dividend != 0) {   						// nếu phép chia đang có dư 
			dividend = 10 + s[i] - '0';				// 10 vì chia 2 nên số dư luôn luôn là 1
			result += dividend / 2 + '0';
			dividend = dividend % 2;				// sau khi chia xong, số bị chia tiếp theo là số dư
		}
		else if (s[i] - '0' < 2) {					// s[i] nhỏ hơn 2, cho nên ta ko chia 2 dc mà phải mượn số kế tiếp 
			result += '0';							// thêm số 0
			dividend = s[i] - '0';					// cập nhật số bị chia = s[i]
		}
		else if (s[i] - '0' >= 2) {					// s[i] lớn hơn 2
			result += (s[i] - '0') / 2 + '0';
			dividend = (s[i] - '0') % 2;
		}
	}
	while (result[0] == '0' && result.length() > 1) {
		result.erase(0, 1);							// xoá số 0 dư ở đầu tiên
	}
	return result;
}
string Qfloat::Mul2String(string s) {
	string result;									// result = null
	int product = 0;								// tích
	for (int i = s.length() - 1; i >= 0; i--) {
		if (product != 0) {							// còn nhớ 1
			product = 2 * (s[i] - '0') + 1;			// +1 nhớ lúc trước
			result = char((product % 10) + '0') + result;
			if (product / 10 != 0) {
				if (i > 0) {
					product = 1;					// nhớ 1
				}
				else {
					result = '1' + result;			// nếu là số đầu tiên thì thêm 1 vào đầu 
				}
			}
			else {
				product = 0;						// không nhớ
			}
		}
		else {
			product = 2 * (s[i] - '0');
			result = char((product % 10) + '0') + result;
			if (product > 9) {						// nhớ 1
				if (i > 0) {
					product = 1;
				}
				else {
					result = '1' + result;			// nếu là số đầu tiên thì thêm 1 vào đầu 
				}
			}
			else {
				product = 0;						// <9 nên không nhớ
			}
		}
	}
	//while (result[0] == '0' && result.length() > 1) {
	//	result.erase(0, 1);							// xoá số 0 ở đầu
	//}
	return result;
}