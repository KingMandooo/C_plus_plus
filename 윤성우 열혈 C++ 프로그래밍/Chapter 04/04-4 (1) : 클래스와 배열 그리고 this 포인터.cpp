

๐ข ๊ฐ์ฒด ๋ฐฐ์ด

 SoSimple arr[10];  
 
 SoSimple* arr = new SoSimple[10];    ์ด๋ฌํ ํํ๋ก ์ ์ธ
 
 ์ด๋ฌํ ๋ฐฐ์ด์ ์ ์ธ๊ณผ์ ์์๋ ํธ์ถํ  ์์ฑ์๋ฅผ ๋ณ๋๋ก ๋ช์ํ์ง ๋ชปํ๋ค. // ๐๐ ์์ฑ์์ ์ธ์๋ฅผ ์ ๋ฌํ์ง ๋ชปํ๋ค.
 
 ์ฆ ์์ ํํ๋ก ๋ฐฐ์ด์ด ์์ฑ๋๋ ค๋ฉด ๋ค์ ํํ์ ์์ฑ์๊ฐ ๋ฐ๋์ ์ ์๋์ด ์์ด์ผ ํ๋ค.
   
  SoSimple() {}

--------------------------------------------------
  
  
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
private:
	char* name;
	int age;
public:
	Person(const char* myname, int myage)
	{
		int len = strlen(myname) + 1;
		name = new char[len];
		strcpy(name, myname);
		age = myage;
	}

	Person()
	{
		name = NULL;
		age = 0;
		cout << "called Person()" << endl;
	}

	void SetPersonInfo(char* myname, int myage)
	{
		name = myname;
		age = myage;
	}

	void ShowPersonInfo() const
	{
		cout << "์ด๋ฆ: " << name << endl;
		cout << "๋์ด: " << age << endl;
	}

	~Person()                             
	{
		delete[]name;
		cout << "call destructor!" << endl;
	}
};

int main()
{
	Person parr[3];       // ์์ฑ์ 3๋ฒ ํธ์ถ
	char namestr[100];  
	char* strptr;
	int age;
	int len;

	for (int i = 0; i < 3; i++)      // ์ผ์ผ์ด ์ด๊ธฐํ์ ๊ณผ์ ์ ๊ฑฐ์น๋ ๊ณผ์ 
	{
		cout << "์ด๋ฆ: ";
		cin >> namestr;
		cout << "๋์ด: ";
		cin >> age;
		len = strlen(namestr) + 1;
		strptr = new char[len];                         โ Q. ์ ๋์ ์ผ๋ก ํ ๋นํ ํฌ์ธํฐ strptr์ ํด์ ๋ฅผ ์์์ผ์ค๊น?
		strcpy(strptr, namestr);                             
		parr[i].SetPersonInfo(strptr, age);                 A. ์ด์ฒํผ ๊ฐ์ฒด์ ๋ฉค๋ฒ๋ณ์์ธ ํฌ์ธํฐ name๊ณผ (์ฃผ์)๊ฐ์ ๊ณต์ ํ๊ณ , ์ด๋ฅผ ํด์ ํ  ๊ฒฝ์ฐ
	}                                                        ์ฌ์ฉํ๋ ๋ฉ๋ชจ๋ฆฌ๋ ํจ๊ป ํด์ ๊ฐ ๋๋ฏ๋ก ๊ตณ์ด strptr์ ํด์ ์์ผ์ฃผ์ง ์๋ ๊ฒ ๊ฐ๋ค.
	parr[0].ShowPersonInfo();
	parr[1].ShowPersonInfo();
	parr[2].ShowPersonInfo();

	return 0;   // ์๋ฉธ์ 3๋ฒ ํธ์ถ
}


/*
  ์ถ๋ ฅ๊ฒฐ๊ณผ: called Person()     
            called Person()
            called Person()
            ์ด๋ฆ: sun
            ๋์ด: 24
            ์ด๋ฆ: hong
            ๋์ด: 41
            ์ด๋ฆ: kim
            ๋์ด: 37
            ์ด๋ฆ: sun, ๋์ด: 24
            ์ด๋ฆ: hong, ๋์ด: 41
            ์ด๋ฆ: kim, ๋์ด: 37
            call destructor!         
            call destructor!
            call destructor!
*/
------------------------
  
๐ข ๊ฐ์ฒด ํฌ์ธํฐ ๋ฐฐ์ด      (์์ ์ฝ๋์ ๋น๊ตํด๋ณด๊ธฐ : ๐๐ ์์ฑ์์ ํธ์ถ์์ ์ ์ ์ฌํ๋ณด๊ธฐ)
  
    --> ๊ฐ์ฒด์ ์ฃผ์๊ฐ๋ค์ ๋ชจ์

#include <iostream>
#include <cstring>
using namespace std;

class Person
{
private:
	char* name;
	int age;
public:
	Person(const char* myname, int myage)
	{
		int len = strlen(myname) + 1;
		name = new char[len];
		strcpy(name, myname);
		age = myage;
	}

	Person()
	{
		name = NULL;
		age = 0;
		cout << "called Person()" << endl;
	}

	void SetPersonInfo(char* myname, int myage)
	{
		name = myname;
		age = myage;
	}

	void ShowPersonInfo() const
	{
		cout << "์ด๋ฆ: " << name << ", ";
		cout << "๋์ด: " << age << endl;
	}

	~Person()                             
	{
		delete[]name;
		cout << "call destructor!" << endl;
	}
};

int main()
{
	Person* parr[3];         // ํฌ์ธํฐ ํ์์ ๋์ ์ผ๋ก ํ ๋นํด์ผ ๊ฐ์ฒด๊ฐ ์์ฑ ๋ฐ๋ผ์ ์ฌ๊ธฐ์ ์์ฑ์ ํธ์ถ x
	char namestr[100];
	int age;

	for (int i = 0; i < 3; i++)
	{
		cout << "์ด๋ฆ: ";
		cin >> namestr;
		cout << "๋์ด: ";
		cin >> age;
		parr[i] = new Person(namestr, age);  // ์ฌ๊ธฐ์ ๋์ ํ ๋น -> ์์ฑ์ -> ๊ฐ์ฒด ์์ฑ  
	}

	parr[0]->ShowPersonInfo();
	parr[1]->ShowPersonInfo();
	parr[2]->ShowPersonInfo();
	delete parr[0];
	delete parr[1];
	delete parr[2];

	return 0;   // ์๋ฉธ์ 3๋ฒ ํธ์ถ
}


/*
  ์ถ๋ ฅ๊ฒฐ๊ณผ: ์ด๋ฆ: sun
            ๋์ด: 24
            ์ด๋ฆ: hong
            ๋์ด: 41
            ์ด๋ฆ: kim
            ๋์ด: 37
            ์ด๋ฆ: sun, ๋์ด: 24
            ์ด๋ฆ: hong, ๋์ด: 41
            ์ด๋ฆ: kim, ๋์ด: 37
            call destructor!         
            call destructor!
            call destructor!
*/

