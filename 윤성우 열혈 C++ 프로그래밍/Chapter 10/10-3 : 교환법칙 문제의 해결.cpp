 
        A + B = B + A   <-- κ΅νλ²μΉ
        
---------------------------------------------------------------------

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
	Point operator*(int times)
	{
		Point pos(xpos * times, ypos * times);
		return pos;
	}
};                             

int main()
{
	Point pos(1, 2);  
	Point cpy;                           
	
	cpy = pos * 3;         // pos.operator(3); 
	cpy.ShowPosition();

	cpy = pos * 3 * 2;     // pos.operator(6);
	cpy.ShowPosition();

	return 0;
}

                         ππ μμ μ½λμμ λ¬Έμ λ κ³±μμ κ΅νλ²μΉμ΄ μ±λ¦½νμ§ μλλ€λ κ²μ΄λ€.
                         
                              pos * 3 μ pos.operator(3); μΌλ‘ ν¨μνΈμΆμ΄ μ§νλλ€.
                              κ·Έλ¬λ λ§μ½ 
                              3 * posλΌκ³  νλ€λ©΄..???   3.operator(pos) μ΄λ°μμΌλ‘ ν¨μκ° νΈμΆμ΄ λλ€.
                              μ΄λ λΉμ°ν μ€λ₯κ° λ°μνλ€.
                            
                              κ·Έλ λ€λ©΄ μ΄λ₯Ό ν΄κ²°νκΈ° μν΄μλ μ΄λ»κ² μ½λλ₯Ό μ€κ³ν΄μΌν κΉ?
                           
                           
                           
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
	Point operator*(int times)
	{
		Point pos(xpos * times, ypos * times);
		return pos;
	}
};

Point operator*(int times, Point& ref)                // ππ cpy = 3 * pos; νμμ κ³±μμ°μ°μ΄ κ°λ₯ νλ €λ©΄,
{                                                     //       μ μ­ν¨μμ ννλ‘ κ³±μ μ°μ°μλ₯Ό μ€λ²λ‘λ© νλ μ λ°μ μλ€.
	return ref * times;  // ref.operator*(times);
}

int main()
{
	Point pos(1, 2);
	Point cpy;
	
	cpy = 3 * pos;           // operator*(3, pos);
	cpy.ShowPosition();

	cpy = 2 * pos * 3;       // operator*(2, pos);   -->   (posμ μ°Έμ‘°μ).operator*(3);
	cpy.ShowPosition();

	return 0;
}
                         
