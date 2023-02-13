
   함수 템플릿을 특수화하는 이유는 특정 자료형에 대해서 구분이 되는 다른 행동을 보이기 위해서이다.
   
   마찬가지로 "클래스 템플릿을 특수화하는 이유는 특정 자료형을 기반으로 생성된 객체에 대해, 구분이 되는 다른 행동양식을 적용하기 위해서이다."
  
template <typename T>
class SoSimple
{
  public:
    T SimpleFunc(T num) { ... }
}

template <>                 //🎈🎈 위의 클래스 템플릿을 기반으로 자료형 int에 대해 특수화 한 템플릿 클래스
class SoSimple <int>
{
  public:
    int SimpleFunc(int num) { ... }
}

---------------------------------------------------------------------------

#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class Point
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

template <typename T>
class SimpleDataWrapper
{
private:
	T mdata;
public:
	SimpleDataWrapper(T data) : mdata(data) {}
	void ShowDataInfo()
	{
		cout << "Data: " << mdata << endl;
	}
};
 
template <>                             //🎈🎈 클래스 템플릿 특수화
class SimpleDataWrapper <char*>
{
private:
	char* mdata;
public:
	SimpleDataWrapper(const char* data)
	{
		mdata = new char[strlen(data) + 1];
		strcpy(mdata, data);
	}
	void ShowDataInfo()
	{
		cout << "String: " << mdata << endl;
		cout << "Length: " << strlen(mdata) << endl;
	}
	~SimpleDataWrapper() { delete[] mdata; }
};
  
template <>                             //🎈🎈 클래스 템플릿 특수화
class SimpleDataWrapper <Point<int>>
{
private:
	Point<int> mdata;
public:
	SimpleDataWrapper(int x, int y) : mdata(x, y) {}
	void ShowDataInfo()
	{
		mdata.ShowPosition();
	}
};

int main()
{
	SimpleDataWrapper<int> iwrap(170);
	iwrap.ShowDataInfo();
	SimpleDataWrapper<char*> swrap("Class Template Specialization");
	swrap.ShowDataInfo();
	SimpleDataWrapper<Point<int>> poswrap(3, 7);
	poswrap.ShowDataInfo();
	return 0;
}


/*
실행결과:   Data: 170
            String: Class Template Specialization
            Length: 29
            [3, 7]
*/

---------------------------------------------------------------------------

🟢 클래스 템플릿의 부분 특수화 

#include <iostream>
using namespace std;

template <class T1, class T2>
class MySimple
{
public:
	void WhoAreYou()
	{
		cout << "size of T1: " << sizeof(T1) << endl;
		cout << "size of T2: " << sizeof(T2) << endl;
		cout << "<typename T1, typename T2>" << endl;
	}
};

template <>
class MySimple<int, double>
{
public:
	void WhoAreYou()
	{
		cout << "size of int: " << sizeof(int) << endl;
		cout << "size of double: " << sizeof(double) << endl;
		cout << "<int, double>" << endl;
	}
};

template <class T1>
class MySimple<T1, double>
{
public:
	void WhoAreYou()
	{
		cout << "size of T1: " << sizeof(T1) << endl;
		cout << "size of double: " << sizeof(double) << endl;
		cout << "<T1, double>" << endl;
	}
};

int main()
{
	MySimple<char, double> obj1;
	obj1.WhoAreYou();

	MySimple<int, long> obj2;
	obj2.WhoAreYou();

	MySimple<int, double> obj3;     // 🎈🎈  MySimple<int, double> 클래스 템플릿이 존재하므로 MySimple<T1, double> 는 무시된다.
	obj3.WhoAreYou();               //       이로써 전체 특수화가 부분 특수화보다 우선시 된다는 것을 알 수 있다.

	return 0;
}


/*
실행결과:   size of T1: 1
            size of double: 8
            <T1, double>
            size of T1: 4
            size of T2: 4
            <typename T1, typename T2>
            size of int: 4
            size of double: 8
            <int, double>
*/

