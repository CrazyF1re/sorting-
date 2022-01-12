#include <iostream>
#include <math.h>
#include "my_lib.h"
void BitSort(int* N, int first, int last, int digit)// сортировка массива
{
    if (first < last && digit>=0)
    {
        int mask = 1<<digit;
        int left = first, right = last, middle = N[(left + right) / 2];
        while (left <= right)
        {
            while (!(N[left] & mask)) left++;
            while (N[right] &mask) right--;
            if (left <= right)
            {
                int a = N[left];
                N[left] = N[right];
                N[right] = a;
                left++;
                right--;
            }
        }
        digit--;
        BitSort(N, first, right,digit);
        BitSort(N, left, last,digit);
    }
}
    
int main()
{
    srand(time(0));
    int n, * N;//n - количество числе, N - массив для чисел
    std::cout << "Enter number of counts: ";
    std::cin >> n;
    N = new int[n];
    fill_massive(n, N);//заполняем массив числами
    int max = Max(n, N);//находим максимальный элемент
    int mask = 65536,count =16;
    while (!(max & mask) )//считаем количество битов в максимальном элементе
    {
        count--;
        mask >>= 1;
    }
    for (int i = 0; i < n; i++)std::cout << N[i]<<"\t";//выводим массив до сортировки
    std::cout << std::endl;
    BitSort(N, 0, n-1,count);//битовая сортировка
    for (int i = 0; i < n; i++)std::cout << N[i] << "\t";//выводим массив после сортировки
    std::cout << std::endl;
}
//через рекурсию