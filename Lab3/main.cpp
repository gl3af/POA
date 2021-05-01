// 371
#include <iostream>
#include <fstream>
#include <vector>
#include <random>

typedef std::vector<std::vector<double>> Matrix;

const std::string input_path = "Lab3/input.txt";
const std::string output_path = "Lab3/output.txt";
std::string input_way = "";
std::string checker = "";

void print_matrix(Matrix& m)
{
    for (auto& row: m)
    {
        for (auto& elem: row)
            std::cout << elem << " ";
        std::cout << "\n";
    }
}

void resizer(Matrix& a, Matrix& b, Matrix& c, int n)
{
    if (n == 0)
    {
        a.resize(0, std::vector<double>());
        b.resize(0, std::vector<double>());
        c.resize(0, std::vector<double>());
    }
    else
    {
        a.resize(n, std::vector<double>(n));
        b.resize(n, std::vector<double>(n));
        c.resize(n, std::vector<double>(n));
    }
}

bool valid_input(std::string& input)
{
    size_t amount_of_digits = 0;
    for(auto& c : input)
        if (isdigit(c))
            ++amount_of_digits;

    return amount_of_digits == input.size() and input[0] != '0';
}

void generate_matrix(Matrix& matrix)
{
    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_real_distribution<> dis(-100, 100);
    for (size_t i = 0; i < matrix.size(); i++)
        for (size_t j = 0; j < matrix.size(); j++)
            matrix[i][j] = dis(e);
}

void file_reader(std::string path)
{
    std::ifstream file(path);
    getline(file, checker);
    file.close();
}

void file_writer(std::string path, Matrix& a ,Matrix& b, Matrix& c)
{
    std::ofstream file(path);
    file << "Матрица A: \n";
    for (auto& row: a)
    {
        for (auto& elem: row)
            file << elem << " ";
        file << "\n";
    }
    file << "Матрица В: \n";
    for (auto& row: b)
    {
        for (auto& elem: row)
            file << elem << " ";
        file << "\n";
    }
    file << "Матрица C: \n";
    for (auto& row: c)
    {
        for (auto& elem: row)
            file << elem << " ";
        file << "\n";
    }
    file.close();
}

std::string input_menu()
{
    std::string key;
    std::cout << "Доступные команды: \n" <<
        "0 - Ввод данных из консоли\n"  <<
        "1 - Ввод данных из файла 'input.txt'\n" <<
        "Ваш выбор: ";
    std::cin >> key;

    return key;
}

std::string output_menu()
{
    std::string key;
    std::cout << "Доступные команды: \n" <<
        "0 - Вывод результата в консоль\n"  <<
        "1 - Вывод результата в файл 'output.txt'\n" <<
        "Ваш выбор: ";
    std::cin >> key;

    return key;
}

void worker(Matrix& a, Matrix& b, Matrix& c)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < a.size(); j++)
        {
            // B
            if(j >= i)
            {
                b[i][j] = a[i][j];
                c[i][j] = -a[i][j];
            }
            else
            {
                b[i][j] = a[j][i];
                c[i][j] = a[i][j];
            }
        }
    }
}

int main()
{
    int n{};
    Matrix a, b, c;
    bool is_working = true;
    std::string key, inner_key;
    while(is_working)
    {
        if(input_way == "")
        {
            key = input_menu();
            if(key == "0")
            {
                input_way = "console";
                while(true)
                {
                    std::cout << "Введите размерность n матрицы (Она будет сгенерированна): ";
                    std::cin >> checker;
                    if(!valid_input(checker))
                        std::cout << "Вы ввели не число! Попробуйте снова!";
                    else
                    {
                        n = std::stoi(checker);
                        break;
                    }
                }
                resizer(a, b, c, n);
                std::cout << "Матрица А: \n";
                generate_matrix(a);
                print_matrix(a);
            }
            else if(key == "1")
            {
                file_reader(input_path);
                input_way = "file";
                if(!valid_input(checker))
                {
                    std::cout << "В файле не число, обновите значение в файле и перезапустите программу!\n";
                    is_working = false;
                }
                else
                {
                    n = std::stoi(checker);
                    resizer(a, b, c, n);
                    std::cout << "Матрица А: \n";
                    generate_matrix(a);
                    print_matrix(a);
                }
            }
            else std::cout << "Команда отсутствует! Попробуйте снова!\n";
        }
        else
        {
            worker(a, b, c);
            key = output_menu();
            if(key == "0")
            {
                std::cout << "Матрица B: \n";
                print_matrix(b);
                std::cout << "Матрица C: \n";
                print_matrix(c);
                if(input_way == "file")
                    is_working = false;
                else
                {
                    std::cout << "Хотите продолжить? 1 - Да, 0 - Нет\nВаш выбор: ";
                    std::cin >> inner_key;
                    if(inner_key == "1")
                    {
                        input_way = "";
                        resizer(a, b, c, 0);
                        std::cout << "Отлично!\n";
                    }
                    else if(inner_key == "0")
                        is_working = false;
                    else std::cout << "Команда отсутствует! Попробуйте снова!\n";
                }  
            }
            else if(key == "1")
            {
                file_writer(output_path, a, b, c);
                if(input_way == "file")
                    is_working = false;
                else
                {
                    std::cout << "Хотите продолжить? 1 - Да, 0 - Нет\nВаш выбор: ";
                    std::cin >> inner_key;
                    if(inner_key == "1")
                    {
                        input_way = "";
                        resizer(a, b, c, 0);
                        std::cout << "Отлично!\n";
                    }
                    else if(inner_key == "0")
                        is_working = false;
                    else std::cout << "Команда отсутствует! Попробуйте снова!\n";
                }
            }
            else std::cout << "Команда отсутствует! Попробуйте снова!\n";
        }
    }
    std::cout << "Хорошего дня!\n";
    return 0;
}