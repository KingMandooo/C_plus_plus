π’ ν¨μ ννλ¦Ώκ³Ό static μ§μ­λ³μ

  ππ μΆ©λΆν μ½λλ§ λ³΄λλΌλ μ΄ν΄κ° κ°λ₯νλ€.

#include <iostream>
using namespace std;

template <class T>         // ν¨μ ννλ¦Ώ
void ShowStaticValue()    
{
	static T num = 0;       
	num += 1;
	cout << num << " ";
}

int main()
{
	ShowStaticValue<int>();   // 1 μΆλ ₯
	ShowStaticValue<int>();   // 2 μΆλ ₯
	ShowStaticValue<int>();   // 3 μΆλ ₯

	cout << endl;

	ShowStaticValue<long>();   // 1 μΆλ ₯
	ShowStaticValue<long>();   // 2 μΆλ ₯
	ShowStaticValue<long>();   // 3 μΆλ ₯
	
	return 0;
}

---------------------------------------------------------
  
π’ ν΄λμ€ ννλ¦Ώκ³Ό static λ©€λ²λ³μ

  ππ μΆ©λΆν μ½λλ§ λ³΄λλΌλ μ΄ν΄κ° κ°λ₯νλ€.

#include <iostream>
using namespace std;

template <class T>
class StaticValue
{
private:
	static T mem;
public:
	void AddMen(T num) { mem += num; }
	void ShowStaticValue() { cout << mem; }
};

template <class T>
T StaticValue<T>::mem = 0;

int main()
{
	StaticValue<int> obj1;
	StaticValue<int> obj2;
	obj1.AddMen(50);         
	obj2.AddMen(900);
	obj1.ShowStaticValue();      // 950 μΆλ ₯

	cout << endl;

	StaticValue<long> obj3;
	StaticValue<long> obj4;
	obj3.AddMen(300);
	obj4.ShowStaticValue();      // 300 μΆλ ₯
	
	return 0;
}

---------------------------------------------------------
  
   ππ μ μ λΆλΆμ Tκ° μ‘΄μ¬νλ©΄ Tμ λν μ€λͺμ μν΄μ <class T>μ ννλ‘ λ§λΆμ΄λ©΄ λκ³ ,
        Tκ° μ‘΄μ¬νμ§ μμΌλ©΄ <>μ ννλ‘ κ°λ¨νκ² μ μΈνλ©΄ λλ€.
          
        μ¬μ€ λ λΉμ°ν μ΄λ λ€κ³  μκ°νκ³  μμλ€.
          
          
          
    ππ ννλ¦Ώ static λ©€λ²λ³μ λν νΉμνκ° νμν κ²½μ°κ° μμ κ²μ΄λ€.
          
          template <class T>
          T StaticValue<T>::mem = 0;

          μ΄ κ²½μ°μ μλ£νμ΄ doubleμΌ κ²½μ°μ ννλ¦Ώμ 
          
          template<>
          long StaticValue<long>::mem = 5;
   
          μ΄λ κ² μ μν΄μ£Όλ©΄ λλ€.
     
          μ΄μ  main() μμ StaticValue<long> obj3; 
          μ΄λ κ² μ μΈμ ν΄μ£Όλ©΄ static λ³μμΈ memμ΄ 5λ‘ μ΄κΈ°νκ° λμ΄μμ κ²μ΄λ€.
   
     
     
