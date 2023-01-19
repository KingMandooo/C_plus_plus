🟢 객체 포인터 변수 : 객체의 주소 값을 저장하는 포인터 변수


  Person* ptr;         // 포인터 변수 선언
  ptr = new Person();  // 포인터 변수의 객체 참조


  🎈🎈 Person형 포인터는 Person 객체뿐만 아니라, Person을 상속하는 유도 클래스의 객체도 가리킬 수 있다.
    
  
  class Studnet : public Person
  {
     ....
  };

  Person* ptr = new Student();    // Person형 포인터가 Student 객체를 가리킨다.



  class PartTimeStudent : public Student
  {
     ....
  };

  Person* ptr1 = new PartTimeStudent();     // Person형 포인터가 PartTimeStudent 객체를 가리킨다.
  Student* ptr2 = new PartTimeStudent();    // Studnet형 포인터가 PartTimeStudent 객체를 가리킨다.

  "C++에서, AAA형 포인터 변수는 AAA 객체 또는 AAA를 직접 혹은 간접적으로 상속하는 모든 객체를 가리킬 수 있다.(객체의 주소 값을 저장할 수 있다)."
    
                                                           // 🎈🎈 당연히 포인터 변수에는 주소값이 저장되어야 하니까,
                                                           //       Person* ptr = new Studnet(); 에서 ptr에는 Studnet 객체의 주소값이 저장되겠지??

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
	Person* ptr1 = new Student();                          // 학생은 사람이다.         학생은 사람의 일종이다.
	Person* ptr2 = new PartTimeStudent();                  // 근로학생은 사람이다.     근로학생은 사람의 일종이다.
	Student* ptr3 = new PartTimeStudent();                 // 근로학생은 학생이다.     근로학생은 학생의 일종이다.

	ptr1->Sleep();                                 // 🎈🎈  Student와 PartTimeStudent 객체를 Person 객체의 일종으로 간주한다.
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
  
	//int Add()   // 기초클래스 BB의 Add() 함수 재정의 (override)
	//{
	//	return a + b;
	//}
  
	int Add(int c)            // <-- 🎈🎈 이 부분이 주석처리가 되어있으면  cout << aa.Add() << endl; 이 문장이 오류가 안뜸
	{                            
		return a + b + c;      // ✅ A. 이러면 결론이 "오버로딩이든 오버라이딩이든 유도 클래스와 기초 클래스의 함수가 겹치는 상황에서는
	}                              //        기초클래스의 함수를 호출하려면 BB:: 와 같은 식으로 명시를 해줘야한다."
};
 
int main()
{
	AA aa(3, 5, 7, 8);
 	BB* bb = new AA(1, 2, 3, 4);   // 🎈🎈 BB 객체가 유도클래스 AA의 객체 저장
  
	cout << aa.Add() << endl;  // <-- ✅ Q. 여기서 오류가 나는게 이해가 안되네? (Answer 위에)
  	cout << aa.BB::Add() << endl;             // aa.num1 = 7 
	cout << bb->Add() << endl;                // aa.num2 = 8    이렇게 할당해줬는데
                                                  // aa.Add()는 기초클래스 BB에 저장되어있기 때문에
	delete bb;                                // aa.num1 + aa.num2 값이 반환되어야 하는게 아닌가?
	return 0;                                 // 왜 AA 클래스에 정의되어있는 Add() 함수에만 기준이 맞춰지지?
}                                                
 						 
