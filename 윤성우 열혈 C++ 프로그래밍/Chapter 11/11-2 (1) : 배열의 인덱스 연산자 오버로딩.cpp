π’ λ°°μ΄λ³΄λ€ λμ λ°°μ΄ ν΄λμ€

	int s[3] = { 0 }; 
	printf("%d", s[-1]);       <--   Cμ C++μ κΈ°λ³Έ λ°°μ΄μ λ€μκ³Ό κ°μ λ¨μ μ μ§λκ³  μλ€.
	printf("%d", s[-2]);
	printf("%d", s[-3]);               ππ "κ²½κ³κ²μ¬λ₯Ό νμ§ μλλ€."
    
                     μ΄λ¬ν λ¨μ μ ν΄κ²°νκΈ° μν΄μ 'λ°°μ΄ ν΄λμ€'λΌλ κ²μ λμμΈμ ν΄λ³Έλ€.
    
                     μ°μ ,  κ°μ²΄ arrObjectμ μ€λ²λ‘λ©λ []μ°μ°μλ₯Ό μ¬μ©νλ©΄ μ΄λ»κ² ν΄μμ΄ λ κΉ?
    
                     arrObject[2];   -->    arrObject.operator[](2);

                     μ΄λ κ² ν΄μλλ€.
                       
---------------------------------------------------------------------
                       
#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;
public:
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)       // ππ μ΄λ κ² νλ©΄ λ°°μ΄μ κ·Όμ μμ μ±μ λ³΄μ₯λ°μ μ μλ€.
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	~BoundCheckIntArray()
	{
		delete[] arr;
	}
};

int main()
{
	BoundCheckIntArray arr(5);
	for (int i = 0; i < 5; i++)
		arr[i] = (i + 1) * 11;  //  ππ arr.operator[](i); --> return arr[idx];
	for (int i = 0; i < 6; i++)
		cout << arr[i] << endl; //  ππ 0~4 κΉμ§λ μΆλ ₯ 5μμ  λ°°μ΄ λ²μ λ²μ΄λμ κ²½κ³ λ¬Έ μΆλ ₯

	return 0;
}

/*
  μΆλ ₯κ²°κ³Ό:   11
              22
              33
              44
              55
              Array index out of boud exception
*/

---------------------------------------------------

int main()
{
	BoundCheckIntArray arr(5);

	BoundCheckIntArray cpy1(5);   // λμμ°μ°μ νΈμΆ
	cpy1 = arr;

	BoundCheckIntArray cpy2 = arr;  // λ³΅μ¬μμ±μ νΈμΆ

	return 0;
}

              λ§μ½ μ΄λ κ² μμ μ½λμ μ΄ μ½λλ₯Ό μΆκ°νλ€λ©΄ μ΄λ»κ² λ κΉ?
                
              λ¬Όλ‘  λν΄νΈ λ³΅μ¬μμ±μμ λν΄νΈ λμμ°μ°μλ μμ λ³΅μ¬λ§ ν¨μΌλ‘ κΉμ λ³΅μ¬κ° μ§νλλλ‘ 
              λ³΅μ¬μμ±μμ λμμ°μ°μλ₯Ό λ°λ‘ λͺμμ μΌλ‘ μ μν΄μ€μΌνλ€κ³  μκ°μ΄ λ€κΈ°λ νλ€.
                
              κ·Έλ¬λ κ·Έμ μ λ μ€μμλλ μμΉμ΄ μλ€.
                
              ππ λ°λ‘ λ°°μ΄μ μ μ₯μμ μΌμ‘°μ΄κ³ , μ μ₯μμ μ μ₯λ λ°μ΄ν°λ 'μ μΌμ±'μ΄ λ³΄μ₯λμ΄μΌ νλ€λ κ²μ΄λ€.
                   μ¦, λλΆλΆμ κ²½μ° μ μ₯μμ λ³΅μ¬λ λΆνμνκ±°λ μλͺ»λ μΌλ‘ κ°μ£Όλλ€λ κ²μ΄λ€.
           
              κ·Έλ λ€λ©΄ μ΄λ₯Ό μν΄μ μ°λ¦¬λ λ³΅μ¬μμ±μμ λμμ°μ°μλ₯Ό μμ νΈμΆμ λͺ»νκ² νλ λ°©λ²μ μ¬μ©νλ€.
                
              λΉ μνλ‘ μ μλ λ³΅μ¬ μμ±μμ λμ μ°μ°μλ₯Ό private λ©€λ²λ‘ λ μΌλ‘μ¨ λ³΅μ¬μ λμμ μμΉμ μΌλ‘ λ§μλμλ€.
                
