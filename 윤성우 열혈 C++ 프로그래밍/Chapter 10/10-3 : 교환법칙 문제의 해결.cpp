 
        A + B = B + A   <-- 교환법칙
        
---------------------------------------------------------------------

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
	Point operator*(int times)
	{
		Point pos(xpos * times, ypos * times);
		return pos;
	}
};                             

int main()
{
	Point pos(1, 2);  
	Point cpy;                           
	
	cpy = pos * 3;         // pos.operator(3); 
	cpy.ShowPosition();

	cpy = pos * 3 * 2;     // pos.operator(6);
	cpy.ShowPosition();

	return 0;
}

                         🎈🎈 위의 코드에서 문제는 곱셈의 교환법칙이 성립하지 않는다는 것이다.
                         
                              pos * 3 은 pos.operator(3); 으로 함수호출이 진행된다.
                              그러나 만약 
                              3 * pos라고 한다면..???   3.operator(pos) 이런식으로 함수가 호출이 된다.
                              이는 당연히 오류가 발생한다.
                            
                              그렇다면 이를 해결하기 위해서는 어떻게 코드를 설계해야할까?
                           
                           
                           
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
	Point operator*(int times)
	{
		Point pos(xpos * times, ypos * times);
		return pos;
	}
};

Point operator*(int times, Point& ref)                // 🎈🎈 cpy = 3 * pos; 형식의 곱셈연산이 가능 하려면,
{                                                     //       전역함수의 형태로 곱셈 연산자를 오버로딩 하는 수 밖에 없다.
	return ref * times;  // ref.operator*(times);
}

int main()
{
	Point pos(1, 2);
	Point cpy;
	
	cpy = 3 * pos;           // operator*(3, pos);
	cpy.ShowPosition();

	cpy = 2 * pos * 3;       // operator*(2, pos);   -->   (pos의 참조자).operator*(3);
	cpy.ShowPosition();

	return 0;
}
                         
