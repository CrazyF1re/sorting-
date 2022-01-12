#pragma once

#include "Bool_vector.h"

class Bool_Matrix
{
	BoolVector* BV;
	int m, n;//m - ���������� ����� �������, n - ���������� �������� �������
	bool is_ok(int i, int);
	int Max(char** s, int m);//��������������� ������� ���������� � ������������
public:
	int Get_m();
	int Get_n();
	Bool_Matrix();
	Bool_Matrix(int m,int n);
	Bool_Matrix(char** s,int m);
	Bool_Matrix(const Bool_Matrix &x);//����������� �����������
	~Bool_Matrix();
	Bool_Matrix& operator =(const Bool_Matrix& x);
	void Scan(int m, int n);
	void Print();
	BoolVector operator[](int i);
	bool operator ==(Bool_Matrix& x);
	bool operator !=(Bool_Matrix& x);
	//��������� ����� ��� ���������� ��������� �������
	Bool_Matrix SetUp1(int i ,int j);
	Bool_Matrix SetUp0(int i, int j);
	Bool_Matrix Invert(int i, int j);

	Bool_Matrix SetUp1(int i, int j, int kol);// ���������� � 1 kol ��������� �  [i] ������ ������� � ������� j
	Bool_Matrix SetUp0(int i, int j, int kol);// �������� � 0 kol ��������� �  [i] ������ ������� � ������� j
	Bool_Matrix Invert(int i, int j, int kol);// ������������� kol ��������� �  [i] ������ ������� � ������� j

	//�������� ��� �������� ���������
	Bool_Matrix operator &(Bool_Matrix &x);//���������� ���������� ���� ������, ��������� ����� �������
	Bool_Matrix & operator &=(Bool_Matrix& x);//���������� ���������� ���� ������, ���������� *this
	Bool_Matrix operator |(Bool_Matrix& x);//���������� ���������� ���� ������, ��������� ����� �������
	Bool_Matrix& operator |=(Bool_Matrix& x);//���������� ���������� ���� ������, ���������� *this
	Bool_Matrix operator ^(Bool_Matrix& x);//���������� ����������� "���" ���� ������, ��������� ����� �������
	Bool_Matrix& operator ^=(Bool_Matrix& x);//���������� ������������ "���" ���� ������, ���������� *this
	Bool_Matrix operator ~();//�������� ���� �������
	Bool_Matrix ShiftRight(int i, int k);//����� ������ ��������� i-��� ������ �� k - ���, ��������� ����� �������
	Bool_Matrix ShiftRightEq(int i, int k);//����� ������ ��������� i-��� ������ �� k - ���, ���������� *this
	Bool_Matrix ShiftLeft(int i, int k);//����� ����� ��������� i-��� ������ �� k - ���, ��������� ����� �������
	Bool_Matrix ShiftLeftEq(int i, int k);//����� ����� ��������� i-��� ������ �� k - ���, ���������� *this
	BoolVector Conj();   	    	//���������� ���� ����� �������
	BoolVector Disj();         	//���������� ���� ����� �������
	BoolVector Xor();		    	//Xor ���� ����� �������
	friend std:: ostream& operator << (std::ostream& r, Bool_Matrix& x);
	friend std::istream& operator >> (std::istream& r, Bool_Matrix& x);

};