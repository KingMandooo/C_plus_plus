
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str1 = "I like ";         // string str1("I like ");
	string str2 = "string class"; 
	string str3 = str1 + str2;       // 🎈🎈 string 객체간 덧셈연산, 이는 operator+ 연산자의 오버로딩을 의미

	cout << str1 << endl;            // 🎈🎈 string 클래스가 << 연산자에 대해서도 오버로딩 되어있음을 확인
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;
	if (str1 == str3)
		cout << "동일 문자열!" << endl;
	else
		cout << "동일하지 않은 문자열!" << endl;

	string str4;
	cout << "문자열 입력: ";
	cin >> str4;                                     // 🎈🎈 string 클래스는 >> 연산자에 대해서도 오버로딩 되어있음을 확인
	cout << "입력한 문자열: " << str4 << endl;
	return 0;
}

