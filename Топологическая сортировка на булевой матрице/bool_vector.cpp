#include <iostream>
#include "bool_vector.h"
typedef unsigned char UC;
//int BoolVector::Input(char* a, int i_bv, int i_a, int k) 
//{
//	//char* a- вводимая строка
//	// int i_bv - индкс элемента в массиве bv
//	// int i_a - индекс с которого просматривается а
//	// int k - количество значащих цифр в элементе i_bv(bv[i_bv])
//	//BoolVector::BoolVector(char* s)
//	//BoolVector::BoolVector(char* s, int n)
//
//}
int BoolVector::Get_n()
{
	return this->n;
}
int BoolVector::Get_m()
{
	return this->m;
}
void BoolVector::Output(int i_bv, int k)
{
	UC mask = 1;
	mask <<= (k - 1);
	for (int i = 0; i < k; i++, mask >>= 1)
	{
		if (bv[i_bv] & mask) std::cout << "1 ";
		else std::cout << "0 ";
	}

}
BoolVector::BoolVector()
{
	n = 1;
	m = 1;
	bv = new UC[1];
	bv[0] = 0;
}
BoolVector::BoolVector(int n)
{
	m = n / 8;
	if (n % 8 != 0)m++;
	this->n = n;
	bv = new UC[m];
	for (int i = 0; i < m; i++)bv[i] = 0;
}
BoolVector::BoolVector(char* s)
{
	UC mask = 1;
	int len = strlen(s);
	n = strlen(s);
	m = n / 8;
	if (n % 8 != 0)
	{
		m++;
	}
	bv = new UC[m];
	for (int i = 0; i < m; i++)  bv[i] = 0;
	int count_s = len - 1;
	int count_bv = m - 1;
	while (count_s >= 0)
	{
		if (s[count_s] == '1') { bv[count_bv] |= mask; }
		mask <<= 1;
		count_s--;
		if (mask == 0) {
			mask = 1; count_bv--;
		}
	}
}
BoolVector::BoolVector(char* s, int n)
{
	UC mask = 1;
	int len = strlen(s);
	this->n = n;
	m = n / 8;
	if (n % 8) m++;
	bv = new UC[m];
	for (int i = 0; i < m; i++)bv[i] = 0;
	if (len > n)
	{
		int count_s = len - 1;
		int count_bv = m - 1;
		while (count_s >= len - n)
		{
			if (s[count_s] == '1')bv[count_bv] += mask;
			mask <<= 1;
			count_s--;
			if (mask == 0) {
				mask = 1; count_bv--;
			}
		}
	}
	else
	{
		int count_s = len - 1;
		int count_bv = m - 1;
		while (count_s >= 0)
		{
			if (s[count_s] == '1') { bv[count_bv] += mask; }
			mask <<= 1;
			count_s--;
			if (mask == 0) {
				mask = 1; count_bv--;
			}
		}
	}
}
BoolVector::BoolVector(const BoolVector& B)
{
	n = B.n;
	m = B.m;
	bv = new UC[m];
	for (int i = 0; i < m; i++)
	{
		bv[i] = B.bv[i];
	}
}
BoolVector BoolVector::operator =(const BoolVector& B)
{
	if (this != &B) {
		n = B.n;
		m = B.m;
		delete[]bv;
		bv = new UC[m];
		for (int i = 0; i < m; i++)
		{
			bv[i] = B.bv[i];
		}
	}
	return *this;
}
void BoolVector::Scan(int N)
{
	char* s = new char[N + 1];
	std::cout << "Enter boolean vector of length " << N << ": ";
	gets_s(s, N + 1);
	BoolVector temp(s);
	*this = temp;
}
void BoolVector::Print()
{
	int k = n % 8, i = 0;
	if (k) { Output(i, k); i++; }
	while (i < m)
	{
		Output(i, 8); i++;
	}
	std::cout << std::endl;
}
int BoolVector::Weight()
{
	int result = 0;
	int count = 0;
	while (count < m)
	{
		UC mask = 128;
		while (mask > 0)
		{
			if (mask & bv[count])result++;
			mask >>= 1;
		}
		count++;
	}
	return result;
}
UC BoolVector:: operator[](int pos)
{
	int M = pos / 8, k = pos % 8;
	UC mask = 1 << k;
	if (mask & bv[m - 1 - M])return '1';
	else return '0';
}
bool BoolVector:: operator == (BoolVector& B)
{
	int i = (m < B.m) ? m : B.m;
	i--;
	if (n != B.n)return 0;
	while (i >= 0)
	{
		if (bv[i] != B.bv[i])return 0;
		i--;
	}
	return 1;
}
bool BoolVector:: operator != (BoolVector& B)
{
	int i = (m < B.m) ? m : B.m;
	i--;
	if (n != B.n)return 1;
	while (i >= 0)
	{
		if (bv[i] != B.bv[i])return 1;
		i--;
	}
	return 0;
}
bool BoolVector:: operator < (BoolVector& y)
{
	int count = m < y.m ? m : y.m;
	int flag = 0;
	for (int i = count - 1; i >= 0; i--)
	{
		if (bv[i] <= y.bv[i]) flag++;
		else flag--;
	}
	if (m == abs(flag))
	{
		if (flag)return 1;
		else return 0;
	}
	else
	{
		std::cout << "disparate bool vectors";
		return -1;
	}
}
bool BoolVector:: operator > (BoolVector& y)
{
	int count = m < y.m ? m : y.m;
	int flag = 0;
	for (int i = count - 1; i >= 0; i--)
	{
		if (bv[i] > y.bv[i]) flag++;
		else flag--;
	}
	if (m == abs(flag))
	{
		if (flag)return 1;
		else return 0;
	}
	else
	{
		std::cout << "disparate bool vectors";
		return -1;
	}
}
BoolVector BoolVector:: operator & (BoolVector& x)
{
	int N = n, j_res = m - 1;
	if (N > x.n)N = x.n; j_res = x.m - 1;
	BoolVector Res(N);
	int j, j_x;
	for (j = m - 1, j_x = x.m - 1; j_res >= 0; j--, j_x--, j_res--)
	{
		Res.bv[j_res] = bv[j] & x.bv[j_x];
	}
	return Res;

}
BoolVector& BoolVector::operator &= (BoolVector& x)
{
	int j, j_x, j_res = n < x.n ? m - 1 : x.m - 1;
	for (j = m - 1, j_x = x.m - 1; j_res >= 0; j--, j_x--, j_res--)
	{
		bv[j_res] = bv[j] & x.bv[j_x];
	}
	return *this;
}
BoolVector BoolVector:: operator |(BoolVector& x)
{
	BoolVector ans;
	int s = x.m - 1;
	if (n > x.n)ans = *this;
	else
	{
		ans = x; s = m - 1;
	}
	int i = m - 1, j = x.m - 1;
	while (s >= 0)
	{
		ans.bv[s] = bv[i] | x.bv[j];
		s--; i--; j--;
	}
	return ans;
}
BoolVector& BoolVector::operator |=(BoolVector& x)
{
	BoolVector res;
	res = *this | x;
	*this = res;
	return *this;
}
BoolVector BoolVector:: operator ^(BoolVector& x)
{
	BoolVector ans;
	int s = x.m - 1;
	if (n > x.n)ans = *this;
	else
	{
		ans = x; s = m - 1;
	}
	int i = m - 1, j = x.m - 1;
	while (s >= 0)
	{
		ans.bv[s] = bv[i] ^ x.bv[j];
		s--; i--; j--;
	}
	return ans;
}
BoolVector& BoolVector:: operator ^=(BoolVector& x)
{
	BoolVector res;
	res = *this ^ x;
	*this = res;
	return *this;
}
BoolVector  BoolVector::operator ~()
{
	for (int i = 0; i < m; i++)
	{
		bv[i] = ~bv[i];
	}
	return *this;
}
BoolVector BoolVector:: operator <<(int a)
{
	BoolVector ans(n);
	try
	{
		if (a < 0)throw "incorrect data";
		if (a < n)
		{
			for (int i = n - 1; i >= a; i--)
			{
				if (this->operator[](i - a) == '1')ans.SetUp1(i);
			}
		}
		return ans;
	}
	catch (char* s)
	{
		std::cout << s << std::endl;
		return *this;
	}
}
BoolVector& BoolVector:: operator <<=(int a)
{
	try
	{
		if (a < 0)throw "incorrect data";
		if (a < n)
		{
			for (int i = n - 1; i >= a; i--)
			{
				if (this->operator[](i - a) == '1')this->SetUp1(i);
				else this->SetUp0(i);
			}
			for (int i = a - 1; i > 0; i--) this->SetUp0(i);
		}
		return *this;
	}
	catch (char* s)
	{
		std::cout << s << std::endl;
		return *this;
	}

}
BoolVector BoolVector:: operator >>(int a)
{
	BoolVector ans(n);
	try
	{
		if (a < 0)throw "incorrect data";
		if (a < n)
		{
			for (int i = 0; i < n - a; i++)
			{
				if (this->operator[](i + a) == '1')ans.SetUp1(i);
			}
		}
		return ans;
	}
	catch (char* s)
	{
		std::cout << s << std::endl;
		return *this;
	}
}
BoolVector BoolVector:: operator >>=(int a)
{
	try
	{
		if (a < 0)throw "incorrect data";
		if (a < n)
		{
			for (int i = 0; i < n - a; i++)
			{
				if (this->operator[](i + a) == '1')this->SetUp1(i);
				else this->SetUp0(i);
			}
			for (int i = n - a; i < n; i++) this->SetUp0(i);
		}
		return *this;
	}
	catch (char* s)
	{
		std::cout << s << std::endl;
		return *this;
	}
}
BoolVector BoolVector::SetUp1(int pos)
{
	if ((pos < 0) | (pos > n))
	{
		std::cout << "Incorrect index of component" << std::endl;
		return 0;
	}
	int N = pos / 8, M = pos % 8;
	UC mask = 1 << M;
	bv[m - N - 1] = bv[m - N - 1] | mask;
	return *this;
}
BoolVector BoolVector::SetUp0(int pos)
{
	if ((pos < 0) | (pos > n))
	{
		std::cout << "Incorrect index of component" << std::endl;
		return 0;
	}
	int N = pos / 8, M = pos % 8;
	UC mask = 1 << M;
	mask = ~mask;
	bv[m - N - 1] = bv[m - N - 1] & mask;
	return *this;
}
BoolVector BoolVector::Invert(int pos)
{
	if ((pos < 0) | (pos > n))
	{
		std::cout << "Incorrect index of component" << std::endl;
		return 0;
	}
	int N = pos / 8, M = pos % 8;
	UC mask = 1 << M;
	bv[m - N - 1] = mask ^ bv[m - N - 1];
	return *this;
}
BoolVector BoolVector::SetUp1(int kol, int pos)
{
	if ((pos < 0) | (pos > n))
	{
		std::cout << "Incorrect index of component" << std::endl;
		return 0;
	}
	int M = pos % 8;
	UC mask = 1 << M;
	for (int i = pos; i < pos + kol; i++)
	{
		bv[m - i / 8 - 1] = mask | bv[m - i / 8 - 1];
		mask <<= 1;
		if (mask == 0)mask = 1;
	}
	return *this;
}
BoolVector BoolVector::SetUp0(int kol, int pos)
{
	if ((pos < 0) | (pos > n))
	{
		std::cout << "Incorrect index of component" << std::endl;
		return 0;
	}
	int M = pos % 8;
	UC mask = 1 << M;
	mask = ~mask;
	for (int i = pos; i < pos + kol; i++)
	{
		bv[m - i / 8 - 1] = mask & bv[m - i / 8 - 1];
		mask <<= 1;
		mask++;
		if (mask == 255)
		{
			mask = 1;
			mask = ~mask;
		}
	}
	return *this;
}
BoolVector BoolVector::Invert(int kol, int pos)
{
	if ((pos < 0) | (pos > n))
	{
		std::cout << "Incorrect index of component" << std::endl;
		return 0;
	}
	int  M = pos % 8;
	UC mask = 1 << M;
	for (int i = pos; i < pos + kol; i++)
	{
		bv[m - i / 8 - 1] = mask ^ bv[m - i / 8 - 1];
		mask <<= 1;
		if (mask == 0)mask = 1;
	}
	return *this;
}
std::ostream& operator << (std::ostream& r, BoolVector& x)
{
	for (int i = 0; i < x.m; i++)
	{
		r << x.bv[i];
	}
	return r;
}
std::istream& operator >> (std::istream& r, BoolVector& x)
{
	char* temp = new char[x.m];
	r >> temp;
	BoolVector A(temp);
	x = A;
	return r;
}