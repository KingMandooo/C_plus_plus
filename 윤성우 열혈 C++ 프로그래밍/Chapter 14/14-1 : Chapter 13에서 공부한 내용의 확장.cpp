template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;
};


                            위와 아래와 같은 두 개의 클래스가 있다.


template <typename T>                         //🎈🎈 BoundCheckArray<int> iarr(50); 이렇게 저장이 가능하다.
class BoundCheckArray                         //     BoundCheckArray<Point<int>> oarr(50); 이렇게 Point<int> 템플릿 클래스의 객체를 저장할 수도 있다.
{                                             //     BoundCheckArray<Point<int>*> oparr(50); 이렇게 Point<int>형 포인터 객체를 저장할 수도 있다.
private:
	T* arr;
	int arrlen;

	BoundCheckArray(const BoundCheckArray& copy) {}
	BoundCheckArray& operator= (const BoundCheckArray& ref) {}
public:
	BoundCheckArray(int len = 100) : arrlen(len)
	{
		arr = new T[len];
	}
	T& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	T operator[] (int idx) const      
	{                                   
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	T GetArrLen() const { return arrlen; }
	~BoundCheckArray() { delete[] arr; }
};

--------------------------------------------------------------------
  
template <typename T>
class Point
{
private:
	T xpos, ypos;
public:
	Point(T x = 0, T y = 0);
	void ShowPosition() const;

  //✅ 특정 템플릿 클래스의 객체를 인자로 받는 일반함수의 정의와 friend 선언
	friend Point<int> operator+(const Point<int>&, const Point<int>&);
	friend ostream& operator<<(ostream& os, const Point<int>& pos);
};


           🎈🎈 템플릿과 관련해서 무엇이 되고, 무엇이 안 되는지를 아는 것도 중요하지만,
                템플릿 관련 코드를 보면서 이것이 의미하는 바가 무엇인지를 유추하는 것도 중요하다.
                  