#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;
	BoundCheckIntArray(const BoundCheckIntArray& copy) {}          // ππ λ³΅μ¬μμ±μμ λμμ°μ°μλ₯Ό privateμ μ μΈ.
	BoundCheckIntArray operator= (const BoundCheckIntArray& ref) {}
public:                             
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
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
	~BoundCheckIntArray()
	{
		delete[] arr;
	}
};

int main()
{
	BoundCheckIntArray arr(5);

	BoundCheckIntArray cpy1(5);   
	cpy1 = arr;                     // ββ μ€λ₯λ°μ

	BoundCheckIntArray cpy2 = arr;  // ββ μ€λ₯λ°μ

	return 0;
}

------------------------------------------------------------------------
  
π’ const ν¨μλ₯Ό μ΄μ©ν μ€λ²λ‘λ©μ νμ©

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
	int GetArrLen() const { return arrlen; }
	~BoundCheckIntArray() { delete[] arr; }
};

void ShowAllData(const BoundCheckIntArray& ref)
{
	int len = ref.GetArrLen();
	for (int idx = 0; idx < len; idx++)
		cout << ref[idx] << endl;
                                  // refλ const κ°μ²΄μ΄κΈ° λλ¬Έμ const ν¨μλ§ νΈμΆμ΄κ°λ₯νλ€.
                                  // κ·Έλ¬λ ref.operator[](idx); ν¨μλ const ν¨μκ° μλλ€.
                                  // λ°λΌμ νΈμΆν  ν¨μκ° μκΈ° λλ¬Έμ μ€λ₯κ° λ°μνλ€.
}

int main()                        // ππ κ·Έλ¬λ, constλ₯Ό μΆκ°ν΄λ λ°°μ΄μ λ©€λ²λ‘ μ μΈνλ κ²½μ°μλ μ μ₯ μμ²΄κ° λΆκ°λ₯ν΄μ§κΈ° λλ¬Έμ 
{                                 //      μ’μ λ°©λ²μ΄λΌκ³  ν  μ μλ€.  ππ λ­ λ§μ΄μ§????????
	BoundCheckIntArray arr(5);                                      // https://www.acmicpc.net/board/view/78189
	for (int i = 0; i < 5; i++)
		arr[i] = (i + 1) * 11;                                // β μμ κΆκΈμ¦μ λν λ΅μ μλμ λ΄κ° μ½λλ‘ μ€λͺμ ν΄λ¨λ€!!!!!!!
 
	ShowAllData(arr);

	return 0;
}

