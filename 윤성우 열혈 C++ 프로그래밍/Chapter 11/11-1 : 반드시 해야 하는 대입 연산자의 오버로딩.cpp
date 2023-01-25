  🟢 객체간 대입연산의 비밀: 디폴트 대입 연산자
  
  - 정의하지 않으면 디폴트 복사 생성자가 삽입된다.
  - 디폴트 복사 생성자는 멤버 대 멤버의 복사(얕은 복사)를 진행한다.
  - 생성자 내에서 동적 할당을 한다면, 그리고 깊은 복사가 필요하다면 직접 정의해야 한다.
    
    
  - 정의하지 않으면 디폴트 대입 연산자가 삽입된다.
  - 디폴트 대입 연산자는 멤버 대 멤버의 복사(얕은 복사)를 진행한다.
  - 연산자 내에서 동적 할당을 한다면, 그리고 깊은 복사가 필요하다면 직접 정의해야 한다.
    
                           🎈🎈 디폴트 대입 연산자와 디폴트 복사 생성자는 유사하다.
                                하지만 당연히 차이는 존재한다. 바로 둘의 호출시점이 다르다는 것이다.

#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)    
	{
		cout << "생성자 호출" << endl;
	}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point(Point& ref) : xpos(ref.xpos), ypos(ref.ypos)
	{
		cout << "복사생성자 호출" << endl;
	}
	Point& operator=(Point& ref)          // ✅ cout를 사용한줄을 빼면 디폴트 대입연산자는 이렇게 정의되어있다.
	{
		cout << "대입 연산자 호출" << endl;
		xpos = ref.xpos;
		ypos = ref.ypos;
		return *this;
	}
};                                      

int main()
{
	Point aa(3, 5);           // 🎈🎈 이미 생성 및 초기화가 진행된 객체는 두 객체간의 대입연산 시에는 대입 연산자가 호출된다.
	Point bb(1, 2);
	bb = aa;                  // 🎈🎈 여기서 대입연산자는 오버로딩된 대입연산자이다. 

  // Point cc = aa;         <-- 🎈🎈 이런식으로 되어있다면 여기서는 복사생성자를 호출한다.
                             //      왜냐하면 cc는 생성과 초기화가 진행되지 않았기 때문이다.
	aa.ShowPosition();
	bb.ShowPosition();
                                  // ✅ 	bb = aa;  우리는 이렇게 대입 연산이 가능한 것을보고 
	return 0;                       //     "어라? 동일한 자료형의 두 객체간에 대입연산이 허용되네!" 라고 생각하면 허수다.
}                                 //      이는 단순한 대입연산이 아닌, 대입 연산자를 오버로딩 한 함수의 호출이기 때문이다.
    
/*
  출력결과:   생성자 호출 
              생성자 호출
              대입 연산자 호출
              [3, 5]
              [3, 5]
*/

-----------------------------------------------------------------------------------
  
🟢 디폴트 대입 연산자의 문제점

  --> 이 부분에 대해서는 Chapter 05에서 이미 언급이 되었다.
      그리고 디폴트 대입 연산자도 이와 같은 문제를 야기할 가능성이 있다.
      이 말은 디폴트 대입 연산자도 깊은 복사를 할 수 있도록 정의를 해줘야한다는 것이다.
      
      
#include <iostream>
using namespace std;

class Person
{
private:
	char* name;
	int age;
public:
	Person(char* myname, int myage)
	{
		name = new char[strlen(myname) + 1];
		strcpy(name, myname);
		age = myage;
	}
	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age <<  endl;
	}
	~Person()
	{
		delete[] name;
		cout << "called destructor!" << endl;
	}
};

int main()
{
	Person man1("Lee dong woo", 29);
	Person man2("Yoon ji yul", 22);
	man2 = man1;

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();

	return 0;                              // 🎈🎈 출력결과를 보면 소멸자가 한 번 밖에 호출이 안된 것을 볼 수 있다.
}                                        //       이는 디폴트 대입 연산자가 얕은 복사로 통해 멤버 대 멤버의 복사를 했기 때문이다.
                                         //       즉, 각 객체의 포인터 멤버변수인 name이 같은 공간을 가리키는 상황이 발생하여
                                         //       "Yoon ji yul"를 가지고 있는 메모리가 누수가 발생하는 상황이 일어난다.
/*
  출력결과:   이름: Lee dong woo
              나이: 29
              이름: Lee dong woo
              나이: 29
              called destructor!     
*/


                  Person& operator=(Person& ref)           // ✅ 이를 해결하기 위해서 Person 클래스에 이 코드를 추가해줘야한다.
                  {
                    delete[] name;  // 본래 name이 가리키는 메모리 해제 
                    name = new char[strlen(ref.name) + 1]; // 새로운 알맞는 길이의 메모리 공간 할당
                    strcpy(name, ref.name);  // 메모리 공간에 문자열 복사
                    age = ref.age;
                    return *this;
                  }

-----------------------------------------------------------------------------------
  
🟢 상속 구조에서의 대입 연산자 호출
