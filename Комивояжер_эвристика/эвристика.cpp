#include <iostream>
struct Point 
{
    int i;
    int j;
};
void prt(int* cycle) 
{
    int s = 0;
    while (cycle[s] != -1) {
        std::cout << cycle[s] << ' '; s++;
    }
    std::cout << std::endl;
}
bool check_cycle(int pi, int pj, int* cycle)
{
    int i = 0, j = 1;
    for (i; cycle[i] != -1; i += 2) //исключения
    {
        j = i + 1;
        while (cycle[i] != -1 && cycle[j] != 1)
        {
            if (cycle[i + 1] == pi && cycle[j + 1] == pj && cycle[i] == cycle[j + 2])return 0;
            j += 2;
        }
    }
    i = 0; j = 1;
    while (cycle[i] != -1 && cycle[j] != 1)
    {
        if (cycle[i] == pj && cycle[j] == pi) return 0;
        i += 2; j += 2;
    }
    i = 1;
    for (i; cycle[i] != -1; i += 2)
    {
        j = i + 1;
        while (cycle[i] != -1 && cycle[j] != -1 )
        {
            if (cycle[i] == pi && cycle[j] == pj)
            {
                cycle[i] = cycle[j + 1];
                cycle[j] = -1; cycle[j + 1] = -1;
                bool a =0;
                while (cycle[j + 2] != -1)
                {
                    cycle[j] = cycle[j + 2];
                    cycle[j + 1] = cycle[j + 3];
                    j += 2;
                    a = 1;
                }
                if (a) { cycle[j] = -1; cycle[j - 1] = -1; }
                return 1;
            }
            else if (cycle[i - 1] == cycle[j + 1] && cycle[i] == pi && cycle[j] == pj)return 0;
            j += 2;
        }
    }
    i = 0; j = 1;
    while (cycle[i] != -1 && cycle[j] != -1)
    {
        if (cycle[i] == pj)
        {
            cycle[i] = pi;
            return 1;
        }
        else if (cycle[j] == pi) 
        {
            cycle[j] = pj;
            return 1;
        }
        else 
        {
            i += 2;
            j += 2;
        }
    }
    cycle[i] = pi; cycle[j] = pj;
    return 1;

}
void fill_matrix(int** mas, int n)
{
    srand(time(0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) mas[i][j] = 1 + rand() % 10;
    }
    for (int i = 0; i < n; i++)mas[i][i] = 0;
 
}
Point find_line_and_calmn(int** matrix, int n, int i, int* cycle) 
{
    Point p;
    int max = 0;
    for (int i = 0; i < n; i++) //находим номер строки
    {
        int m = 0;
        for (int j = 0; j < n; j++)  m += matrix[i][j];
        if (m > max)
        {
            max = m;
            p.i = i;
        }
    }
    int s = 0;
    while (matrix[p.i][s] == 0)s++;
    p.j = s;
    for (int i = 0; i < n-1; i++) 
    {
        if (matrix[p.i][i + 1] < matrix[p.i][p.j] && matrix[p.i][i + 1] != 0 )p.j = i + 1;
    }
    if (check_cycle(p.i,p.j, cycle)) 
    {
        std::cout << " i = " << p.i << " j = " << p.j << std::endl;
    }
    else 
    {
        
        matrix[p.i][p.j] = 0;
        p = find_line_and_calmn(matrix, n, i,cycle);
    }
    return p;
}
void delete_worst(int** matrix, int i,int j, int n) 
{
    for (int s = 0; s < n; s++) 
    {
        matrix[i][s] = 0;
        matrix[s][j] = 0;
    }
    matrix[i][j] = 0;
    matrix[j][i] = 0;
}
Point last_element(int *P,int n) 
{   
    int s = 0;
    int end = 0;
    for (int i = 0; i < n; i++)
    {
        s += i; end += i;
    }
    for (int i = 0; i < 2 * (n - 1); i += 2) 
    {
        s -= P[i]; end -= P[i + 1];
    }
    std::cout << " i = " << s << " j = " <<  end << std::endl;
    Point p;
    p.i = s; p.j = end;
    return p;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    int n;// количество городов
    int min = 0;//стоимаость минимальной перестановки
    std::cout << "Введите количество городов: ";
    std::cin >> n;
    int** matrix = (int**)malloc(sizeof(int*) * n);//динамический массив для весов
    int* cycle = new int[n*2];//массив для исключения циклов
    for (int i = 0; i < n; i++) matrix[i] = (int*)malloc(sizeof(int) * n);//выделение памяти под каждую строку
    for (int i = 0; i <  n*2; i++)cycle[i] = -1;//инициализация массива cycle где любой элемент равен -1
    fill_matrix(matrix, n);//функция заполнения массива случайными числами, исключая главную диагональ
    for (int i = 0; i < n; i++)//вывод матрицы
    {
        for (int j = 0; j < n; j++)std::cout << ' ' << matrix[i][j]<<"\t";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    int* P = new int[(n-1)*2];// массив для записи всех ребер, чтобы вычислить последнее ребро методом исключения
    for (int i = 0; i < n-1; i++) //основной цикл
    {
        Point p;
        p = find_line_and_calmn(matrix, n, i,cycle);// функция поиска нужного элемента
        min += matrix[p.i][p.j];
        P[i * 2] = p.i;     //четные элементы в P - это номер строки
        P[i * 2 + 1] = p.j; //нечетные элементы в P - это номер столбца
        delete_worst(matrix, p.i, p.j, n);//функция удаления элемента из матрмцы
    }
    Point p;
    p =last_element(P,n);//функция нахождения последнего ребра обхода
    min += matrix[p.i][p.j];
    std::cout << min;//вывод
    free(matrix);//освобождение динамической памяти
    delete P;
    delete cycle;
} 
