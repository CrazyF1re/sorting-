#include <iostream>
void fill_massive(int n,int*N) 
{
    for (int i = 0; i < n; i++)std::cin >> N[i];
}
void QuickSort(int* N, int first, int last,int n)// сортировка массива
{
    if (first < last)
    {
        int left = first, right = last, middle = N[(left + right) / 2];
        while (left <= right)
        {
            while (N[left] < middle) left++;
            while (N[right] > middle) right--;
            if (left <= right)
            {
                int a = N[left];
                N[left] = N[right];
                N[right] = a;
                left++;
                right--;
            }
        } 
        for (int i = 0; i < n; i++)std::cout << N[i] << ' ';
        std::cout << std::endl;
        QuickSort(N, first, right, n);
        QuickSort(N, left, last,n);
    }
}
int main()
{
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int n =0;
	std::cout << "Введите количество элементов: ";
	std::cin >> n;
	int *N = new int[n];
	fill_massive(n, N);
    for (int i = 0; i < n; i++)std::cout <<" "<< N[i];
    std::cout << std::endl;
    QuickSort(N, 0, n - 1,n);
    for (int i = 0; i < n; i++)std::cout <<" " <<N[i];
    std::cout << std::endl;
}