-------------------          ππ κ·Έλμ const λν ν¨μ μ€λ²λ‘λ©μ΄ λλ€λ κ²μ μ΄μ©νμ¬ λκ°μ μ μμ constν¨μλ₯Ό μ μΈν΄μ€λ€.
  
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
	int& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int& operator[] (int idx) const      // ππ const ν¨μ μ μΈ
	{                                    //      μ΄λ κ² const κΈ°λ° μ€λ²λ‘λ©μ΄ μ μ©νλ€λ μ¬μ€!!
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

void ShowAllData(const BoundCheckIntArray& ref)
{
	int len = ref.GetArrLen();
	for (int idx = 0; idx < len; idx++)
		cout << ref[idx] << endl;
}

int main()
{
	BoundCheckIntArray arr(5);
	for (int i = 0; i < 5; i++)
		arr[i] = (i + 1) * 11;

	ShowAllData(arr);

	return 0;
}

--------------------------------------------------------

 β λλμ²΄ const μ°Έμ‘°ν ν¨μμμ λ©€λ²λ³μκ° λ°νμ΄ μλλμ§ μ΄ν΄κ° μλλλ°, μ΄μ  μ΄ν΄λλ€.
	
class StudyHard
{
private:
	int v;
public:
	int& aa() const
	{
		cout << v << endl;
		return v;  // <-- β μ¬κΈ°μ μ€λ₯λ°μ (const ν¨μλ΄μμλ λ©€λ²λ³μ v λν const νμ.)

		// λ°ννμ΄ μ°Έμ‘°νμ΄λ©΄.
		// const int num1 = 3;
		// int& num2 = num1;      <---  μ΄λ κ²νλ©΄ μ»΄νμΌ μλ¬κ° λ°μνλ€.

		// λ°λΌμ μλ¬λ₯Ό μμ μ£ΌκΈ° μν΄μλ
		// const int& num2 = num1;  <---  μ΄λ κ² μ μΈν΄μ€μΌ νλ€.

		// μ! μ΄μ  λ€μ ν¨μλ‘ λμμμ μ½λλ₯Ό μμΈν λ΄λ³΄λ©΄
		// νμ¬ int& aa() μ λ°νκ°μ μΌλ° μ°Έμ‘°νμ΄λ€.
		// κ·Έλ°λ° μ΄ ν¨μλ const ν¨μμ΄λ―λ‘ ν¨μ λ΄μ λ©€λ²λ constνμΌλ‘ λ°λλ€. (νμ¬ λ©€λ²λ³μ vκ° constν)
		// κ·Έλ°λ° λ§μ½ μ΄ λ°νκ°μ λ°μ μ°Έμ‘°νμ΄ 
		// μλ₯Ό λ€μ΄ int& b = aa(); λΌλ©΄
		// constμ κΈ°λ³Έμλ¦¬κ° νκ΄΄λλ νμμ΄ μΌμ΄λλ€. (aaμ λ°νκ°μ΄ const μ΄κΈ° λλ¬Έμ..)
		
		// ππ "const int λ int& μ λμνμ§ λͺ»νλ€" (vκ° const intμ΄κ³  vλ₯Ό λ°νλ°μ μ΄λ int&ν λ³μκ° μ‘΄μ¬ν  μλ μλ€.)
		
		// κ·ΈλκΉ μ μ΄μ C++ μ΄λ¬ν λͺ¨μμ λ§κΈ° μν΄μ μ»΄νμΌ μ€λ₯λ₯Ό λ°μνλ κ²μ΄λ€.
		// λ§μ½ const vλ₯Ό λ°ννκ³  μΆλ€λ©΄,
		// int& aa() μμ constλ₯Ό λΆμ¬μ const int& νμ λ°νν΄μΌν  κ²μ΄λ€.
		
		// const int& aa() { ... } <-- μ΄λ κ² λ§μ΄λ€.
	}
};

-----------------
 β  private λ³μμ μ΄λ κ² μ κ·Όμ΄ κ°λ₯νλ€..?? (λ΄κ° μ§  μ½λ)
	
#include <iostream>
using namespace std;

class StudyHard
{
private:
	int v;
public:
	StudyHard(int v) :v(v) {}
	int& aa() 
	{
		cout << "v: " << v << endl;
		return v; 
	}
	void ShowV()
	{
		cout << "v: " << v << endl;
	}
};

int main()
{
	StudyHard bb(3);
	int& num = bb.aa();    
	num = 100;
	bb.ShowV();
	return 0;
}

/*
  μΆλ ₯κ²°κ³Ό:     v: 3
		v: 100
*/
