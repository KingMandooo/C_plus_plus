
           우리는 객체의 생성을 목적으로 클래스를 디자인..  '정보은닉'과 '캡슐화'는 좋은 클래스가 되기 위한 최소한의 조건..
             
---------------------------------------------------------         
#include <iostream>
using namespace std;

class Point
{
public:
	int x;  // 조건: x좌표의 범위는 0 이상 100 이하
	int y;  //       y좌표의 범위는 0 이상 100 이하
};

class Rectangle
{
public:
	Point upLeft;
	Point lowRight;

public:
	void ShowRecInfo()
	{
		cout << "좌 상단: " << '[' << upLeft.x << ", ";
		cout << upLeft.y << ']' << endl;
		cout << "우 하단: " << '[' << lowRight.x << ", ";
		cout << lowRight.y << ']' << endl;
	}
};

int main()
{
	Point pos1 = { -2, 4 };           // 🎈🎈 문제1: 좌표의 범위의 조건에 충족하지 않음.. 그러나 오류 또한 발생하지 않음
	Point pos2 = { 5, 9 };
	Rectangle rec = { pos2, pos1 };   // 🎈🎈 문제2: 우하단에 들어가는 좌표값보다 좌상단에 들어가는 좌표값이 더 크다.
	rec.ShowRecInfo();

	return 0;
}

              ✅ 위 코드의 문제 :
                                 - 점의 좌표는 0이상 100이하가 되어야 하는데, 그렇지 못한 Point 객체가 있다.
                                 - 직사각형을 의미하는 Rectangle 객체의 좌 상단 좌표 값이 우 하단 좌표 값보다 크다.
                         
                무엇보다 이 코드는 "프로그래머의 실수에 대한 대책이 하나도 준비되어 있지 않다!" ..
                                   
                
             👉👉👉  이러한 이유로 제한된 방법으로의 접근만 허용을 해서 잘못된 값이 저장되지 않도록 도와야 하고, 
                       또 실수를 했을 때, 실수가 쉽게 발견되도록 해야 한다.
                         
                         
---------------------------------------------------------------------------------
                         
🔷 Point.h

#ifndef __POINT_H_
#define __POINT_H_

class Point
{
private:
	int x;  // x좌표의 범위는 0 이상 100 이하
	int y;  // y좌표의 범위는 0 이상 100 이하

public:
	bool InitMembers(int xpos, int ypos);
	int GetX() const;
	int GetY() const;
	bool SetX(int xpos);
	bool SetY(int ypos);
};

#endif // __POINT_H_

                         
🔷 Point.cpp       

#include <iostream>
#include "Point.h"
using namespace std;

bool Point::InitMembers(int xpos, int ypos)
{
	if (xpos < 0 || ypos < 0)
	{
		cout << "벗어난 범위의 값 전달" << endl;
		return false;
	}

	x = xpos;
	y = ypos;
	return  true;
}

int Point::GetX() const  // const 함수
{
	return x;
}

int Point::GetY() const
{
	return y;
}

bool Point::SetX(int xpos)
{
	if (xpos < 0 || xpos > 100)
	{
		cout << "벗어난 범위의 값 전달" << endl;
		return false;
	}
	x = xpos;
	return true;
}

bool Point::SetY(int ypos)
{
	if (ypos < 0 || ypos > 100)
	{
		cout << "벗어난 범위의 값 전달" << endl;
		return false;
	}
	y = ypos;
	return true;
}

                                       🎈🎈 "멤버변수를 private으로 선언하고, 해당 변수에 접근하는 함수를 별도로 정의해서,
                                             안전한 형태로 멤버변수의 접근을 유도하는 것이 바로 '정보은닉'이며,
                                             이는 좋은 클래스가 되기 위한 기본조건이 된다!!"
                                               
                                               
                                               
          위의 코드에서 int GetX() const;
                        bool SetX(int xpos);
                        int GetY() const;
                        bool SetY(int ypos);
                                                 같은 함수들을 '엑세스 함수(access function)'이라고 한다.
                                                 이들은 멤버변수를 private으로 선언하면서 클래스 외부에서의
                                                 멤버변수 접근을 목적으로 정의되는 함수들이다.
                                                 그러나 이들 함수는 정의되었으나 호출되지 않는 경우도 많다.
                                                 클래스의 정의과정에서 지금 당장은 필요하지 않지만, 필요할 수 있다고 판단되는 함수들도
                                                 멤버에 포함시키는 경우도 많다. 그 대표적인 예가 '엑세스 함수'이다.
                                                  
                                               
