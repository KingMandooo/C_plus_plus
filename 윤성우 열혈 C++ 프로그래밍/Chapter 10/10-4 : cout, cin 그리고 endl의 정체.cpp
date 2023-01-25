🟢 cout와 endl 이해하기

#include <iostream>
namespace mystd
{
	using namespace std;

	class ostream
	{
	public:
		void operator<<(char* str)
		{
			printf("%s", str);
		}
		void operator<< (char str)
		{
			printf("%c", str);
		}
		void operator<< (int num)
		{
			printf("%d", num);
		}
		void operator<< (double e)
		{ 
			printf("%g", e);  // %g: 실수형 자동출력
		}
		void operator<< (ostream& (*fp)(ostream& ostm))   // <-- ✅ Q. 도대체 이건 뭘까?? (아래에 질문에 대한 답있음)
		{
			fp(*this);
		}
	};

	ostream& endl(ostream& ostm)                 
	{
		ostm << '\n';
		fflush(stdout);
		return ostm;
	}

	ostream cout; // cout 객체생성
}

int main()
{
	using mystd::cout;
	using mystd::endl;

	cout << "Simple String";  // cout.operator<<("Simple String");
	cout << endl;             // cout.operator<<(endl);
	cout << 3.14;
	cout << endl;
	cout << 123;
	endl(cout);

}
                                 ✅ A. 아래의 함수에서 받는 매개변수는 ostream& 형의 함수포인터이다.

                                        void operator<< (ostream& (*fp)(ostream& ostm))   
                                        {
                                          fp(*this);
                                        }

                                      이 함수를 호출할 때 cout << endl; 를 사용한다.
                                      그러면 ostream& (*fp)(ostream& ostm) = endl; 과 같은 식으로 매개변수가 전달이 된다.
                                        
                                      이는 함수포인터 fp가 endl()함수를 가리키게 되는 것이다.
                                        
                                      그래서 fp(*this); 를 하면 endl()함수에 자기 객체를 전달하고 endl()에서 
                                      '\n'을 출력하는 것이다.
                                        
            
              위의 코드는 cout << 123 << endl << 3.14 << endl; 과 같은 형식으로 출력은 불가하다.
              이를 해결하기 위해서 아래와 같이 수정해보자.

------------------------------------------------------------------------------
                                        
#include <iostream>
namespace mystd
{
	using namespace std;

	class ostream
	{
	public:
		ostream& operator<<(char* str)
		{
			printf("%s", str);
			return *this;                  // 🎈🎈 함수의 반환형을 수정해주고 return *this 추가해주었다.
		} 
		ostream& operator<< (char str)
		{
			printf("%c", str);
			return *this;
		}
		ostream& operator<< (int num)
		{
			printf("%d", num);
			return *this;
		}
		ostream& operator<< (double e)
		{ 
			printf("%g", e);  // %g: 실수형 자동출력
			return *this;
		}
		ostream& operator<< (ostream& (*fp)(ostream& ostm))
		{
			return fp(*this);
		}
	};

	ostream& endl(ostream& ostm)
	{
		ostm << '\n';
		fflush(stdout);
		return ostm;
	}

	ostream cout; // cout 객체생성
}

int main()
{
	using mystd::cout;
	using mystd::endl;

	cout << 3 << endl << 6.14 << endl;
}

------------------------------------------------------------------------------
  
🟢 <<, >> 연산자의 오버로딩

int main()
{
  Point pos(3, 4);
  cout << pos << endl;  // [3, 4] 출력     <-- 이런식으로 연산이 가능하게 하고자 하려면 어떻게 해야할까?
}
           
                   - cout는 ostream 클래스의 객체이다.
                     
                   - ostream은 이름공간 std 안에 선언되어 있으며, 이의 사용을 위해서는 헤더파일 <iostream>을 포함해야 한다.
                     
                   
                   두 가지 방법이 있을 것이다. 멤버함수의 형태 혹은 전역함수의 형태 이렇게 말이다.
                     
                   cout.ostream<<(pos);     <--  🎈🎈 멤버함수에 의한 방법은 cout 객체의 멤버함수를 하나 추가해야한다.
                                                      따라서 ostream 클래스를 수정해야하므로 이는 불가능한 방법이다.

                   ostream<<(cout, pos):    <--  그렇다면 이 방법을 채택..!!


                     
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
	friend ostream& operator<<(ostream&, const Point&);
};

ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}

int main()
{
	Point pos1(1, 3);
	cout << pos1;           // cout.operator(cout, pos1);
	Point pos2(101, 303);
	cout << pos2 << endl;  // ✅ ostream& operator<<(ostream& os, const Point& pos); 함수의 반환형이 ostream& 이어야 이렇게 객체를 반환함으로써 
                         //     연속적으로 함수를 호출할 수 있다.
	return 0;
}
      
------------------------------------------------------------------------------

🟠 문제 10-3
	
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
	friend ostream& operator<<(ostream&, const Point&);
	friend istream& operator >>(istream&, Point&);
};

ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}

istream& operator>>(istream& is, Point& pos)
{
	is >> pos.xpos >> pos.ypos;
	return is;
}

int main()
{
	Point pos1(1, 3);
	cout << "x, y 좌표 순으로 입력: ";
	cin >> pos1;
	cout << pos1;

	Point pos2(101, 303);
	cout << "x, y 좌표 순으로 입력: ";
	cin >> pos2;
	cout << pos2;

	return 0;
}
