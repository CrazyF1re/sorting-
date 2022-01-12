#include <iostream>
#include "Bool_Matrix.h"
using namespace std;

int main()
{
	int n;
	cout << "Enter size of matrix: ";
	cin >> n;
	getchar();
	Bool_Matrix X(n, n);
	X.Scan(n,n);
	X.Print();
	BoolVector d(n);//дизъюнкция всех строк
	BoolVector w(n);//?
	BoolVector v0(n);//обработанные вершины
	BoolVector v1(n);//v0^w
	int* res = new int[n];
	int count = 0;
	for (int i = 0; i < n; i++) res[i] = 0;
	while (res[n - 1] == 0)
	{
		v0 = w;
		d = X.Disj();
		w = (~d); ~d;
		v1 = v0 ^ w;
		for (int j = n-1; j >=0; j--) 
		{
			if (v1[j] == '1') {
				res[count] = n-j;
				count++;
				X.SetUp0(n-j-1, 0, n);
			}
		}
	}
	for (int i = 0; i < n; i++)cout << res[i];
	cout << endl;
}
//000101000
//101000100
//000100000
//000000000
//001000000
//000010000
//000000010
//000010000
//000111000