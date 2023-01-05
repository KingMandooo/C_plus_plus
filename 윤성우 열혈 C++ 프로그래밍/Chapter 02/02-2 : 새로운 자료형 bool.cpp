
#include <iostream> 
using namespace std;

int main()
{
	int num = 10;

	cout << "true: " << true << endl;
	cout << "false: " << false << endl;

	cout << "sizeof(1): " << sizeof(1) << endl;                   // 4 출력
	cout << "sizeof(0): " << sizeof(0) << endl;                   // 4 출력
	cout << "sizeof(true): " << sizeof(true) << endl;             // 1 출력
	cout << "sizeof(false): " << sizeof(false) << endl;           // 1 출력

	return 0;
}

           
                     🎈🎈 true는 1이 아니며, false 역시 0이 아니다.
                          이 둘은 '참'과 '거짓'을 표현하기 위한 1바이트 크기의 데이터일 뿐이다.
                          이 둘을 출력하거나 정수의 형태로 형 변환하는 경우에 각각 1과 0으로 변환되도록 정의되어 있을 뿐이다.
                       
                          따라서 true와 false를 굳이 숫자에 연결시켜서 이해하지 말자.
                          true와 false는 그 자체로 '참'과 '거짓'을 나타내는 목적으로 정의된 데이터로 인식하는 것이 바람직하다.
                       
                       
                       
🟢 자료형 bool

#include <iostream>
using namespace std;

bool IsPositive(int num)    // num이 음수거나 0이면 false 반환, 양수면 true 반환
{
	if (num <= 0)
		return false;
	else
		return true;
}

int main()
{
	bool isPos;
	int num;
	cout << "Input number: ";
	cin >> num;

	isPos = IsPositive(num);

	if (isPos)
		cout << "Positive number" << endl;
	else
		cout << "Negative number" << endl;
	
	return 0;
}


