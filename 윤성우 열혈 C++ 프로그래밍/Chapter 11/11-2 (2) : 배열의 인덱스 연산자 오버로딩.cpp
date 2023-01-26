🟢 객체의 저장을 위한 배열 클래스의 정의

  앞서 보인 예제들은 기본자료형 대상의 배열 클래스였다.
  이번에는 객체 대상의 배열 클래스를 공부해보자.
  
  
  
     이 두 가지 형태로 정의해보겠다.
  
              - Point 객체의 주소 값을 저장하는 배열 기반의 클래스
              - Point 객체를 저장하는 배열 기반의 클래스 
  
---------------------------------------------------------------------

💙 Point 객체를 저장하는 배열 기반의 클래스 💙
              
#include <iostream>
#include <cstdlib>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}
	friend ostream& operator<<(ostream& os, const Point& pos);
};

ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}

class BoundCheckPointArray
{
private:
	Point* arr;
	int arrlen;
	BoundCheckPointArray(const BoundCheckPointArray& copy) {}
	BoundCheckPointArray operator= (const BoundCheckPointArray& ref) {}
public:
	BoundCheckPointArray(int len) : arrlen(len)
	{
		arr = new Point[len];
	}
	Point& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	Point& operator[] (int idx) const
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int GetArrLen() const { return arrlen; }
	~BoundCheckPointArray() { delete[] arr; }
};

int main()
{
	BoundCheckPointArray arr(3);
	arr[0] = Point(3, 4);          // ✅ arr.operator[](0)의 반환값이 Point 객체이다. 따라서 "(반환된 Point 객체) = Point(3, 4);"
	arr[1] = Point(5, 6);          //    이렇게 풀어보면 당연히 Point 클래스에서 디폴트 대입연산자가 실행된다.
	arr[2] = Point(7, 8);          //    이는 두 객체간의 멤버 대 멤버의 복사가 일어난다.

	for (int i = 0; i < arr.GetArrLen(); i++)
		cout << arr[i];
}


💙 Point 객체의 주소 값을 저장하는 배열 기반의 클래스 💙

#include <iostream>
#include <cstdlib>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}
	friend ostream& operator<<(ostream& os, const Point& pos);
};

ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}

typedef Point* POINT_PTR;

class BoundCheckPointArray
{
private:
	POINT_PTR* arr;    // 이중포인터
	int arrlen;
	BoundCheckPointArray(const BoundCheckPointArray& copy) {}
	BoundCheckPointArray operator= (const BoundCheckPointArray& ref) {}
public:
	BoundCheckPointArray(int len) : arrlen(len)
	{
		arr = new POINT_PTR[len];
	}
	POINT_PTR& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	POINT_PTR& operator[] (int idx) const
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];                     // 주소값으로 반환
	}
	int GetArrLen() const { return arrlen; }
	~BoundCheckPointArray() { delete[] arr; }
};

int main()
{
	BoundCheckPointArray arr(3);
	arr[0] = new Point(3, 4);      // 포인터이므로 주소값을 가리켜야 해서 
	arr[1] = new Point(5, 6);
	arr[2] = new Point(7, 8);

	for (int i = 0; i < arr.GetArrLen(); i++)
		cout << *(arr[i]);

	delete arr[0];
	delete arr[1];
	delete arr[2];
	return 0;
}

---------------------------------------------------------------------

🟠 문제 11-2(1)
  
#include <iostream>
#include <cstdlib>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y) {}
	friend ostream& operator<<(ostream& os, const Point& pos);
	friend ostream& operator<<(ostream& os, const Point* pos);
};

ostream& operator<<(ostream& os, const Point& pos)
{
	os << '[' << pos.xpos << ", " << pos.ypos << ']' << endl;
	return os;
}
ostream& operator<<(ostream& os, const Point* pos)
{
	os << '[' << pos->xpos << ", " << pos->ypos << ']' << endl;
	return os;
}

typedef Point* POINT_PTR;

class BoundCheckPointArray
{
private:
	POINT_PTR* arr;
	int arrlen;
	BoundCheckPointArray(const BoundCheckPointArray& copy) {}
	BoundCheckPointArray operator= (const BoundCheckPointArray& ref) {}
public:
	BoundCheckPointArray(int len) : arrlen(len)
	{
		arr = new POINT_PTR[len];
	}
	POINT_PTR& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	POINT_PTR& operator[] (int idx) const
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int GetArrLen() const { return arrlen; }
	~BoundCheckPointArray() { delete[] arr; }
};

int main()
{
	BoundCheckPointArray arr(3);
	arr[0] = new Point(3, 4);
	arr[1] = new Point(5, 6);
	arr[2] = new Point(7, 8);

	for (int i = 0; i < arr.GetArrLen(); i++)
		cout << arr[i];

	delete arr[0];
	delete arr[1];
	delete arr[2];
	return 0;
}


🟠 문제 11-2(2)   개어렵네???
  
#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;

	BoundCheckIntArray(const BoundCheckIntArray& copy) {}
	BoundCheckIntArray operator= (const BoundCheckIntArray& ref) {}
public:
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx) const
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int& operator[] (int idx) 
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int GetArrLen() const { return arrlen; }
	~BoundCheckIntArray() { delete[] arr; }
};

typedef BoundCheckIntArray* BoundCheckIntArrayPtr;

class BoundCheck2DIntArray
{
private:
	BoundCheckIntArray** arr;
	int arrlen;
	BoundCheck2DIntArray(const BoundCheck2DIntArray& arr) {}
	BoundCheck2DIntArray& operator=(const BoundCheck2DIntArray& arr) {}

public:
	BoundCheck2DIntArray(int col, int row) : arrlen(col)
	{
		arr = new BoundCheckIntArrayPtr[col];
		for (int i = 0; i < col; i++)
			arr[i] = new BoundCheckIntArray(row);
	}
	BoundCheckIntArray& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of bound exception" << endl;
			exit(1);
		}
		return *(arr[idx]);
	}
	~BoundCheck2DIntArray()
	{
		for (int i = 0; i < arrlen; i++)
			delete arr[i];
		delete[] arr;
	}
};

int main()
{
	BoundCheck2DIntArray arr2d(3, 4);

	for (int n = 0; n < 3; n++)
		for (int m = 0; m < 4; m++)
			arr2d[n][m] = n + m;
	       // (arr2d.operator[](n))[m];
	for (int n = 0; n < 3; n++)
	{
		for (int m = 0; m < 4; m++)
			cout << arr2d[n][m] << ' ';
		cout << endl;
	}
	 
	return 0;
}
