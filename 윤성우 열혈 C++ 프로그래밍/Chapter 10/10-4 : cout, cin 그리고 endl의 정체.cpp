π’ coutμ endl μ΄ν΄νκΈ°

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
			printf("%g", e);  // %g: μ€μν μλμΆλ ₯
		}
		void operator<< (ostream& (*fp)(ostream& ostm))   // <-- β Q. λλμ²΄ μ΄κ±΄ λ­κΉ?? (μλμ μ§λ¬Έμ λν λ΅μμ)
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

	ostream cout; // cout κ°μ²΄μμ±
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
                                 β A. μλμ ν¨μμμ λ°λ λ§€κ°λ³μλ ostream& νμ ν¨μν¬μΈν°μ΄λ€.

                                        void operator<< (ostream& (*fp)(ostream& ostm))   
                                        {
                                          fp(*this);
                                        }

                                      μ΄ ν¨μλ₯Ό νΈμΆν  λ cout << endl; λ₯Ό μ¬μ©νλ€.
                                      κ·Έλ¬λ©΄ ostream& (*fp)(ostream& ostm) = endl; κ³Ό κ°μ μμΌλ‘ λ§€κ°λ³μκ° μ λ¬μ΄ λλ€.
                                        
                                      μ΄λ ν¨μν¬μΈν° fpκ° endl()ν¨μλ₯Ό κ°λ¦¬ν€κ² λλ κ²μ΄λ€.
                                        
                                      κ·Έλμ fp(*this); λ₯Ό νλ©΄ endl()ν¨μμ μκΈ° κ°μ²΄λ₯Ό μ λ¬νκ³  endl()μμ 
                                      '\n'μ μΆλ ₯νλ κ²μ΄λ€.
                                        
            
              μμ μ½λλ cout << 123 << endl << 3.14 << endl; κ³Ό κ°μ νμμΌλ‘ μΆλ ₯μ λΆκ°νλ€.
              μ΄λ₯Ό ν΄κ²°νκΈ° μν΄μ μλμ κ°μ΄ μμ ν΄λ³΄μ.

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
			return *this;                  // ππ ν¨μμ λ°ννμ μμ ν΄μ£Όκ³  return *this μΆκ°ν΄μ£Όμλ€.
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
			printf("%g", e);  // %g: μ€μν μλμΆλ ₯
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

	ostream cout; // cout κ°μ²΄μμ±
}

int main()
{
	using mystd::cout;
	using mystd::endl;

	cout << 3 << endl << 6.14 << endl;
}

------------------------------------------------------------------------------
  
π’ <<, >> μ°μ°μμ μ€λ²λ‘λ©

int main()
{
  Point pos(3, 4);
  cout << pos << endl;  // [3, 4] μΆλ ₯     <-- μ΄λ°μμΌλ‘ μ°μ°μ΄ κ°λ₯νκ² νκ³ μ νλ €λ©΄ μ΄λ»κ² ν΄μΌν κΉ?
}
           
                   - coutλ ostream ν΄λμ€μ κ°μ²΄μ΄λ€.
                     
                   - ostreamμ μ΄λ¦κ³΅κ° std μμ μ μΈλμ΄ μμΌλ©°, μ΄μ μ¬μ©μ μν΄μλ ν€λνμΌ <iostream>μ ν¬ν¨ν΄μΌ νλ€.
                     
                   
                   λ κ°μ§ λ°©λ²μ΄ μμ κ²μ΄λ€. λ©€λ²ν¨μμ νν νΉμ μ μ­ν¨μμ νν μ΄λ κ² λ§μ΄λ€.
                     
                   cout.ostream<<(pos);     <--  ππ λ©€λ²ν¨μμ μν λ°©λ²μ cout κ°μ²΄μ λ©€λ²ν¨μλ₯Ό νλ μΆκ°ν΄μΌνλ€.
                                                      λ°λΌμ ostream ν΄λμ€λ₯Ό μμ ν΄μΌνλ―λ‘ μ΄λ λΆκ°λ₯ν λ°©λ²μ΄λ€.

                   ostream<<(cout, pos):    <--  κ·Έλ λ€λ©΄ μ΄ λ°©λ²μ μ±ν..!!


                     
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
	cout << pos2 << endl;  // β ostream& operator<<(ostream& os, const Point& pos); ν¨μμ λ°ννμ΄ ostream& μ΄μ΄μΌ μ΄λ κ² κ°μ²΄λ₯Ό λ°νν¨μΌλ‘μ¨ 
                         //     μ°μμ μΌλ‘ ν¨μλ₯Ό νΈμΆν  μ μλ€.
	return 0;
}
      
------------------------------------------------------------------------------

π  λ¬Έμ  10-3
	
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
	cout << "x, y μ’ν μμΌλ‘ μλ ₯: ";
	cin >> pos1;
	cout << pos1;

	Point pos2(101, 303);
	cout << "x, y μ’ν μμΌλ‘ μλ ₯: ";
	cin >> pos2;
	cout << pos2;

	return 0;
}
