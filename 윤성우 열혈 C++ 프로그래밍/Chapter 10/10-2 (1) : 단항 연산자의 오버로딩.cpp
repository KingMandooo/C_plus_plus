
    피연산자가 두 개인 이항 연산자와 피연산자가 한 개인 단항 연산자의 가장 큰 차이점은
    피연산자의 개수이다.
      
    그리고 이에 따른 연산자 오버로딩의 차이점은 매개변수의 개수에서 발견된다.
      
      
      
      ++pos;    
 
      pos.operator++();  // 멤버함수로 오버로딩 된 경우
 
      operator++(pos);   // 전역함수로 오버로딩 된 경우
      
--------------------------------------------------------------------------------------------
      
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
	Point& operator++()
	{
		xpos += 1;
		ypos += 1;
		return *this;
	}
	friend Point& operator--(Point& ref);
};

Point& operator--(Point& ref)
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}

int main()
{
	Point pos(1, 2);
	++pos;
	pos.ShowPosition();
	--pos;
	pos.ShowPosition();

	++(++pos);                // 🎈🎈 ++(pos.operator++());   -->   ++(pos의 참조 값);   -->  (pos의 참조 값).operator++();
	pos.ShowPosition();
	--(--pos);                // 🎈🎈 --(oerator--(pos));   -->   --(pos의 참조 값);   -->   operator--(pos의 참조 값);
	pos.ShowPosition();

	return 0;
}

--------------------------------------------------------------------------------------------
  
🟠 문제 10-2(1)  ❌ 다시풀기
   
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
	/*Point& operator-()
	{
		xpos *= -1;                <-- 🎈🎈 이렇게 하면 pos1의 값 또한 바뀌므로 문제를 틀린 것이다.
		ypos *= -1;
		return *this;
	}*/
	Point operator-()
	{
		Point pos(-xpos, -ypos);
		return pos;
	}
};

int main()
{
	Point pos1(1, 2);
	Point pos2 = -pos1;  // pos1.operator-();  
	pos1.ShowPosition();
	pos2.ShowPosition();

	return 0;
}
  
  
🟠 문제 10-2(2) 

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
	friend Point operator~(const Point& ref);
};

Point operator~(const Point& ref)
{
	Point pos(ref.ypos, ref.xpos);
	return pos;
}

int main()
{
	Point pos1(1, 2);
	Point pos2 = ~pos1;
	pos1.ShowPosition();
	pos2.ShowPosition();

	return 0;
}
