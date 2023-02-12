
함수를 템플릿으로 정의했듯이 클래스도 템플릿으로 정의가 가능하다. 그리고 이렇게 정의된 템플릿을 가리켜
'클래스 템플릿(Class Template)'이라고 하며, 이를 기반으로 컴파일러가 만들어 내는 클래스를 가리켜
'템플릿 클래스(Template Class)'라 한다.
  
---------------------------------------------------
  
#include <iostream>
using namespace std;

template <typename T>
class Point                  //🎈🎈 이렇게 컴파일러는 '클래스 템플릿'을 기반으로 '템플릿 클래스'를 만들어낸다.
{
private:
	T xpos, ypos;
public:
	Point(T x, T y) : xpos(x), ypos(y) {}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
};

int main()          
{
	Point<int> pos1(3, 4);              // Point<int> 템플릿 클래스
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);       // Point<double> 템플릿 클래스
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');         // Point<char> 템플릿 클래스
	pos3.ShowPosition();
	return 0;
}  
          //✅ Q. 템플릿 함수를 호출할 때와 마찬가지로 템플릿 클래스의 객체를 생성할 때도 <int>, <double>, <char>과 같은 자료형 정보를 생략할 수 있나요?
 
          //✅ A. 아니요.
 
---------------------------------------------------
 
🟢 클래스 템플릿의 선언과 정의의 분리

#include <iostream>
using namespace std;

template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;
};

template <typename T>                             //🎈🎈 꼭 template <typename T> 을 빼먹지 않도록 주의하자!!
Point<T>::Point(T x, T y) : xpos(x), ypos(y) {}

template <typename T>
void Point<T>::ShowPosition() const
{
	cout << '[' << xpos << ", " << ypos << ']' << endl;
}

int main()
{
	Point<int> pos1(3, 4);
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');
	pos3.ShowPosition();
	return 0;
}

---------------------------------------------------
 
🟢 클래스 템플릿의 파일 분할

💙 PointTemplate.h 💙
#ifndef __POINT_TEMPLATE_H_
#define __POINT_TEMPLATE_H_

template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;
};
#endif // !__POINT_TEMPLATE_H_


💙 PointTemplate.cpp 💙
#include <iostream>
#include "PointTemplate.h"
using namespace std;

template <typename T>
Point<T>::Point(T x, T y) : xpos(x), ypos(y) {}

template <typename T>
void Point<T>::ShowPosition() const
{
	cout << '[' << xpos << ", " << ypos << ']' << endl;
}


💙 PointMain.cpp 💙
#include <iostream>
#include "PointTemplate.h"
#include "PointTemplate.cpp"       // ✅ Q. 여기서 왜 PointTemplate.cpp 를 추가해준걸까????? (대답은 아래)
using namespace std;

int main()
{
	Point<int> pos1(3, 4);
	pos1.ShowPosition();

	Point<double> pos2(2.4, 3.6);
	pos2.ShowPosition();

	Point<char> pos3('P', 'F');
	pos3.ShowPosition();
	return 0;
}

      ✅ A. 위의 질문을 더 명확히 하자면 
            * 왜 템플릿 클래스의 파일 분할 방법과 일반 클래스의 파일 분할 방법은 다를까?
            * 왜 템플릿 클래스는 일반적인 클래스처럼 파일을 헤더파일과 소스파일(cpp)로 분할할 수 없을까?
        
           이렇게 정리할 수 있을 것이다.
           그렇다면 도대체 일반 클래스와 템플릿 클래스는 무슨 차이를 가지고 있는 걸까?
           (블로그를 통해 찾아봤다)
        
         * 템플릿 클래스를 헤더파일에서 선언하고, cpp파일에서 구현한다면 링크 오류를 만나게 된다.
           일반 함수와는 다르게 템플릿은 컴파일 시점에 인스턴스가 생성되어야 한다.
           왜냐하면 일반 함수는 컴파일 시점에 정의를 볼 수 없어도, 함수가 호출 되면 어떤 함수가 호출되었는지 링킹 과정에서 파악할 수 있다. 
           하지만 템플릿은 호출 될 때마다 그 정의를 확인해야 정확한 코드를 작성할 수 있다.
           즉, 사용되는 개별 번역단위(translation unit)마다 그 정의를 포함시켜줘야 하는 것이다.
           만약 A라는 클래스 템플릿의 헤더파일을 만들고, cpp파일을 만들어 정의 한다면 이와는 개별 번역단위인 main cpp파일에서는 
           링크 과정에서 A의 인스턴스를 생성할 때 그 정의를 확인할 수 없어 오류가 발생하는 것이다.
        
         * 일반적인 클래스나 함수의 경우 별도의 파일에서 컴파일 과정을 통해서 오브젝트 파일을 만들고 이것을 가지고 링크가 되지만, 
           함수 템플릿이나 클래스 템플릿은 컴파일 과정에서 해당 문법 체크과정 외에 실제 사용 시 넘겨진 
           타입 파라미터를 이용해서 구체화(instantiation)과정을 거치게 되는데 
           이 때 사용되는 모든 정의 부분이 컴파일되는 파일에서 모두 #include 등을 통해 명시적으로 보여야 하기 때문입니다.
             
           출처: https://gnaseel.tistory.com/25
                 https://blog.naver.com/agbird/120013984128

           결론은 클래스 템플릿과 함수는 컴파일 과정에서 정의와 선언을 다 알아야지만 오류가 발생하지 않는다.
             
           🎈🎈 따라서 .h 파일에서 선언과 정의를 모두 해주던가, main 파일에 템플릿 클래스의 정의를 포함하는 .cpp 파일을
                include 해주는 방법이 있겠다.
             
-------------------------------------------------------
		   
배열 클래스의 템플릿화 <-- 이 부분이 남았는데 내가 아직 배열 클래스를 명확히 이해하지 못했다.
		   
고로 우선 책으로만 읽었다.
		   
		   
