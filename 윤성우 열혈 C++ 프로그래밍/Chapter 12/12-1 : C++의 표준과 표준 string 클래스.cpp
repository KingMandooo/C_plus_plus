
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str1 = "I like ";         // string str1("I like ");
	string str2 = "string class"; 
	string str3 = str1 + str2;       // ππ string κ°μ²΄κ° λ§μμ°μ°, μ΄λ operator+ μ°μ°μμ μ€λ²λ‘λ©μ μλ―Έ

	cout << str1 << endl;            // ππ string ν΄λμ€κ° << μ°μ°μμ λν΄μλ μ€λ²λ‘λ© λμ΄μμμ νμΈ
	cout << str2 << endl;
	cout << str3 << endl;

	str1 += str2;
	if (str1 == str3)
		cout << "λμΌ λ¬Έμμ΄!" << endl;
	else
		cout << "λμΌνμ§ μμ λ¬Έμμ΄!" << endl;

	string str4;
	cout << "λ¬Έμμ΄ μλ ₯: ";
	cin >> str4;                                     // ππ string ν΄λμ€λ >> μ°μ°μμ λν΄μλ μ€λ²λ‘λ© λμ΄μμμ νμΈ
	cout << "μλ ₯ν λ¬Έμμ΄: " << str4 << endl;
	return 0;
}

