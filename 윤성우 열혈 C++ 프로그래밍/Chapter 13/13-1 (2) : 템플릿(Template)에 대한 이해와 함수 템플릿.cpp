๐ข ํจ์ ํํ๋ฆฟ์ ํน์ํ(Specialization)

#include <iostream>
using namespace std;

template <class T>
T Max(T a, T b)
{
	return a > b ? a : b;
}

int main()
{
	cout << Max(11, 15) << endl;            // 15 ์ถ๋ ฅ
	cout << Max('T', 'Q') << endl;          // T  ์ถ๋ ฅ
	cout << Max(3.5, 7.5) << endl;          // 7.5 ์ถ๋ ฅ
	cout << Max("Simple", "Ace") << endl;   // Simple ์ถ๋ ฅ  ๐๐ ์ฃผ์ ๊น๊ฒ ๋ณด๊ธฐ
	
	return 0;
}                            โ cout << Max("Simple", "Ace") << endl; <-- ์ด ๋ฌธ์ฅ์ ์ ๋๋ก๋ ๋น๊ต ๊ฒฐ๊ณผ๋ฅผ ๋ฐํํ  ์ ์๋ค.
                                ์๋ํ๋ฉด "Simple"๊ณผ "Ace"๋ const char* ํ์ด๋ฏ๋ก ๊ทธ์  ๋จ์ํ ์ฃผ์ ๊ฐ์ ๋น๊ต๊ฒฐ๊ณผ๊ฐ ๋ฐํ๋๊ธฐ ๋๋ฌธ์ด๋ค.
  
                                ๋ฐ๋ผ์ ๋ฌธ์์ด์ ๊ธธ์ด๋น๊ต ๋๋ ์ฌ์ ํธ์ฐฌ ์์์ ๋น๊ต๊ฐ ๋ชฉ์ ์ด๋ผ๋ฉด ๋ฐ๋ก ํํ๋ฆฟ ํจ์๋ฅผ ๊ตฌ์ฑํด์ผ ํ๋ค.
  
  
template<> 
const char* Max(const char* a, const char* b)   
{
	return strlen(a) > strlen(b) ? a : b;
}
  
     ๐๐ "const char* ํ ํจ์๋ ๋ด๊ฐ ์ด๋ ๊ฒ ์ ์๋ฅผ ํ๋, const char* ํ ํํ๋ฆฟ ํจ์๊ฐ ํ์ํ ๊ฒฝ์ฐ์๋ ๋ณ๋๋ก ๋ง๋ค์ง ๋ง๊ณ  ์ด๊ฒ์ ์จ๋ผ!"

---------------------------------------------------------------------
  
#include <iostream>
using namespace std;

template <class T>
T Max(T a, T b)
{
	return a > b ? a : b;
}

template<>
const char* Max(const char* a, const char* b)  // ๋ฌธ์์ด ๊ธธ์ด ๋น๊ต ํจ์
{
	return strlen(a) > strlen(b) ? a : b;
}

template<>
char* Max(char* a, char* b)   // ์ฌ์ ํธ์ฐฌ ์์์ ๋น๊ต ํจ์
{
	return strcmp(a, b) < 0 ? a : b;
}

int main()
{
	cout << Max(11, 15) << endl;
	cout << Max('T', 'Q') << endl;
	cout << Max(3.5, 7.5) << endl;
	cout << Max("Simple", "Ace") << endl;

	char str1[] = "Simple";
	char str2[] = "Best";
	cout << Max(str1, str2) << endl;
	
	return 0;
}                               โ Q. ๊ทผ๋ฐ ํํ๋ฆฟ์ ํน์ํ๋ฅผ ์ํค์ง ์๊ณ  ๊ทธ๋ฅ ์ผ๋ฐ ํจ์๋ฅผ ์ ์ธํ๋ฉด ๋๋๊ฑฐ ์๋๊ฐ?
	
	                            A. ์ ์ด์ Max() ๋ผ๋ ํจ์ ํํ๋ฆฟ์ด ์กด์ฌํ๋ ์ํฉ์์ ๊ตณ์ด ๊ฐ์ ์ด๋ฆ์ ์ผ๋ฐ ํจ์๋ฅผ ์ ์ํ๊ธฐ๋ณด๋ค๋,
                                       ์ด ํจ์๊ฐ ํจ์ ํํ๋ฆฟ์ด๋ผ๋ ๊ฒ์ ๋ช์ํด์ฃผ๋ฉด์ "์ด๋ฌํ ๊ฒฝ์ฐ์๋ ์ด ํํ๋ฆฟ ํจ์๋ฅผ ์จ๋ผ" ๋ผ๊ณ 
				       ์ ์๋ฅผ ๋ด๋ ค์ฃผ๋ ๊ฒ์ด ์ฝ๋๋ฅผ ์ฝ๋ ์ฌ๋๊ณผ ๋์์ธ์ ์ธ ๋ถ๋ถ์์ ํจ์ฌ ๋ซ์ง ์์๊น?
  
----------------------------

๐๐ ์์ ์ฝ๋์์ ํจ์์ ์๋ฃํ ์ ๋ณด๋ฅผ ์ด๋ฐ์์ผ๋ก ๋ช์ํด์ฃผ๋ ๊ฒ์ด ์ข๋ค.
	
template<>
const char* Max<const char*>(const char* a, const char* b)  // ๋ฌธ์์ด ๊ธธ์ด ๋น๊ต ํจ์
{
	return strlen(a) > strlen(b) ? a : b;
}

template<>
char* Max<char*>(char* a, char* b)   // ์ฌ์ ํธ์ฐฌ ์์์ ๋น๊ต ํจ์
{
	return strcmp(a, b) < 0 ? a : b;
}
                         
