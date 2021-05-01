// 141
#include <iostream>
#include <fstream>
#include <cmath>

const double pi = 3.14;
const double start = 0.5f;
const double stop = 5.0f;
const double step = 0.5f;

void menu()
{
    std::cout << "Доступные команды:\n" <<
    "0 - Вывод результата в файл\n" <<
    "1 - Вывод результата в консоль\n" <<
    "Ваш выбор: ";
}

void console_writer(double v)
{
    for (double h = start; h <= stop; h += step)
    {
        double r = sqrt(v / (pi * h));
        std::cout << "Радиус цилиндра с объемом 1 при высоте h = " << h << " равен " << r << "\n";
    }
}

void file_writer(double v)
{
    std::ofstream file("rez.txt");
    for (double h = start; h <= stop; h += step)
    {
        double r = sqrt(v / (pi * h));
        file << "Радиус цилиндра с объемом 1 при высоте h = " << h << " равен " << r << "\n";
    }
}

int main()
{
    double v = 1.0f;
    std::string key, inner_key;
    bool is_active = true;
    while(is_active)
    {
        menu();
        std::cin >> key;
        if(key == "0")
        {
            file_writer(v);
            while(true)
            {
                std::cout << "Хотите продолжить? 1 - Да, 0 - Нет\nВаш выбор: ";
                std::cin >> inner_key;
                if(inner_key == "1")
                {
                    std::cout << "Отлично!\n";
                    break;
                }
                else if(inner_key == "0")
                {
                    is_active = false;
                    break;
                }
                else std::cout << "Команда отсутствует! Попробуйте снова!\n";
            }
        }
        else if(key == "1")
        {
            console_writer(v);
            while(true)
            {
                std::cout << "Хотите продолжить? 1 - Да, 0 - Нет\nВаш выбор: ";
                std::cin >> inner_key;
                if(inner_key == "1")
                {
                    std::cout << "Отлично!\n";
                    break;
                }
                else if(inner_key == "0")
                {
                    is_active = false;
                    break;
                }
                else std::cout << "Команда отсутствует! Попробуйте снова!\n";
            }
        }
        else std::cout << "Команда отсутствует! Попробуйте снова!\n";
    }
    std::cout << "Хорошего дня!\n";
    return 0;
}