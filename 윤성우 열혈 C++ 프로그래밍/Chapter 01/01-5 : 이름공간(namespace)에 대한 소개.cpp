#include <iostream>

namespace BestComImp1
{
	void SimpleFunc(void)
	{
		std::cout << "BestCom이 정의한 함수" << '\n';
	}
}

namespace ProgComImp1
{
	void SimpleFunc(void)
	{
		std::cout << "ProgCom이 정의한 함수" << std::endl;
	}
}

int main()
{
	BestComImp1::SimpleFunc();   // 범위지정 연산자(scope resolution operator) 를 사용했다.
	ProgComImp1::SimpleFunc();

	return 0;
}


                          ✅ ::는 '범위지정 연산자(scope resolution operator)'라 하며, namespace를 지정할 때 사용하는 연산자다.
                            
-----------------------------------

🟢 이름공간 기반의 함수 선언과 정의의 구분

  --> 보통 '함수의 선언'은 헤더파일에 저장하고, '함수의 정의'는 소스파일에 저장한다.

#include <iostream>

namespace BestComImp1
{
	void SimpleFunc(); // 함수의 선언
}

namespace ProgComImp1
{
	void SimpleFunc(); // 함수의 선언
}

int main()
{
	BestComImp1::SimpleFunc();
	ProgComImp1::SimpleFunc();

	return 0;
}

void BestComImp1::SimpleFunc()
{
	std::cout << "BestCom이 정의한 함수" << '\n';        // 함수의 정의
}

void ProgComImp1::SimpleFunc()
{
	std::cout << "ProgCom이 정의한 함수" << std::endl;   // 함수의 정의
}

-----------------------------------
  
#include <iostream>

namespace BestComImp1
{
	void SimpleFunc(void);
	void PrettyFunc(void);
}

namespace ProgComImp1
{
	void SimpleFunc(void);
}

int main()
{
	BestComImp1::SimpleFunc();

	return 0;
}

void BestComImp1::SimpleFunc(void)
{
	std::cout << "BestCom이 정의한 함수" << '\n';

	PrettyFunc();                                      // 같은 네임스페이스 안에 있으면 굳이 명시할 필요가 없다.

	ProgComImp1::SimpleFunc();                         // 다른 네임스페이스이므로 이름공간을 명시해야 한다.

}

void BestComImp1::PrettyFunc(void)
{
	std::cout << "So Pretty!!" << '\n';

}

void ProgComImp1::SimpleFunc(void)
{
	std::cout << "ProgCom이 정의한 함수" << std::endl;
}

-----------------------------------

🟢 이름공간의 중첩

#include <iostream>

namespace Numbers
{
	int a = 5;

	namespace SubOne
	{
		int b = 2;
	}

	namespace SubTwo
	{
		int c = 3;
	}
}

int main()
{
	std::cout << Numbers::a << '\n';                    // 5 출력
	std::cout << Numbers::SubOne::b << '\n';            // 2 출력
	std::cout << Numbers::SubTwo::c << std::endl;       // 3 출력

	return 0;
}
 
-----------------------------------

🟢 std::cout, std::cin, std::endl

namespace std   // 네임스페이스 std에 선언된 cout, cin, endl ...
{
  cout..
  cin..
  endl..
}

-----------------------------------

🟢 using을 이용한 네임스페이스의 명시

#include <iostream>

namespace Hybrid
{
	void HybFunc()
	{
		std::cout << "So simple function!" << std::endl;
		std::cout << "In namespace Hybrid!" << std::endl;
	}
}

int main()
{
	using Hybrid::HybFunc;  // 이렇게 하면 아래처럼 이름공간 지정없이 함수를 호출할 수 있다.

	HybFunc();

	return 0;
}

-----------
  
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	int a;

	cout << "Hello, World!" << endl;
	cin >> a;
	cout << "a의 값: " << a << endl;

	return 0;
}


🎈🎈 위처럼 일일이 using 선언을 하는 것은 매우 귀찮은 일이다. 
      따라서 'using namespace std;' 를 사용하면,
      '이름공간 std에 선언된 모든 것에 대해 이름공간 지정의 생략'을 명령할 수 있다.

        
#include <iostream>

using namespace std;

int main()
{
	int a;

	cout << "Hello, World!" << endl;
	cin >> a;
	cout << "a의 값: " << a << endl;

	return 0;
}

              ✅ 이렇게 선언을 해버리면, 그만큼 이름충돌이 발생할 확률은 상대적으로 높아진다. 
                  따라서, 무조건 편한 것만을 선호하기 보다는 상황을 판단해서 적절히 혼용하는 지혜가 필요하다.
                
                  만약 다른 네임스페이스 안에 같은 함수가 있다고 가정했을 때, 두 네임스페이스를 모두 using 해버린다면,
                  그 안에 이름이 겹치는 함수를 사용했을 경우, 어떤 네임스페이스를 활용해야하는지 컴파일러가 헷갈려한다. (아래 예시)
                  
#include <iostream>

using namespace std;

using namespace AA;
using namespace BB;

namespace AA
{
	int a = 5;     // AA의 a
}

namespace BB
{ 
	int a = 3;    // BB의 a
}

int main()
{
	cout << a << endl;    🎈🎈 a 가 모호하다고 컴파일에서 오류 출력

	return 0;
}
       
-----------------------------------
🟢 namespace의 별칭 지정
  
                         --> namespace가 중첩되면서까지 과도하게 사용되는 경우.
	
#include <iostream>

using namespace std;

namespace AA
{
	namespace BB
	{
		namespace CC
		{
			int num1;
			int num2;
		}
	}
}

int main()
{
	AA::BB::CC::num1 = 5;
	AA::BB::CC::num2 = 12;

	cout << AA::BB::CC::num1 << '\n';
	cout << AA::BB::CC::num2 << '\n';

	namespace ABC = AA::BB::CC;       // ✅ AA::BB::CC에 ABC라는 별칭을 붙여준다.

	cout << ABC::num1 << '\n';
	cout << ABC::num2 << '\n';

	return 0;
}

-----------------------------------
	
🟢 :: 의 또 다른 기능 (New !) 

#include <iostream>

using namespace std;

int a = 50;

int main()
{
	int a = 100;

	a = 999;

	cout << "지역변수 a : " << a << endl;

	::a++;   // ✅ 전역변수 a에 접근

	cout << "전역변수 a : " << ::a << endl;

	return 0;
}




