#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



template <typename T>
std::string to_string(const T& x)
{
	std::stringstream buf;
	buf << x;
	return buf.str();
}

std::vector<int> min(std::vector<int> mas)
{
	std::vector<int> ans = {32767, 0};
	for (int i = 0; i < mas.size(); i++) 
	{
		if (mas[i] < ans[0] && mas[i] != -1) 
		{
			ans[0] = mas[i]; ans[1] = i;
		}
	}
	if (ans[0] == 32767) 
	{
		ans[0] = -1; ans[1] = -1;
		return ans;
	};
	return ans;
}

bool eof(std::ifstream* read, int N ) 
{
	int count = 0;
	for (int i = 0; i < N; i++) 
	{
		if (read[i].eof())count++;
	}
	if (count == N)return 0;
	else return 1;
}

std::string* create_names_of_files(std::string s, int N) 
{
	std::string* files = new std::string[N];
	for (int i = 0; i < N; i++)
	{
		files[i] = s + to_string(i) + ".txt";
	}
	return files;
}

void generate_main_file(std::string s, int N)
{
	srand(time(0));
	std::ofstream fout;
	fout.open(s);
	for (int i = 0; i < N; i++)
	{
		int x = rand() % 100;
		fout << x << ' ';
	}
	fout.close();
}

void create_n_files(std::string* mas, int N) 
{
	std::ofstream file;
	for (int i = 0; i < N; i++) 
	{
		file.open(mas[i]);
		file.close();
	}
}

void split(std::string* files, int N) //сплитим файл A в файлы f1-fn
{
	std::ifstream fin;
	fin.open("fileA.txt", std::ios::in);
	int count = 0;
	int temp;
	fin >> temp;
	while (!fin.eof())
	{
		std::ofstream  fout(files[count], std::ios::app);
		fout << temp << ' ';
		fin >> temp;
		count++;
		if (count == N)count = 0;
		fout.close();
	}
	fin.close();
}

void merge(std::string* files_f, std::string* files_g, int N) 
{
	std::vector<int> current_numbers;//массив для текущих элементов
	std::ifstream* files_read = new std::ifstream[N];// массив потоков файлов на чтение
	std::ofstream* files_write = new std::ofstream[N];//массив потоков файлов на запись

	for (int i = 0; i < N; i++)
	{

		files_read[i].open(files_f[i]);//открываем файлы на чтение и запись
		files_write[i].open(files_g[i]);
		int temp;
		files_read[i] >> temp;
		if (files_read[i].eof()) current_numbers.push_back(-1);//заполняем массив текущих элементов из файлов на чтение
		else
		{
			current_numbers.push_back(temp);
		}
	}
	int* temp = new int[N];//дополнительный массив 
	for (int i = 0; i < N; i++)temp[i] = -1;
	int count_of_write_file = 0;//номер файла в который нужно записывать текущие элементы
	while (eof(files_read, N)) //цикл прочтения всех файлов
	{
		std::vector<int> next_number = min(current_numbers);
		while (next_number[0] != -1)
		{
			files_write[count_of_write_file] << next_number[0] << ' ';
			int number = -1;
			if (!files_read[next_number[1]].eof())
			{
				files_read[next_number[1]] >> number;
				if (next_number[0] <= number)current_numbers[next_number[1]] = number;
				else {
					temp[next_number[1]] = number; current_numbers[next_number[1]] = -1;
				}
			}
			next_number = min(current_numbers);

		}
		for (int i = 0; i < N; i++)current_numbers[i] = temp[i];
		count_of_write_file++;
		if (count_of_write_file == N)count_of_write_file = 0;
	}

	for (int i = 0; i < N; i++) //закрытие всех файлов на чтение и запись
	{
		files_read[i].close();
		files_write[i].close();
	}
	for (int i = 2; i < N; i++) 
	{
		std::ofstream temp(files_f[i], std::ios::trunc);
		temp.close();
	}
}

void cycle(std::string* files_f, std::string* files_g, int N)
{
	if (N < 1)return;
	std::ifstream  temp1(files_f[1],std::ios::in);//
	std::ifstream  temp2(files_g[1], std::ios::in);//два потока для проверки на пустоту
	bool flag = 1;//флаг для слияния в разных направлениях
	while (!temp1.eof() && !temp2.eof() ) //основной цикл
	{
		temp1.close();//закрываем файлы открытые на чтение
		temp2.close();
		if (flag) //если флаг то сливаем из f в h
		{
			flag = !flag;
			merge(files_f, files_g, N);
		}
		else//иначе сливаем из g в f
		{
			flag = !flag;
			merge(files_g, files_f, N);
		}
		temp1.open(files_f[1], std::ios::in);
		temp2.open(files_g[1], std::ios::in);
		std::string temp;
		temp1 >> temp;
		if (temp == (""))return;
		temp2 >> temp;
		if (temp == (""))return;


	}
}

void destroy(std::string* files, int N) 
{
	for (int i = 1; i < N; i++) 
	{
		const char* temp = files[i].c_str();
		remove(temp);
	}
}

int main()
{
	int N;
	int n;
	std::string main = ("fileA.txt");//файл с исходными неупорядоченными числами
	std::cout << "Enter number of files: ";
	std::cin >> N;
	std::cout << "Enter amount of numbers: ";
	std::cin >> n;
	std::string* files_f = new std::string[N];//выделяем память под имена файлов f
	std::string* files_g = new std::string[N];//выделяем память под имена файлов g
	files_f = create_names_of_files("f", N);//определяем массив имен файлов f1-fn
	files_g =create_names_of_files("g", N);//определяем массив имен файлов g1-gn
	generate_main_file(main, n);//изначальная генерация случайных чисел в файле А
	create_n_files(files_f, N);//создаем n файлов f
	create_n_files(files_g, N);//создаем n файлов g
	split(files_f, N);//разделяем файл А на файлы f1-fn
	cycle(files_f, files_g, N);
	destroy(files_f,N);
	destroy(files_g, N);

}