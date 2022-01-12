#include <iostream>
void create_numbers(int n, int* N)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        N[i] = rand() % 100;
    }
    if (n < 100) {
        for (int i = 0; i < n; i++)
        {
            std::cout << " " << N[i];

        }
        std::cout << std::endl;
    }
}
void algoritm2(int n, int* N)
{
    int i = 1;
    while (i < n)
    {
        int L = 0, R = i, x = N[i];
        while (L < R) 
        {
            int m = (L + R) / 2;
            if (x < N[m])
            {
                R = m;
            }
            else L = m + 1;
        }
        int k = i - 1;
        while (k >= R) 
        {
            N[k + 1] = N[k];
            k--;
        }
        N[k + 1] = x;
        i++;
    }
    if (n < 100) {
        for (int i = 0; i < n; i++)
        {
            std::cout << " " << N[i];

        }
        std::cout << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL,"Russian");
    int n;
    std::cout << "Введите количество чисел: ";
    std::cin >> n;
    int* N = (int*)malloc(n * sizeof(int));
    create_numbers(n,N);
    clock_t start = clock();
    algoritm(n,N);
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nThe time: %f seconds\n", seconds);
}
