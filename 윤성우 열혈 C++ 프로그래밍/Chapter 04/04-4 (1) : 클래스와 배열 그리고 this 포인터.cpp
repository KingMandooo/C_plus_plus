

🟢 객체 배열

 SoSimple arr[10];  
 
 SoSimple* arr = new SoSimple[10];    이러한 형태로 선언
 
 이러한 배열의 선언과정에서는 호출할 생성자를 별도로 명시하지 못한다. // 🎈🎈 생성자에 인자를 전달하지 못한다.
 
 즉 위의 형태로 배열이 생성되려면 다음 형태의 생성자가 반드시 정의되어 있어야 한다.
   
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
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}

	~Person()                             
	{
		delete[]name;
		cout << "call destructor!" << endl;
	}
};

int main()
{
	Person parr[3];       // 생성자 3번 호출
	char namestr[100];  
	char* strptr;
	int age;
	int len;

	for (int i = 0; i < 3; i++)      // 일일이 초기화의 과정을 거치는 과정
	{
		cout << "이름: ";
		cin >> namestr;
		cout << "나이: ";
		cin >> age;
		len = strlen(namestr) + 1;
		strptr = new char[len];                         ✅ Q. 왜 동적으로 할당한 포인터 strptr을 해제를 안시켜줄까?
		strcpy(strptr, namestr);                             
		parr[i].SetPersonInfo(strptr, age);                 A. 어처피 객체의 멤버변수인 포인터 name과 (주소)값을 공유하고, 이를 해제할 경우
	}                                                        사용하는 메모리는 함께 해제가 되므로 굳이 strptr을 해제시켜주지 않는 것 같다.
	parr[0].ShowPersonInfo();
	parr[1].ShowPersonInfo();
	parr[2].ShowPersonInfo();

	return 0;   // 소멸자 3번 호출
}


/*
  출력결과: called Person()     
            called Person()
            called Person()
            이름: sun
            나이: 24
            이름: hong
            나이: 41
            이름: kim
            나이: 37
            이름: sun, 나이: 24
            이름: hong, 나이: 41
            이름: kim, 나이: 37
            call destructor!         
            call destructor!
            call destructor!
*/
------------------------
  
🟢 객체 포인터 배열      (위의 코드와 비교해보기 : 🎈🎈 생성자의 호출시점을 유심히보기)
  
    --> 객체의 주소값들의 모임

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
		cout << "이름: " << name << ", ";
		cout << "나이: " << age << endl;
	}

	~Person()                             
	{
		delete[]name;
		cout << "call destructor!" << endl;
	}
};

int main()
{
	Person* parr[3];         // 포인터 형식은 동적으로 할당해야 객체가 생성 따라서 여기서 생성자 호출 x
	char namestr[100];
	int age;

	for (int i = 0; i < 3; i++)
	{
		cout << "이름: ";
		cin >> namestr;
		cout << "나이: ";
		cin >> age;
		parr[i] = new Person(namestr, age);  // 여기서 동적할당 -> 생성자 -> 객체 생성  
	}

	parr[0]->ShowPersonInfo();
	parr[1]->ShowPersonInfo();
	parr[2]->ShowPersonInfo();
	delete parr[0];
	delete parr[1];
	delete parr[2];

	return 0;   // 소멸자 3번 호출
}


/*
  출력결과: 이름: sun
            나이: 24
            이름: hong
            나이: 41
            이름: kim
            나이: 37
            이름: sun, 나이: 24
            이름: hong, 나이: 41
            이름: kim, 나이: 37
            call destructor!         
            call destructor!
            call destructor!
*/

