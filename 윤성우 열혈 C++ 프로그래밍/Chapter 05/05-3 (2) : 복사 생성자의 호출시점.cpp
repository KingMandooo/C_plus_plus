

 C++에서는 리턴값이 있을때 리턴값을 저장하기 위해 메모리 상에 임시 변수가 생성된다.
 단, 리턴값이 없다면 임시변수는 생성되지 않는다.
 또한, 함수 선언이 끝나게 된다면 임시변수 역시 메모리 상에서 사라진다.(🎈🎈 함수 선언이 끝난다는 말을 잘 이해하기)
	 
int Func(int num)
{
	num++;
	cout << &num << endl;
	return num;
}
int main()
{
	int a = 5;
	cout << &a << endl;
	
	int num = Func(a);   
	// Func(a) 함수 선언이 끝난 행
}
 
 
 솔직히 함수의 반환값으로 인해 임시메모리가 할당된다는 것만 생소하고, 나머지는 다 당연하다.
 
----------------------------------------------------------------------------------------------
👉👉 코드 분석하기 (답: 아래 ㅋ)

#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n) {}
  
	SoSimple(const SoSimple& copy) : num(copy.num)
	{
		cout << "Called SoSimple(const SoSimple& copy)" << endl;
	}
  
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}
  
	void ShowData()
	{
		cout << "num: " << num << endl;
	}
};

SoSimple SimpleFuncObj(SoSimple ob)
{
	cout << "return 이전" << endl;
	return ob;                         // 반환하면 메모리에 선언과 초기화가 동시에 이루어진다는 것을 꼭 기억하기 !
}                                    // 🎈🎈 객체를 반환하게 되면, '임시객체'라는 것이 생성되고, 이 객체의 복사 생성자가 호출되면서 
                                     //      return문에 명시된 객체가 인자로 전달된다. 즉, 최종적으로 반환되는 객체는 새롭게 생성되는 임시객체이다.
int main()
{
	SoSimple obj(7);
	SimpleFuncObj(obj).AddNum(30).ShowData();
	obj.ShowData();

	return 0;
}

---------------------------------------------------------------------------
👉👉 코드 분석하기 (정 모르겠으면 아래 설명보고 다시 분석)
  
#include <iostream>
using namespace std;

class Temporary
{
private:
	int num;
public:
	Temporary(int n) : num(n)
	{
		cout << "create obj" << num << endl;
	}

	~Temporary()
	{
		cout << "destroy obj: " << num << endl;
	}

	void ShowTempInfo()
	{
		cout << "My num is " << num << endl;
	}
};

int main()
{
	Temporary(100);
	cout << "******** after make!" << endl << endl;

	Temporary(200).ShowTempInfo();
	cout << "******** after make!" << endl << endl;

	const Temporary& ref = Temporary(300);
	cout << "******** end of main!" << endl << endl;
  
  // 5;  <-- 이런 식으로 선언해도 오류 발생 없다. 그러나 생성하자마자 없어진다. 왜냐하면 쓸수가 없기 때문이다.

	return 0;
}
 
       
           클래스 외부에서 객체의 멤버함수를 호출하기 위해서 필요한 것은 다음 세 가지 중 하나이다.
           
           - 객체에 붙여진 이름
           - 객체의 참조 값(객체 참조에 사용되는 정보)
           - 객체의 주소 값

                
             🎈🎈 임시객체가 생성된 위치에는 임시객체의 참조 값이 반환된다.

               Temporary(200).ShowTempInfo(); --> (임시객체의 참조 값).ShowTempInfo();

               const Temporary& ref = Temporary(300);
           

               1. 임시객체는 다음 행으로 넘어가면 바로 소멸되어 버린다.
               2. 참조자에 참조되는 임시객체는 바로 소멸되지 않는다.
  
                 
                3+5의 연산에 사용되는 상수 3과 5처럼 임시객체에는 이름이 없기 때문에 다음 행으로 넘어가면
                어처피 접근이 불가능해진다. 따라서 접근이 불가능하게 된 임시객체는 바로 소멸을 시켜버린다.
                 
                반면에, const Temporary& ref = Temporary(300); 와 같이 임시객체를 생성하고 반환된 참조 값을
                참조자로 참조하게 된다면, 다음 행에서도 접근이 가능하다.
                따라서 비로소 소멸시키지 않는 것이다.




/*
  출력결과:  create obj100
             destroy obj: 100
             ******** after make!

             create obj200
             My num is 200
             destroy obj: 200
             ******** after make!

             create obj300
             ******** end of main!

             destroy obj: 300   

*/
---------------------------------------------------------------------------
👉👉 코드 분석하기

#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n)
	{
		cout << "New Object: " << this << endl;
	}

	SoSimple(const SoSimple& copy) : num(copy.num)
	{
		cout << "New Copy obj" << this << endl;
	}

	~SoSimple()
	{
		cout << "Destroy obj: " << this << endl;
	}
};

SoSimple SimpleFuncObj(SoSimple ob)
{
	cout << "Parm ADR: " << &ob << endl;
	return ob;
}

int main()
{
	SoSimple obj(7);
	SimpleFuncObj(obj);

	cout << endl;
	SoSimple tempRef = SimpleFuncObj(obj);
	cout << "Return Obj " << &tempRef << endl;

	return 0;
}


/*
  출력결과 :  New Object: 000000076A77FBC4         // obj 객체 생성자 호출
              New Copy obj000000076A77FCC4         // SimpleFuncObj()의 매개변수 ob의 복사 생성자 호출
              Parm ADR: 000000076A77FCC4           // SimpleFuncObj()의 정의 출력
              New Copy obj000000076A77FD04         // SimpleFuncObj()의 반환값 ob의 복사 생성자 호출
              Destroy obj: 000000076A77FCC4        // SimpleFuncObj()의 매개변수 ob의 소멸자 호출
              Destroy obj: 000000076A77FD04        // SimpleFuncObj()의 반환값 ob의 소멸자 호출

              New Copy obj000000076A77FD24         // SimpleFuncObj()의 매개변수 ob의 복사 생성자 호출
              Parm ADR: 000000076A77FD24           // SimpleFuncObj()의 정의 출력
              New Copy obj000000076A77FBE4         // SimpleFuncObj()의 반환값 ob의 복사 생성자 호출  👈👈  이 주소와
              Destroy obj: 000000076A77FD24        // SimpleFuncObj()의 매개변수 ob의 소멸자 호출
              Return Obj 000000076A77FBE4          // &tempRef는 SimpleFuncObj()에서 반환된 ob의 주소 👈👈  이 주소가 같다.
              Destroy obj: 000000076A77FBE4        // tempRef가 참조하는 임시객체 소멸
              Destroy obj: 000000076A77FBC4        // obj 소멸 (처음의 SoSimple obj(7);)
*/



---------------------------------------------------------------------------

/*
  출력결과 :  Called SoSimple(const SoSimple& copy)
              return 이전
              Called SoSimple(const SoSimple& copy)
              num: 37
              num: 7
*/