🔷 Rectangle.h

#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle
{
private:
	Point upLeft;
	Point lowRight;

public:
	bool InitMembers(const Point& ul, const Point& lr);
	void ShowRecInfo() const;
};

#endif //__RECTANGLE_H_


🔷 Rectangle.cpp

#include <iostream>
#include "헤더2.h"
using namespace std;

bool Rectangle::InitMembers(const Point& ul, const Point& lr)
{
	if (ul.GetX() > lr.GetX() || ul.GetY() > lr.GetY())
	{
		cout << "잘못된 위치정보 전달" << endl;
		return false;
	}
	upLeft = ul;
	lowRight = lr;
	return true;
}

void Rectangle::ShowRecInfo() const
{
	cout << "좌 상단: " << '[' << upLeft.GetX() << ", ";
	cout << upLeft.GetY() << ']' << endl;
	cout << "우 하단: " << '[' << lowRight.GetX() << ", ";
	cout << lowRight.GetY() << ']' << endl << endl;
}


🔷 main.cpp

#include <iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main()
{
	Point pos1;
	if (!pos1.InitMembers(-2, 4))
		cout << "초기화 실패" << endl;
	if (!pos1.InitMembers(2, 4))
		cout << "초기화 실패" << endl;

	Point pos2;
	if (!pos2.InitMembers(5, 9))
		cout << "초기화 실패" << endl;

	Rectangle rec;
	if (!rec.InitMembers(pos2, pos1))
		cout << "직사각형 초기화 실패" << endl;

	if (!rec.InitMembers(pos1, pos2))
		cout << "직사각형 초기화 실패" << endl;

	rec.ShowRecInfo();

	return 0;
}


/*
  출력결과:   벗어난 범위의 값 전달
              초기화 실패
              잘못된 위치정보 전달
              직사각형 초기화 실패
              좌 상단: [2, 4]
              우 하단: [5, 9]
*/
---------------------------------------------------------------------------------
  
🟢 const 함수

int GetX() const;
int GetY() const;
voi ShowRecInfo() const;                🎈🎈 "이 함수 내에서는 멤버변수에 저장된 값을 변경하지 않겠다!"


  
❌ 오류발생 코드 1
  
class SimpleClass
{
private: 
	int num;

public:
	void InitNum(int n)
	{
		num = n;
	}

	int GetNum()          // const를 붙여줘야 오류 발생 안함           
	{
		return num;
	}

	void ShowNum() const                // 🎈🎈 const 함수 내에서는 const가 아닌 함수의 호출이 제한된다..!!
	{
		cout << GetNum() << endl;
	                                  
                                  const 함수는 멤버변수에 저장된 값을 변경하지 않아야 한다.
                                  그러나 GetNum()을 하게 되면 //(물론, 현재 GetNum()은 멤버변수 num의 값에 영향을 미치는 코드는 아니다.)
                                  멤버변수인 num을 마음만 먹으면 어떤 식으로든 변경할 수 있기 때문에 오류가 발생한다.
                                    
                                  따라서 const 함수 내에서는 const가 아닌 함수의 호추링 제한되는 것이다.


❌ 오류발생 코드 2
                                    
class EasyClass
{
private: 
	int num;

public:
	void InitNum(int n)
	{
		num = n;
	}

	int GetNum()       // const 붙여야 오류 발생 안함
	{
		return num;
	}
};

class LiveClass
{
private:
	int num;
public:
	void InitNum(const EasyClass& easy)   // const 참조자를 이용한 것은 const 함수만 호출이 가능하다. 그러나 GetNum()은 const함수가 아니다.
	{
		num = easy.GetNum();
	}
};

                         사실 이것도 너무 당연한 것이다. const 참조자의 값을 일반 멤버함수를 호출함으로써 변경이 가능하면 
                         논리에 모순이 발생하기 때문이다.
                           
                           
                           
                           
                🎈🎈 이렇게 const 선언을 한번 사용하기 시작하면, 그만큼 작성한 코드의 안정성은 높아진다.                           
                           
                           
