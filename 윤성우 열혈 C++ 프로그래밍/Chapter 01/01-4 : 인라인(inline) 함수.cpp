 '프로그램 코드라인 안으로 들어가 버린 함수'

   
 🟢 C언어의 매크로 함수

#include <stdio.h>

#define SQR(X) ((X)*(X)) // 매크로 함수는 이처럼 모든 인수를 괄호로 묶어줘야 함.
#define PRT(X) printf("계산 결과는 %d입니다.\n", X)  

int main(void)
{
    int result;
    int x = 5;  
 
    result = SQR(10);     // reuslt = 100;

    PRT(result);          // 100 출력

    result = SQR(x);      // result = 25;

    PRT(result);          // 25 출력

    result = SQR(x+3);    // result = 64;

    PRT(result);          // 64 출력

    return 0;
}

--------------------------------

✔ 매크로 함수의 장점

  1. 매크로 함수는 단순 치환만을 해주므로, 인수의 타입을 신경 쓰지 않습니다.

  2. 매크로 함수를 사용하면 여러 개의 명령문을 동시에 포함할 수 있습니다.

  3. 함수 호출에 의한 성능 저하가 일어나지 않으므로, 프로그램의 실행속도가 향상됩니다.

✔ 매크로 함수의 단점

  1. 원하는 결과를 얻는 정확한 매크로 함수의 구현은 어려우며, 따라서 디버깅 또한 매우 어렵습니다.

  2. 매크로 함수의 크기가 증가하면 증가할수록 사용되는 괄호 또한 매우 많아져서 가독성이 떨어집니다.
   
              
                                                                출처: http://www.tcpschool.com/c/c_prepro_macroFunc
