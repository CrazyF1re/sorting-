#include <iostream>
int index_of_max(int s,int i,int*N) 
{
    if (N[i] > N[s] && N[i] > N[s - 1])return i;
    else if (N[s] > N[s - 1])return s;
    return s - 1;
}
void fill_massiv(int n, int* N) 
{
    srand(time(0));
    for (int i = 0; i < n; i++) 
    {
        N[i] = rand() % 100;
    }
}
void sort_tree(int n, int* N)
{
    //найти три последних элементов
    int s = n-1;
    int i = n / 2 - 1;
    if (n % 2 == 0) //исключение когда есть только два элемента из трех для поиска максимального из них
    {
        if (N[n - 1] > N[i]) 
        {
            int x = N[n - 1];
            N[n - 1] = N[i];
            N[i] = x;
        }
        s--;
        i--;
    }
    while (i >= 0) //основной цикл для сортировки дерева
    {
        int id = index_of_max(s,i,N);//находим индекс максимального элемента из трех возможных
        if (id == i) //если родитель совпадает с максимальным элементом, то берем следующего родителя и его потомков для сравнения
        {
            i--; s -= 2;
        }
        else //иначе максимальный элемент ставим как родителя и соблюдаем правило, родитель> потомка для второго элемента, который был родителем
        {
            int head = i;
            int s1 = s;
            bool f = 1;
            while ((head < n / 2) && f) 
            {
                id = index_of_max(s1, head, N);
                if (head == id)f = 0;
                else
                {
                    int x = N[head];
                    N[head] = N[id];
                    N[id] = x;
                    head = id;
                    s1 = head * 2 + 2;
                    if (s1 >= n)f = 0;
                }
            }
            /*if ((head * 2 + 2) == n)//исключение когда вместо трех элементов есть только два для сравнения, но работает и без него????
            {
                id = n - 1;
                if (N[id] > N[head])
                {
                    int x = N[head];
                    N[head] = N[id];
                    N[id] = x;
                }
                f = 0;
                std::cout << "WOW ";
            }*/
            s -= 2;
            i--;
        } 
    }
}
void algoritm(int n, int* N) //основной алгоритм
{
    for (int i = n; i >1; i--) 
    {
        sort_tree(i, N);
        int x = N[0];
        N[0] = N[i - 1];
        N[i - 1] = x;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n;
    int* N;
    std::cout << "Введите количество элементов: ";
    std::cin >> n;
    N = new int[n];
    fill_massiv(n, N);
    for (int i = 0; i < n; i++)std::cout << " " << N[i];
    std::cout << std::endl;
    algoritm(n,N);
    for (int i = 0; i < n; i++)std::cout << " " << N[i];
    std::cout << std::endl;
    delete[]N;
}
