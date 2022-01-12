#include <iostream>
void invert(int* P, int i ,int n) 
{
    int a = 1;
    while (((n - (i + a)) / 2) > 0)
    {
        int s = P[n - a];
        P[n - a] = P[i + a];
        P[i + a] = s;
        a++;
    }
}
void fill_matrix( int** mas,int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n;j++)
        {
            mas[i][j] =1+ rand() % 100;
        }
    }
    for (int i = 0; i < n;i++) 
    {
        mas[i][i] = 0;
    }
}
int cost(int** matrix, int n, int* Pmin) 
{
    int ans = 0;
    for (int i = 0; i < n - 1; i++) 
    {
        ans += matrix[Pmin[i]][Pmin[i + 1]];
    }
    ans += matrix[Pmin[n-1]][Pmin[0]];
    return ans;
}
bool shift(int* P, int n)
{
    int i = n - 2, j = n - 1;
    while (P[i] > P[i + 1] && i > 0)i--;
    if (i == 0) return 0;
    while (P[i] > P[j] && j>i)j--;
    if (j <= i) return 0;
    int m = P[i];
    P[i] = P[j];
    P[j] = m;
    invert(P,i,n);
    return 1;

}
void answer(int* Pmin, int min, int n) 
{
    std::cout << "Результат: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << Pmin[i] << ' ';
    }
    std::cout << std::endl << "Минимальный вес равен: " << min<< std::endl;
}
void initialization(int** matrix,int* P, int* Pmin, int &min, int n, int k) 
{
    P[0] = k - 1;
    for (int i = 0; i < k - 1; i++)P[i + 1] = i;//P
    for (int i = k; i < n; i++)P[i] = i;//P
    for (int i = 0; i < n; i++)
    {
        Pmin[i] = P[i];//Pmin
    }
    min = cost(matrix, n, Pmin);//min
}
// invert - инверсия хвоста, fill_matrix - заполнение матрицы весами, cost - стоимость перестановки, shift - построение новой перестановки, answer - вывод ответа
int main()
{
    setlocale(LC_ALL,"Russian");
    int n=1;// количество городов, отсчет с 0
    int k;//номер города
    int min = 0;//стоимаость минимальной перестановки
    std::cout << "Введите количество городов: ";
    std::cin >> n;
    while (n != 0) {
        int** matrix = (int**)malloc(sizeof(int*) * n);//динамический массив для весов
        for (int i = 0; i < n; i++)
        {
            matrix[i] = (int*)malloc(sizeof(int) * n);
        }
        fill_matrix(matrix, n);//функция заполнения массива случайными числами, исключая главную диагональ
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout <<  matrix[i][j] <<"\t" ;
            }
            std::cout << std::endl;
        }
        std::cout << "Введите номер исходного города: ";
        std::cin >> k;
        int s = 1;
        int* P = new int[n];//динамический массив для перестановок
        int* Pmin = new int[n];//динамический массив для минимальной из найденных перестановок
        initialization(matrix, P, Pmin, min, n, k);//первоначальная инициализация таких переменных, как P,Pmin,min
        std::cout << "Перестановка " << s << " равна: ";
        for (int i = 0; i < n; i++) { std::cout << P[i] << ' '; }
        std::cout << "Стоимость: " << cost(matrix, n, P) << std::endl;
        s++;
        while (shift(P, n))//основной цикл
            {
                int t = cost(matrix, n, P);
                std::cout << "Перестановка " << s << " равна: ";
                for (int i = 0; i < n; i++) { std::cout << P[i] << ' '; }
                std::cout << "Стоимость: " << t << std::endl;
                s++;
                if (t < min)
                {
                    min = t;
                    for (int i = 0; i < n; i++)
                    {
                        Pmin[i] = P[i];
                    }
                }
            }
        answer(Pmin, min, n);//вывод ответа
        delete P;
        delete Pmin;
        free(matrix);
        std::cout << "Введите количество городов: ";
        std::cin >> n;
    }
}
