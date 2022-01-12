#pragma once
typedef unsigned char UC;
#include <iostream>
class BoolVector 
{
	int n, m; 
	UC *bv;
	int Input(char * s,int a, int b, int c);//???
	void Output(int i_bv, int k);
public:
	int Get_n();
	int Get_m();
	BoolVector();
	BoolVector(int n);
	BoolVector(char* s);
	BoolVector(char* s, int n);
	BoolVector(const BoolVector& B);
	BoolVector operator =(const BoolVector& B);
	~BoolVector() { delete[]bv; }
	void Scan(int N);
	void Print();
	int Weight();
	UC operator[](int k);
	bool operator == (BoolVector& B);
	bool operator != (BoolVector& B);
	bool operator < (BoolVector& B);
	bool operator > (BoolVector& B);
	BoolVector operator & (BoolVector& x);
	BoolVector& operator &= (BoolVector& X);
	BoolVector operator |(BoolVector& x);
	BoolVector& operator |=(BoolVector& x);
	BoolVector operator ^(BoolVector& x);
	BoolVector& operator ^=(BoolVector& x);
	BoolVector operator ~();
	BoolVector operator <<(int a);
	BoolVector& operator <<=(int a);
	BoolVector operator >>(int a);
	BoolVector operator >>=(int a);
	BoolVector SetUp1(int pos);
	BoolVector SetUp0(int pos);
	BoolVector Invert(int pos);
	BoolVector SetUp1(int kol, int pos);
	BoolVector SetUp0(int kol, int pos);
	BoolVector Invert(int kol, int pos);
	friend std::ostream& operator << (std::ostream& r, BoolVector& x);
	friend std::istream & operator >> (std::istream & r, BoolVector &x);


};