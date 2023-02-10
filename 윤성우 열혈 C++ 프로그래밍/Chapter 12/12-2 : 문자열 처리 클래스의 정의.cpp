직접 구현해보는 string 클래스

💙 내가 짠 코드 💙

#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
	char* arr;
public:
	String() { arr = NULL; }
	String(const char* arr)
	{
		this->arr = new char[strlen(arr) + 1];
		strcpy(this->arr, arr);
	}
	String(const String& copy)
	{
		arr = new char[strlen(copy.arr) + 1];
		strcpy(arr, copy.arr);
	}
	String& operator=(const String& copy)
	{
		if (arr != NULL)
			delete[] arr;
		arr = new char[strlen(copy.arr) + 1];
		strcpy(arr, copy.arr);
		return *this;
	}
	String operator+(const String& copy)
	{
		char* s = new char[strlen(arr) + strlen(copy.arr) + 1];  // 이부분에서 널문자 계산 잘못해서 오래걸림.. (처음에 -1 이라고했음)
		strcpy(s, arr);
		strcat(s, copy.arr);

		String ss = s;
		delete[] s;    
		return ss;
	}
	String& operator+=(const String& copy)
	{
		char* s = new char[strlen(arr) + strlen(copy.arr) + 1];
		strcpy(s, arr);
		strcat(s, copy.arr);

		if (arr != NULL)
			delete[] arr;
		arr = s;
		return *this;
	}
	bool operator==(const String& copy)
	{
		if (strcmp(arr, copy.arr) == 0)
			return true;
		else
			return false;
	}
	~String()
	{
		if (arr != NULL)
			delete[] arr;
	}

	friend ostream& operator<<(ostream& os, const String& copy);
	friend istream& operator>>(istream& is, String& copy);
};

ostream& operator<<(ostream& os, const String& copy)
{
	os << copy.arr;
	return os;
}

istream& operator>>(istream& is, String& copy)
{
	char str[100];
	is >> str;
	copy = String(str);
	return is;
}

int main() 
{
	String str1 = "I like ";
	String str2 = "string class";
	String str3 = str1 + str2;

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;
	if (str1 == str3)
		cout << "동일 문자열!" << endl;
	else
		cout << "동일하지 않은 문자열!" << endl;

	String str4;
	cout << "문자열 입력: ";
	cin >> str4;
	cout << "입력한 문자열: " << str4 << endl;
	return 0; 
}

------------------------------------------------------------------

💙 책 코드 💙

#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
	int len;
	char* str;
public:
	String()
	{
		len = 0;
		str = NULL;
	}
	String(const char* s)
	{
		len = strlen(s) + 1;
		str = new char[len];
		strcpy(str, s);
	}
	String(const String& s)
	{
		len = s.len;
		str = new char[len];
		strcpy(str, s.str);
	}
	~String()
	{
		if (str != NULL)
			delete[]str;
	}
	String& operator=(const String& s)
	{
		if (str != NULL)
			delete[] str;
		len = s.len;
		str = new char[len];
		strcpy(str, s.str);
		return *this;
	}
	String& operator+=(const String& s)
	{
		len += (s.len - 1);
		char* tempstr = new char[len];
		strcpy(tempstr, str);
		strcat(tempstr, s.str);

		if (str != NULL)
			delete[] str;
		str = tempstr;
		return *this;
	}
	bool operator==(const String& s)
	{
		return strcmp(str, s.str) ? false : true;
	}
	String operator+ (const String& s)
	{
		char* tempstr = new char[len + s.len - 1];
		strcpy(tempstr, str);
		strcat(tempstr, s.str);

		String temp(tempstr);
		delete[] tempstr;
		return temp;
	}
	friend ostream& operator<<(ostream& os, const String& copy);
	friend istream& operator>>(istream& is, String& copy);
};

ostream& operator<<(ostream& os, const String& copy)
{
	os << copy.str;
	return os;
}

istream& operator>>(istream& is, String& copy)
{
	char str[100];
	is >> str;
	copy = String(str);
	return is;
}

int main()
{
	String str1 = "I like ";
	String str2 = "string class";
	String str3 = str1 + str2;

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;
	if (str1 == str3)
		cout << "동일 문자열!" << endl;
	else
		cout << "동일하지 않은 문자열!" << endl;

	String str4;
	cout << "문자열 입력: ";
	cin >> str4;
	cout << "입력한 문자열: " << str4 << endl;
	return 0;
}


