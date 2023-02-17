#ifndef __BOUND_CHECK_ARRAY_H__
#define __BOUND_CHECK_ARRAY_H__

template <typename T>
class BoundCheckArray
{
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

#endif // !__BOUND_CHECK_ARRAY_H__
