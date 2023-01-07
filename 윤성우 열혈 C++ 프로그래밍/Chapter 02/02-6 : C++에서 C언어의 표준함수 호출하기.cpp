

    #include <stdio.h>  --> #include <cstdio>
    #include <stdlib.h> --> #include <cstdlib>
    #include <string.h> --> #include <cstring>
    #include <math.h>   --> #include <cmath>


      "헤더파일의 확장자인 .h를 생략하고 앞에 c를 붙이면 C언어에 대응하는 C++의 헤더파일 이름이 된다."
        
        
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
	char str1[] = "Result";
	char str2[30];

	strcpy(str2, str1);
	printf("%s: %f \n", str1, sin(0.14));     // Result: 0.139543  출력
	printf("%s: %f \n", str2, abs(-1.25));    // Result: 1.250000  출력
}       

                 

                                        🎈🎈 모든 표준함수들이 이름공간 std 내에 선언되어있다.
                                          
                                          
---------------------------------------------------------------------


🟠 문제 1
                                          
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char str1[30] = "Result";
	char str2[30];
	char str3[20] = ": I'm hansom";

	cout << strlen(str1) << endl;     // strlen(str1) : str1의 '\0'을 제외한 길이 출력

	strcat(str1, str3);               // str1 뒤에 str3 덧붙이기
	cout << str1 << endl;

	strcpy(str2, str1);               // str2에 str1 복사
	cout << str2 << endl;

	cout << strcmp(str1, str2) << endl;     // str1과 str2가 같으면 0 출력, 다르면 1 출력
	cout << strcmp(str1, str3) << endl;
}


/*
  출력결과: 6
            Result: I'm hansom
            Result: I'm hansom
            0
            1
*/


🟠 문제 2
  
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));

	for (int i = 0; i < 5; i++)
	{
		int random = rand() % 100;
		cout << random << endl;
	}

	return 0;
}
  
  
  
  
  
  
  
