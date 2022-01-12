#include <iostream>
#include "graph.h"
int main()
{
	Graph A;
	A.Form_graph();
	A.Print();
	cout << '\n';
	Graph B;
	B.Sort_graph(A);
	B.Print();
}
//2 1
//4 5
//5 1
//5 3
//6 2
//6 3
//6 5
//7 1
//0 0
