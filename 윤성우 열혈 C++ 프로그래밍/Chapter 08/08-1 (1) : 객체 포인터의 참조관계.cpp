๐ข ๊ฐ์ฒด ํฌ์ธํฐ ๋ณ์ : ๊ฐ์ฒด์ ์ฃผ์ ๊ฐ์ ์ ์ฅํ๋ ํฌ์ธํฐ ๋ณ์


  Person* ptr;         // ํฌ์ธํฐ ๋ณ์ ์ ์ธ
  ptr = new Person();  // ํฌ์ธํฐ ๋ณ์์ ๊ฐ์ฒด ์ฐธ์กฐ


  ๐๐ Personํ ํฌ์ธํฐ๋ Person ๊ฐ์ฒด๋ฟ๋ง ์๋๋ผ, Person์ ์์ํ๋ ์ ๋ ํด๋์ค์ ๊ฐ์ฒด๋ ๊ฐ๋ฆฌํฌ ์ ์๋ค.
    
  
  class Studnet : public Person
  {
     ....
  };

  Person* ptr = new Student();    // Personํ ํฌ์ธํฐ๊ฐ Student ๊ฐ์ฒด๋ฅผ ๊ฐ๋ฆฌํจ๋ค.



  class PartTimeStudent : public Student
  {
     ....
  };

  Person* ptr1 = new PartTimeStudent();     // Personํ ํฌ์ธํฐ๊ฐ PartTimeStudent ๊ฐ์ฒด๋ฅผ ๊ฐ๋ฆฌํจ๋ค.
  Student* ptr2 = new PartTimeStudent();    // Studnetํ ํฌ์ธํฐ๊ฐ PartTimeStudent ๊ฐ์ฒด๋ฅผ ๊ฐ๋ฆฌํจ๋ค.

  "C++์์, AAAํ ํฌ์ธํฐ ๋ณ์๋ AAA ๊ฐ์ฒด ๋๋ AAA๋ฅผ ์ง์  ํน์ ๊ฐ์ ์ ์ผ๋ก ์์ํ๋ ๋ชจ๋  ๊ฐ์ฒด๋ฅผ ๊ฐ๋ฆฌํฌ ์ ์๋ค.(๊ฐ์ฒด์ ์ฃผ์ ๊ฐ์ ์ ์ฅํ  ์ ์๋ค)."
    
                                                           // ๐๐ ๋น์ฐํ ํฌ์ธํฐ ๋ณ์์๋ ์ฃผ์๊ฐ์ด ์ ์ฅ๋์ด์ผ ํ๋๊น,
                                                           //       Person* ptr = new Studnet(); ์์ ptr์๋ Studnet ๊ฐ์ฒด์ ์ฃผ์๊ฐ์ด ์ ์ฅ๋๊ฒ ์ง??

--------------------------------------------------------------------------------------------------
    
#include <iostream>
using namespace std;

class Person
{
public: 
	void Sleep() { cout << "Sleep" << endl; }
};

class Student : public Person
{
public:
	void Study() { cout << "Study" << endl; }
};

class PartTimeStudent : public Student
{
public:
	void Work() { cout << "Work" << endl; }
};

int main()
{
	Person* ptr1 = new Student();                          // ํ์์ ์ฌ๋์ด๋ค.         ํ์์ ์ฌ๋์ ์ผ์ข์ด๋ค.
	Person* ptr2 = new PartTimeStudent();                  // ๊ทผ๋กํ์์ ์ฌ๋์ด๋ค.     ๊ทผ๋กํ์์ ์ฌ๋์ ์ผ์ข์ด๋ค.
	Student* ptr3 = new PartTimeStudent();                 // ๊ทผ๋กํ์์ ํ์์ด๋ค.     ๊ทผ๋กํ์์ ํ์์ ์ผ์ข์ด๋ค.

	ptr1->Sleep();                                 // ๐๐  Student์ PartTimeStudent ๊ฐ์ฒด๋ฅผ Person ๊ฐ์ฒด์ ์ผ์ข์ผ๋ก ๊ฐ์ฃผํ๋ค.
	ptr2->Sleep();
	ptr3->Study();

	delete ptr1;
	delete ptr2;
	delete ptr3;

	return 0;
}

--------------------------------------
  
#include <iostream>
using namespace std;

class BB
{
private:
	int num1;
	int num2;
public:
	BB(int num1, int num2) : num1(num1), num2(num2)
	{}
	int Add()
	{
		return num1 + num2;
	}
};

class AA : public BB
{
private:
	int a;
	int b;
public:
	AA(int a, int b, int num1, int num2) : a(a), b(b), BB(num1, num2)
	{}
  
	//int Add()   // ๊ธฐ์ดํด๋์ค BB์ Add() ํจ์ ์ฌ์ ์ (override)
	//{
	//	return a + b;
	//}
  
	int Add(int c)            // <-- ๐๐ ์ด ๋ถ๋ถ์ด ์ฃผ์์ฒ๋ฆฌ๊ฐ ๋์ด์์ผ๋ฉด  cout << aa.Add() << endl; ์ด ๋ฌธ์ฅ์ด ์ค๋ฅ๊ฐ ์๋ธ
	{                            
		return a + b + c;      // โ A. ์ด๋ฌ๋ฉด ๊ฒฐ๋ก ์ด "์ค๋ฒ๋ก๋ฉ์ด๋  ์ค๋ฒ๋ผ์ด๋ฉ์ด๋  ์ ๋ ํด๋์ค์ ๊ธฐ์ด ํด๋์ค์ ํจ์๊ฐ ๊ฒน์น๋ ์ํฉ์์๋
	}                              //        ๊ธฐ์ดํด๋์ค์ ํจ์๋ฅผ ํธ์ถํ๋ ค๋ฉด BB:: ์ ๊ฐ์ ์์ผ๋ก ๋ช์๋ฅผ ํด์ค์ผํ๋ค."
};
 
int main()
{
	AA aa(3, 5, 7, 8);
 	BB* bb = new AA(1, 2, 3, 4);   // ๐๐ BB ๊ฐ์ฒด๊ฐ ์ ๋ํด๋์ค AA์ ๊ฐ์ฒด ์ ์ฅ
  
	cout << aa.Add() << endl;  // <-- โ Q. ์ฌ๊ธฐ์ ์ค๋ฅ๊ฐ ๋๋๊ฒ ์ดํด๊ฐ ์๋๋ค? (Answer ์์) // 2023.01.28 ๋ค์๋ณธ ๋: ๊ทธ๋ฅ aa.Add() ํจ์์๋ ์ธ์๊ฐ ํ์ํจ.
  	cout << aa.BB::Add() << endl;             // aa.num1 = 7 
	cout << bb->Add() << endl;                // aa.num2 = 8    ์ด๋ ๊ฒ ํ ๋นํด์คฌ๋๋ฐ
                                                  // aa.Add()๋ ๊ธฐ์ดํด๋์ค BB์ ์ ์ฅ๋์ด์๊ธฐ ๋๋ฌธ์
	delete bb;                                // aa.num1 + aa.num2 ๊ฐ์ด ๋ฐํ๋์ด์ผ ํ๋๊ฒ ์๋๊ฐ?
	return 0;                                 // ์ AA ํด๋์ค์ ์ ์๋์ด์๋ Add() ํจ์์๋ง ๊ธฐ์ค์ด ๋ง์ถฐ์ง์ง?
}                                                
 						 
