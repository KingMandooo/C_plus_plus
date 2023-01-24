

  함수를 오버로딩하면 이름은 하나이지만 기능은 여러 가지인 함수를 만들어낼 수 있다.
    
  마찬가지로 연산자도 오버로딩을 하여 기존에 존재하던 연산자의 기본 기능 이외에 다른 기능을 추가할 수 있다 !!
    

-----------------------------------------------------------------------------------------------------------------

🟢 operator+ 라는 이름의 함수

   --> 연산자 오버로딩이란 C++이 우리에게 제시하는 하나의 약속에 지나지 않는다.
  
       'operator' 키워드와 '연산자'를 묶어서 함수의 이름을 정의하면, 함수의 이름을 이용한 함수의 호출뿐만 아니라,
       연산자를 이용한 함수의 호출도 허용해 주겠다는 것이다.
         
       🎈🎈 "연산자를 이용한 함수의 호출을 허용해 주겠다" 는 말이 꽤나 핵심이다.
         
            아래 코드에서 Point pos3 = pos1 + pos2; 이런 문장이 있다.
             
            즉, 연산자를 이용하여 함수를 호출한 것이다.
              
            pos1 + pos2  라는 문장을  pos1.operator+(pos2) 라는 문장으로 바꿔서 해석해준다.


#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point operator+(const Point& ref)     // 🎈🎈 연산자 오버로딩  
	{ 
		Point pos(xpos + ref.xpos, ypos + ref.ypos); // ✅ 이 함수를 꾸미는 건 내가 마음대로 하는거임 만약 내가 
		return pos;                                  //     41번 줄을 Point pos(xpos - ref.xpos, ypos - ref.ypos);  이렇게
	}                                              //     뺄셈으로 구현하면 연산자 '+'가 객체의 멤버를 빼는 걸로 정의 되는 거임.
};

int main()
{                                        //   ✅ pos1.operator+(pos2); 와 pos1 + pos2; 는 완전히 동일한 문장이다. 
	Point pos1(3, 4);                      //       pos1 + pos2;이 pos1.operator+(pos2); 로 해석되어서 컴파일 된다.
	Point pos2(10, 20);
	Point pos3 = pos1.operator+(pos2);
	// Point pos3 = pos1 + pos2;      <--  🎈🎈 객체도 기본 자료형 변수처럼 덧셈, 뺄셈, 혹은 곱셈과 같은 연산들을 가능하게한다. 
                                           // 객체도 완벽히 기본 자료형 데이터처럼 취급할 수 있다 !!
  
	pos1.ShowPosition();         // [3, 4]   출력
	pos2.ShowPosition();         // [10, 20] 출력         
	pos3.ShowPosition();         // [13, 24] 출력

	return 0;
}

-----------------------------------------------------------------------------------------------------------------

🟢 연산자를 오버로딩 하는 두 가지 방법

   - 멤버함수에 의한 연산자 오버로딩       // pos1.operator+(pos2);
   
   - 전역함수에 의한 연산자 오버로딩       // operator+(pos1, pos2);
   
     참고로, 동일한 자료형을 대상으로 + 연산자를 전역함수 기반으로, 그리고 멤버함수 기반으로
     동시에 오버로딩 할 경우, 멤버함수 기반으로 오버로딩 된 함수가 전역함수 기반으로 오버로딩 된
     함수보다 우선시 되어 호출된다.
     (이러한 상황은 가급적 만들지 않는 게 좋다.)
  
  
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) 
	{}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	friend Point operator+(const Point& pos1, const Point& pos2); // 🎈🎈 friend 키워드로 인하여 operator+ 함수 내에서는 Point 클래스의 private영역에 접근 가능.
};

Point operator+(const Point& pos1, const Point& pos2)      // 🎈🎈 전역함수 operator+ 선언
{
	Point pos(pos1.xpos + pos2.xpos, pos1.ypos + pos2.ypos);
	return pos;
}

int main()
{
	Point pos1(3, 4);
	Point pos2(10, 20);
	//Point pos3 = pos1.operator+(pos2);
	Point pos3 = pos1 + pos2;

	pos1.ShowPosition();
	pos2.ShowPosition();
	pos3.ShowPosition();

	return 0;
}

-----------------------------------------------------------------------------------------------------------------
  
🟠 문제 10-1(1)
  
💙 전역함수 기반으로 오버로딩 💙
💙 멤버 별 - 연산의 결과를 담은 Point 객체 반환 💙

#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) 
	{}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	friend Point operator-(const Point& ref1, const Point& ref2);
};

Point operator-(const Point& ref1, const Point& ref2)
{
	Point pos(ref1.xpos - ref2.xpos, ref1.ypos - ref2.ypos);
	return pos;
}

int main()
{
	Point pos1(3, 4);
	Point pos2(10, 20);
	//Point pos3 = pos1 - pos2;
	Point pos3 = operator-(pos1, pos2);

	pos1.ShowPosition();
	pos2.ShowPosition();
	pos3.ShowPosition();

	return 0;
}


🟠 문제 10-1(2)
  
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) 
	{}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point& operator+=(const Point& ref)
	{
		xpos += ref.xpos;
		ypos += ref.ypos;

		return *this;
	}
	Point& operator-=(const Point& ref)
	{
		xpos -= ref.xpos;
		ypos -= ref.ypos;

		return *this;
	}
};

int main()
{
	Point pos1(3, 4);
	Point pos2(10, 20);

	(pos1 += pos2).ShowPosition();    // 13, 24
	(pos1 -= pos2).ShowPosition();    // 3, 4

	return 0;
}


🟠 문제 10-1(3)
  
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) 
	{}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	friend bool operator==(const Point& ref1, const Point& ref2);
	friend bool operator!=(const Point& ref1, const Point& ref2);
};

bool operator==(const Point& ref1, const Point& ref2)
{
	if (ref1.xpos == ref2.xpos && ref1.ypos == ref2.ypos)
		return true;
	else
		return false;
}

bool operator!=(const Point& ref1, const Point& ref2)
{
	return (!(ref1 == ref2));          // 🎈🎈 이 생각은 못함...
}

int main()
{
	Point pos1(10, 20);
	Point pos2(10, 20);

	if (pos1 == pos2)
		cout << "같다" << endl;
	else
		cout << "다르다" << endl;

	if (pos1 != pos2)
		cout << "다르다" << endl;
	else
		cout << "같다" << endl;

	return 0;
}
