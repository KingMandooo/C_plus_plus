#include <iostream>
// <iostream.h> 와 같이 확장자를 붙이면 오류가 발생한다.
// 그 이유는 C++에서는 프로그래머가 정의하는 헤더파일의 선언이 아닌, 표준 헤더파일의 선언에서는 확장자를 생략하도록 약속되어 있다.

int main()
{
	int num = 20;                   // 🎈🎈 std::cout << '출력대상'; 

	std::cout << "Hello, World!" << std::endl;                        // std:cout와 << 를 사용하여 출력  
	std::cout << "Hello" << ',' << ' ' << "World!" << std::endl;      // std::endl는 '\n'와 같은 역할
	std::cout << num << " + " << num << " = ";
	std::cout << num + num << std::endl;

	num += num; 

	std::cout << num; 

}

/*
  출력결과: Hello, World!
            Hello, World!
            20 + 20 = 40
            40
*/

--------------------------------------------------
  
#include <iostream>

int main()
{
	int val1, val2, sum = 0;

	std::cout << "val1 값 입력: ";
	std::cin >> val1;                  // 🎈🎈 std::cin >> '변수'; 

	std::cout << "val2값 입력: ";
	std::cin >> val2;

	sum = val1 + val2;

	std::cout << "두 값의 합: " << sum << std::endl;

	return 0;
}

--------------------------------------------------
  
#include <iostream>

int main()
{
	int val1, val2, sum = 0;

	std::cout << "val1 값과 val2 값 입력: ";
	std::cin >> val1 >> val2;                   // ✅ 이런식으로 연속적으로 데이터를 입력 받을 수도 있음. (공백으로 구분)

	sum = val1 + val2;

	std::cout << "두 값의 합: " << sum << std::endl;

	return 0;
}

--------------------------------------------------
  
#include <iostream>

int main()
{
	char name[30];
	char country[30];       // 배열 기반의 문자열도 입출력이 가능하다

	std::cout << "What's your name?" << std::endl;
	std::cin >> name;

	std::cout << "Where are you live?" << std::endl;
	std::cin >> country;

	std::cout << "My name is " << name;
	std::cout << " and I live in " << country;

	return 0;
}


-------------------------------------------------------------------------

🟠 문제1

#include <iostream>

int main()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		int num;
		std::cout << i + 1 << "번째 정수 입력: ";
		std::cin >> num;

		sum += num;
	}

	std::cout << "합: " << sum << '\n';    // 이런식으로 std::endl 대신 개행문자를 사용해도 된다.

	return 0;
}


🟠 문제2

#include <iostream>

int main()
{
	char name[30], phoneNum[30];

	std::cout << "이름 입력: ";
	std::cin >> name;
	
	std::cout << "전화번호 입력: ";
	std::cin >> phoneNum;

	std::cout << "이름: " << name << std::endl;
	std::cout << "전화번호: " << phoneNum << std::endl;

	return 0;
}


🟠 문제3

#include <iostream>

int main()
{
	int dan;

	std::cout << "원하는 단 입력: ";
	std::cin >> dan;

	for (int i = 1; i <= 9; i++)
	{
		int result = dan * i;

		std::cout << dan << " * " << i << " = " << result << std::endl;
	}

	return 0;
}


🟠 문제4

#include <iostream>

int main()
{
	while (true)
	{
		int value;

		std::cout << "판매 금액을 만언 단위로 입력(-1 to end): ";
		std::cin >> value;
	
		if (value == -1)
		{
			std::cout << "프로그램을 종료합니다\n";
			return 0;
		}

		std::cout << "이번 달 급여: " << 50 + value * 0.12 << "만원" << std::endl;
	}

	return 0;
}
