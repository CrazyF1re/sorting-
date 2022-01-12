#pragma once

#include "Bool_vector.h"

class Bool_Matrix
{
	BoolVector* BV;
	int m, n;//m - количество строк матрицы, n - количество столбцов матрицы
	bool is_ok(int i, int);
	int Max(char** s, int m);//вспомогательная функция необходима в конструкторе
public:
	int Get_m();
	int Get_n();
	Bool_Matrix();
	Bool_Matrix(int m,int n);
	Bool_Matrix(char** s,int m);
	Bool_Matrix(const Bool_Matrix &x);//конструктор копирования
	~Bool_Matrix();
	Bool_Matrix& operator =(const Bool_Matrix& x);
	void Scan(int m, int n);
	void Print();
	BoolVector operator[](int i);
	bool operator ==(Bool_Matrix& x);
	bool operator !=(Bool_Matrix& x);
	//изменение одной или нескольких компонент матрицы
	Bool_Matrix SetUp1(int i ,int j);
	Bool_Matrix SetUp0(int i, int j);
	Bool_Matrix Invert(int i, int j);

	Bool_Matrix SetUp1(int i, int j, int kol);// установить в 1 kol элементов в  [i] строке начиная с позиции j
	Bool_Matrix SetUp0(int i, int j, int kol);// сбросить в 0 kol элементов в  [i] строке начиная с позиции j
	Bool_Matrix Invert(int i, int j, int kol);// инвертировать kol элементов в  [i] строке начиная с позиции j

	//операции над булевыми матрицами
	Bool_Matrix operator &(Bool_Matrix &x);//построчная конъюнкция двух матриц, создается новая матрица
	Bool_Matrix & operator &=(Bool_Matrix& x);//построчная конъюнкция двух матриц, изменяется *this
	Bool_Matrix operator |(Bool_Matrix& x);//построчная дизъюнкция двух матриц, создается новая матрица
	Bool_Matrix& operator |=(Bool_Matrix& x);//построчная дизъюнкция двух матриц, изменяется *this
	Bool_Matrix operator ^(Bool_Matrix& x);//построчное исключающее "или" двух матриц, создается новая матрица
	Bool_Matrix& operator ^=(Bool_Matrix& x);//построчное ислключающее "или" двух матриц, изменяется *this
	Bool_Matrix operator ~();//инверсия всей матрицы
	Bool_Matrix ShiftRight(int i, int k);//сдвиг вправо элементов i-той строки на k - бит, создается новая матрица
	Bool_Matrix ShiftRightEq(int i, int k);//сдвиг вправо элементов i-той строки на k - бит, изменяется *this
	Bool_Matrix ShiftLeft(int i, int k);//сдвиг влево элементов i-той строки на k - бит, создается новая матрица
	Bool_Matrix ShiftLeftEq(int i, int k);//сдвиг влево элементов i-той строки на k - бит, изменяется *this
	BoolVector Conj();   	    	//конъюнкция всех строк матрицы
	BoolVector Disj();         	//дизъюнкция всех строк матрицы
	BoolVector Xor();		    	//Xor всех строк матрицы
	friend std:: ostream& operator << (std::ostream& r, Bool_Matrix& x);
	friend std::istream& operator >> (std::istream& r, Bool_Matrix& x);

};
