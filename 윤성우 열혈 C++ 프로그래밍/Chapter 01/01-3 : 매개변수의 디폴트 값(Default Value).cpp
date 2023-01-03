디폴트 값 : 기본적으로 설정되어 있는 값


#include <iostream>

int func(int a = 5, int b = 300)
{
	return a + b;
}

int main()
{
	std::cout << func() << std::endl;
	std::cout << func(100) << std::endl;    // a에 100 전달
	std::cout << func(50, 20) << std::endl;

	return 0;
}

/*
  출력결과: 305
            400
            70
*/

----------------------------------------
  
 ❗❗ 주의 
  
            ✅ 아래와 같이 함수의 선언이 별도로 필요한 경우에는 매개변수의 디폴트 값은 함수의 선언부분에만 위치시켜야 한다.
  
#include <iostream>

int func(int a = 5, int b = 300);

int main()
{
	std::cout << func() << std::endl;
	std::cout << func(100) << std::endl;
	std::cout << func(50, 20) << std::endl;

	return 0;
}

int func(int a, int b)   // 이렇게 함수를 따로 정의할 땐, 매개변수의 디폴트 값은 선언부분에만 위치해야 한다.
{
	return a + b;
}            

--------
❌ 오류 발생

#include <iostream>

int func(int a = 5, int b = 300);

int main()
{
	std::cout << func() << std::endl;
	std::cout << func(100) << std::endl;
	std::cout << func(50, 20) << std::endl;

	return 0;
}

int func(int a = 5, int b = 300)   // 함수의 정의 부분에서 디폴트 값을 지정할 수 없다.
{
	return a + b;
}

--------
❌ 오류 발생

#include <iostream>

int func(int a, int b);   // 함수의 선언 부분에서만 디폴트 값을 지정해주어야 한다.

int main()
{
	std::cout << func() << std::endl;
	std::cout << func(100) << std::endl;
	std::cout << func(50, 20) << std::endl;

	return 0;
}

int func(int a = 5, int b = 300)
{
	return a + b;
}
---------
  
🟢 부분적 디폴트 값 설정
   
   int func(int a = 5, int b, int c);  // 오류 발생❌

   int func(int a = 5, int b = 7, int c); // 오류 발생❌
  
   int func(int a, int b, int c = 9);  // 작동⭕

   int func(int a, int b = 7, int c = 9);  // 작동⭕

   
   "함수에 전달되는 인자가 왼쪽에서부터 오른쪽으로 채워지기 때문에 부분적으로 디폴트 값을 설정할 땐 오른쪽부터 값을 채워야 한다."
     
    --> 예를 들어서,     func(30) 으로 호출을 하면 int a에 먼저 값이 채워진다.
                         만약 이때 b와 c에 디폴트 값이 지정되어 있지 않으면, 매개변수에 값이 들어가지 못하게 된다.















