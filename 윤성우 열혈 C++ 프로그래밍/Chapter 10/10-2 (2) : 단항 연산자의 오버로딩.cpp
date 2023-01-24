🟢 전위증가와 후의증가의 구분

    ++pos   -->    pos.operator++();
    pos++   -->    pos.operator++(int);


    --pos   -->    pos.operator--();
    pos--   -->    pos.operator--(int);

   🎈🎈 int는 단지 후위연산을 구분하기 위한 목적으로 선택된 것일 뿐,
        int형 데이터를 인자로 전달하라는 뜻이 아니다.

-------------------------------------------------------------------------          
          
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
	const Point operator++(int)
	{
		const Point retobj(xpos, ypos);          // 🎈🎈 함수 내에서 retobj의 변경을 막기위해 const 객체로 선언
		xpos += 1;                               //      "const 함수 내에서는 const 함수의 호출만 허용하도록 제한한다!"
		ypos += 1;                                
		return retobj;
	}
	friend Point& operator--(Point& ref);
	friend const Point operator--(Point& ref, int);
};

Point& operator--(Point& ref)
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}

const Point operator--(Point& ref, int)
{
	const Point retobj(ref);
	ref.xpos -= 1;
	ref.ypos -= 1;
	return retobj;
}


int main()
{
	Point pos(3, 5);
	Point cpy;
	cpy = pos--;          // cpy = operator--(pos); 이거와 다름, 이건 전위 연산자 함수호출
	cpy.ShowPosition();
	pos.ShowPosition();         // 🎈🎈 출력결과를 잘보면 이 코드는 후위 연산자를 완벽히 구현했다고 볼 수 있다.
                              //       cpy = pos--; 를 하면 cpy의 값에 pos가 들어간다음에, pos의 멤버변수 값이 감소한 것을 볼 수 있다.
	cpy = pos++;
	cpy.ShowPosition();
	pos.ShowPosition();

	return 0;
}


/*
출력결과: [3, 5]
          [2, 4]
          [2, 4]
          [3, 5]
*/
