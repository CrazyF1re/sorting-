#include "my_lib.h"
#include <iostream>
int sum(int a, int b) 
{
	return a + b;
}
int numb( int a)
{
    
    int n = rand() % a;
    return n;
}
int Max(int n,int* N)
{
    int ans = N[0];
    for (int i = 1; i < n; i++) 
    {
        if (N[i] > ans)ans = N[i];
    }
    return ans;
}
int Max(int lines, int columns, int** N) 
{
    int ans = N[0][0];
    for (int i = 0; i < lines; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            if (N[i][j] > ans)ans = N[i][j];
        }
    }
    return ans;
}
void record(int n, int m, int* N)
{
    for (int i = 0; i < m + 1; i++)
    {
        unsigned int mask = 1 << (n - 1);//маска
        char v[32];//вектор
        fgets(v, n + 2, stdin);//ввод вектора
        N[i] = 0;
        for (int j = 0; j < n; j++)
        {

            if (v[j] == '1') { N[i - 1] = N[i - 1] | mask; mask = mask >> 1; }
            else mask = mask >> 1;
        }
    }
}
void print(int n, int m, int* N)
{
    for (int i = 0; i < m; i++)
    {
        unsigned int mask = 1 << (n - 1);
        for (int j = 0; j < n; j++)
        {
            if (N[i] & mask) printf("1 ");
            else printf("0 ");
            mask = mask >> 1;
        }
        printf("\n");
    }
}
void fill_massive(int n,int*N) 
{
	for (int i = 0; i < n; i++)N[i] = rand()%1000;
}