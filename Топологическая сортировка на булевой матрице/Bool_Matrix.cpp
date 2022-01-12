#include "Bool_Matrix.h"
int Bool_Matrix::Get_m() 
{
	return this->m;
}
int Bool_Matrix::Get_n()
{
	return this->n;
}
bool Bool_Matrix::is_ok(int i, int j) 
{
	if (i >= 0 && i < m && j >= 0 && j < n) return 1;
	return 0;
}
int Bool_Matrix::Max(char** s, int m) 
{
	int max, i;
	max = strlen(s[0]);
	for (i = 1; i < m; i++) 
	{
		int temp = strlen(s[i]);
		if (max < temp)max = temp;
	}
	return max;
}//вспомогательная функция необходима в конструкторе
Bool_Matrix::Bool_Matrix() 
{
	m = 1; n = 1;
	BV = new BoolVector[1];	
	BV[0] = BoolVector(n);
}
Bool_Matrix::Bool_Matrix(int M, int N) 
{
	m = M; n = N;
	BV = new BoolVector[m];
	BoolVector B(n);
	for (int i = 0; i < m; i++) BV[i] = B;
}
Bool_Matrix::Bool_Matrix(char** s, int M) 
{
	m = M; n = Max(s, M);
	BV = new BoolVector[m];
	for (int i = 0; i < m; i++)BV[i] = BoolVector(s[i], n);
}
Bool_Matrix::Bool_Matrix(const Bool_Matrix& x) 
{
	m = x.m; n = x.n;
	BV = new BoolVector[m];
	for (int i = 0; i < m; i++) BV[i] = x.BV[i];
}
Bool_Matrix::~Bool_Matrix() { delete[] BV; }
Bool_Matrix& Bool_Matrix::operator =(const Bool_Matrix& x)
{
	delete[] BV;
	m = x.m; n = x.n;
	BV = new BoolVector[m];
	for (int i = 0; i < m; i++) BV[i] = x.BV[i];
	return *this;
}
void Bool_Matrix::Scan(int M, int N) 
{
	if (m != M || n != N) 
	{
		delete[]BV;
		m = M;
		BV = new BoolVector[m];
	}
	n = N;
	std::cout << "enter Boolean matrix size of " << m << 'x' << n << ':';
	std:: cout<< std::endl;
	for (int i = 0; i < m; i++)BV[i].Scan(N);
}
void Bool_Matrix::Print() 
{
	for (int i = 0; i < m; i++) 
	{
		BV[i].Print();
	}
}
BoolVector Bool_Matrix::operator[](int i)
{
	try
	{
		if (i < 0)throw 0;
		if (i >= m) throw "incorrect index (index >= m)";
		return BV[i];
	}
	catch (int j)
	{
		std::cout << j << std::endl;
	}
}
bool Bool_Matrix:: operator ==(Bool_Matrix& x) 
{
	int i = 0;
	while (i < m &&BV[i] == x.BV[i]  )i++;
	if (i == m)return 1;
	return 0;

}
bool Bool_Matrix::operator !=(Bool_Matrix& x) 
{
	int i = 0;
	while (i < m && BV[i] == x.BV[i])i++;
	if (i == m)return 0;
	return 1;
}
Bool_Matrix Bool_Matrix::SetUp1(int i, int j) 
{
	if (is_ok(i, j))BV[i].SetUp1(j);
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::SetUp0(int i, int j) 
{
	if (is_ok(i, j))BV[i].SetUp0(j);
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::Invert(int i, int j) 
{
	if (is_ok(i, j))BV[i].Invert(j);
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::SetUp1(int i, int j, int kol) 
{
	if (is_ok(i, j))BV[i].SetUp1(kol,j);
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::SetUp0(int i, int j, int kol) 
{
	if (is_ok(i, j))BV[i].SetUp0(kol, j);
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::Invert(int i, int j, int kol) 
{
	if (is_ok(i, j))BV[i].Invert(kol,j);
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::operator &(Bool_Matrix& x) 
{
	Bool_Matrix ans(m > x.m ? m : x.m, n);
	int temp = m > x.m ? x.m : m;
	ans = *this;
	for (int i = 0; i < temp; i++)
	{
		ans.BV[i] &= x.BV[i];
	}
	return ans;
}
Bool_Matrix& Bool_Matrix:: operator &=(Bool_Matrix& x) 
{
	int temp;
	if (m > x.m)
	{
		temp = x.m;
	}
	else
	{
		temp = m;
		BoolVector* t = new BoolVector[temp];
		for (int i = 0; i < temp; i++)t[i] = BV[i];
		delete[]BV;
		BV = t;
	}
	for (int i = 0; i < temp; i++)
	{
		this->BV[i] &= x.BV[i];
	}
	return *this;
}
Bool_Matrix Bool_Matrix::operator |(Bool_Matrix& x) 
{
	Bool_Matrix ans(m > x.m? m:x.m,n);
	int temp = m>x.m? x.m:m;
	ans = *this;
	for (int i = 0; i < temp; i++)
	{
		ans.BV[i] |= x.BV[i];
	}
	return ans;
}
Bool_Matrix& Bool_Matrix::operator |=(Bool_Matrix& x) 
{
	int temp;
	if (m > x.m)
	{
		temp = x.m;
	}
	else
	{
		temp = m;
		BoolVector* t = new BoolVector[x.m];
		for (int i = 0; i < temp; i++)t[i] = BV[i];
		delete[]BV;
		BV = t;
	}
	for (int i = 0; i < temp; i++)
	{
		this->BV[i] |= x.BV[i];
	}
	return *this;
}
Bool_Matrix Bool_Matrix::operator ^(Bool_Matrix& x) 
{
	Bool_Matrix ans(m > x.m ? m : x.m, n);
	int temp = m > x.m ? x.m : m;
	ans = *this;
	for (int i = 0; i < temp; i++)
	{
		ans.BV[i] ^= x.BV[i];
	}
	return ans;
}
Bool_Matrix& Bool_Matrix::operator ^=(Bool_Matrix& x) 
{
	int temp;
	if (m > x.m)
	{
		temp = x.m;
	}
	else
	{
		temp = m;
		BoolVector* t = new BoolVector[x.m];
		for (int i = 0; i < temp; i++)t[i] = BV[i];
		delete[]BV;
		BV = t;
	}
	for (int i = 0; i < temp; i++)
	{
		this->BV[i] ^= x.BV[i];
	}
	return *this;
}
Bool_Matrix Bool_Matrix::operator ~() 
{
	for (int i = 0; i < m; i++) 
	{
		BV[i] = ~BV[i];
	}
	return *this;
}
Bool_Matrix Bool_Matrix::ShiftRight(int i, int k) 
{
	Bool_Matrix ans (*this);
	if (is_ok(i, 0))ans.BV[i] >>=k;
	else std::cout << "incorrect index of element";
	return ans;
}
Bool_Matrix Bool_Matrix::ShiftRightEq(int i, int k) 
{
	if (is_ok(i, 0))BV[i] >>= k;
	else std::cout << "incorrect index of element";
	return *this;
}
Bool_Matrix Bool_Matrix::ShiftLeft(int i, int k) 
{
	Bool_Matrix ans(*this);
	if (is_ok(i, 0))ans.BV[i] = ans.BV[i] <<k;
	else std::cout << "incorrect index of element";
	return ans;
}
Bool_Matrix Bool_Matrix::ShiftLeftEq(int i, int k) 
{
	if (is_ok(i, 0)) { BV[i] <<= k; }
	else std::cout << "incorrect index of element";
	return *this;
}
BoolVector Bool_Matrix::Conj() 
{
	BoolVector ans = BV[0];
	for (int i = 1; i < m; i++) 
	{
		ans &= BV[i];
	}
	return ans;
}   	
BoolVector Bool_Matrix::Disj() 
{
	BoolVector ans = BV[0];
	for (int i = 1; i < m; i++)
	{
		ans |= BV[i];
	}
	return ans;
}
BoolVector Bool_Matrix::Xor() 
{
	BoolVector ans;
	for (int i = 0; i < m; i++)
	{
		ans ^= BV[i];
	}
	return ans;
}
std::ostream& operator << (std::ostream& r, Bool_Matrix& x) 
{
	for (int i = 0; i < x.m; i++)
	{
		 x.BV[i].Print();
	}
	return r;
}
std::istream& operator >> (std::istream& r, Bool_Matrix& x) 
{
	std::cout << "Enter the size of matix: ";
	int M, N;
	std::cin >> M >> N;
	x.Scan(M, N);
	return r;
}
