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
void algoritm(int n, int* N,int step)
{
    for (int a=0; a < step; a++)
    {
        int i = a+step;
        while (i < n)
        {

            int j = i - step;
            int x = N[i];
            while (j >= 0)
            {
                if (N[j] > x)
                {
                    N[j + step] = N[j];
                    j-=step;
                }
                else break;
            }
            N[j + step] = x;
            i+=step;
        }
    }
}
void Sedjvik_distance( int n, int* S) 
{
    for (int i = 0; i < n; i++) 
    {
        if (i % 2 == 0) S[i] = 9 * pow(2, i) - 9 * pow(2, i / 2) + 1;
        else S[i] = 8 * pow(2, i) - 6 * pow(2, (i + 1) / 2) + 1;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    std::cout << "Введите количество чисел: ";
    std::cin >> n;
    std::cout << std::endl;
    int* N = (int*)malloc(n * sizeof(int));
    int Sedj[15];
    create_numbers(n, N);
    int i = 0;
    Sedjvik_distance(15,Sedj);
    //for (int i = 0; i < 15; i++)std::cout << " " << Sedj[i];
    std::cout << std::endl;
    i = n;
    std::cout << std::endl;
    int a = 14;
    while (i < Sedj[a]*2)a--;
    int step = Sedj[a];
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << N[i];

    }
    std::cout << std::endl;
    while (step>1) 
    {
        algoritm(n,N,step);
        a--;
        step = Sedj[a];
        
    }

    algoritm(n, N,1);
    for (int i = 0; i < n; i++)
    {
        std::cout << " " << N[i];

    }
    std::cout << std::endl;
        
    
}

