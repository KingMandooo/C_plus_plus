🟢 전위증가와 후의증가의 구분

    ++pos   -->    pos.operator++();
    pos++   -->    pos.operator++(int);


    --pos   -->    pos.operator--();
    pos--   -->    pos.operator--(int);

   🎈🎈 int는 단지 후위연산을 구분하기 위한 목적으로 선택된 것일 뿐,
        int형 데이터를 인자로 전달하라는 뜻이 아니다.

-------------------------------------------------------------------------          
          
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
	Point& operator++()
	{
		xpos += 1;
		ypos += 1;
		return *this;
	}
	const Point operator++(int)
	{
		const Point retobj(xpos, ypos);          // 🎈🎈 함수 내에서 retobj의 변경을 막기위해 const 객체로 선언
		xpos += 1;                               //      "const 객체를 대상으로는 값의 변경능력을 지니는, const로 선언되지 않은 함수의 호출을 허용하지 않는다."
		ypos += 1;                               //                                                       (const가 뒤에 붙은 함수)
		return retobj;
	}
	friend Point& operator--(Point& ref);
	friend const Point operator--(Point& ref, int);
};

Point& operator--(Point& ref)
{
	ref.xpos -= 1;
	ref.ypos -= 1;
	return ref;
}

const Point operator--(Point& ref, int)
{
	const Point retobj(ref);
	ref.xpos -= 1;
	ref.ypos -= 1;
	return retobj;
}


int main()
{
	Point pos(3, 5);
	Point cpy;
	cpy = pos--;          // cpy = operator--(pos); 이거와 다름, 이건 전위 연산자 함수호출
	cpy.ShowPosition();
	pos.ShowPosition();         // 🎈🎈 출력결과를 잘보면 이 코드는 후위 연산자를 완벽히 구현했다고 볼 수 있다.
                              //       cpy = pos--; 를 하면 cpy의 값에 pos가 들어간다음에, pos의 멤버변수 값이 감소한 것을 볼 수 있다.
	cpy = pos++;
	cpy.ShowPosition();
	pos.ShowPosition();

	return 0;
}


/*
출력결과: [3, 5]
          [2, 4]
          [2, 4]
          [3, 5]
*/
-------------------------------------------------------------------------
	
	💫 여기서부터는 내가 이해하는 데 한참이 걸렸던 부분이다. 💫
	
    복습하기 전에 상기시켜야할 내용.
    
    -->  const 위치에 따른 함수의 기능 : https://ladun.tistory.com/19

        - const가 함수의 뒤에 붙으면 그 함수 내에서 객체의 private 멤버변수를 변경 불가.
     
        - const가 함수의 앞에 붙으면 그 함수가 반환하는 값은 const형 (상수).
		
        - const가 함수의 매개변수에 붙으면 함수 내에서 매개변수 값 변경 불가.
		
		
	
const Point operator++(int)
{
	const Point retobj(xpos, ypos);  // const 객체는 멤버변수의 값을 변경하지 못한다. 즉, 객체 내에서 const 함수만 호출할 수 있다.
	xpos += 1;                                                                                  //  (const가 뒤에 붙은 함수)
	ypos += 1;
	return retobj;
}

                                                   이 두 함수는 모두가 앞에 const가 붙었다. 이것은 반환된 값을 변경하지 못하게 하는 기능을 한다.
const Point operator--(Point& ref, int)            따라서 반환된 객체는 'Point형 const 임시객체'가 된다.
{                                                  (const 객체는 const로 선언되지 않은 멤버함수를 호출하지 못한다는 뜻)
	const Point retobj(ref);                   
	ref.xpos -= 1;
	ref.ypos -= 1;
	return retobj;
}                                                  🎈🎈 다시한번 강조하지만, const가 앞에 붙은 함수가 반환하는 값은 const형이다.
                                                   
							   
int main()
{
	Point pos(3, 5);                            따라서 이러한 선언은 오류를 발생한다.
	(pos++)++;
	(pos--)--;                                  🎈🎈 이 부분이 내가 이해를 하지 못했던 부분이다.
							   
	return 0;                       ✅ Q.  const Point operator++(int) 함수가 반환한 값은 변경하지 못한다는 것은 알겠다.
}                                               그런데 왜 뒤에 이어서 또 다시 후위연산자(++)를 붙이면 오류가 뜨는 것일까?
	
					✅ A.  const Point operator++(int) 함수에서
						const가 선언이 안되어있을 때 오류가 안뜨는 것은, retobj가 바꿀 수 있는 값이기 때문이다.
						(retobj가 상수가 아니기 때문에 어떠한 함수도 호출할 수 있다.)
						const가 선언이 되어있을 때 오류가 뜨는 것은, retobj가 바꿀 수 없는 값이기 때문이다.
						(retobj가 상수이기에 const 함수만 호출할 수 있다.)
	
						그니까 여기서 ++은 후위연산자이기 때문에 const Point operator++(int) 함수가 호출된다.
						(poss++)++;  -->   (Point형 const 임시객체)++; 가 된다.
	
						결국 poss++은 상수, 즉 변할 수 없는 값이라는 것이다.
						그러한 값이 다시 한번 후위연산자(++)를 만나게 된다면, 당연히 오류를 발생시킨다.
						왜냐하면 상수 객체는 자신의 멤버변수의 값을 변경하는 것을 막기위해
						const형 함수만 호출하도록 하기때문이다. (const가 뒤에 붙은 함수)
						여기서 후위연산자(++) 또한 연산자 오버라이딩 개념으로 함수를 호출 하는 것이기에,
						const 객체는 ++을 통해 함수를 호출하지 못하게 된다.


                🎈🎈 그니까 코드를 이렇게 설계한 이유는 (poss++)++;  혹은 ++(pos++); 이러한 연산을 금지하기 위해서이다. 
							
                     사실 이러한 논리는 C++의 연산특성이 반영된 것이다.
							
			int num = 100;
			++(++num);   
			(++num)++;
			++(num++);   // ❌ 오류발생 
			(num++)++;   // ❌ 오류발생
                 
                     잘보면 후위연산자만 오류가 발생한다.
			     
	             이는 Lvalue와 Rvalue라는 C++의 개념이 있기 때문이다.
			     
	             이에 대한 설명은 : https://effort4137.tistory.com/entry/Lvalue-Rvalue

