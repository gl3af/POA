// 207
#include <iostream>
#include <fstream>

const char first_out = '0';
const char second_out = '5';
const std::string input_path = "Lab2/input.txt";
const std::string output_path = "Lab2/output.txt";
std::string input_way = "";

bool valid_input(std::string& input)
{
    size_t amount_of_digits = 0;
    for(auto& c : input)
        if (isdigit(c))
            ++amount_of_digits;

    return amount_of_digits == input.size() and input[0] != '0';
}

void file_reader(std::string path, std::string& read_to)
{
    std::ifstream file(path);
    getline(file, read_to);
    file.close();
}

void file_writer(std::string path, std::string& to_write)
{
    std::ofstream file(path);
    file << to_write + "\n";
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

std::string symbol_remover(std::string& input)
{
    std::string out;
    for (size_t i = 0; i < input.size(); i++)
    {
        if ((input[i] != first_out) and (input[i] != second_out))
            out += input[i];
    }
    
    return out;
}

int main()
{
    bool is_working = true;
    std::string key, inner_key, rez;
    std::string c_input = "";
    std::string f_input = "";
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
                    std::cout << "Введите число для редактирования: ";
                    std::cin >> c_input;
                    if(valid_input(c_input)) break;
                    else std::cout << "Это не число! Попробуйте снова!\n";
                }
                rez = symbol_remover(c_input);
            }
            else if(key == "1")
            {
                input_way = "file";
                file_reader(input_path, f_input);
                if(!valid_input(f_input)) 
                {
                    std::cout << "В файле не число! Измените содержимое файла и перезапустите программу!\n";
                    is_working = false;
                }
                rez = symbol_remover(f_input);
            }
            else std::cout << "Команда отсутствует! Попробуйте снова!\n";
        }
        else
        {
            key = output_menu();
            if(key == "0")
            {
                std::cout << "Результат: " + rez + "\n";
                if(input_way == "file")
                    is_working = false;
                else
                {
                    std::cout << "Хотите продолжить? 1 - Да, 0 - Нет\nВаш выбор: ";
                    std::cin >> inner_key;
                    if(inner_key == "1")
                    {
                        input_way = "";
                        std::cout << "Отлично!\n";
                    }
                    else if(inner_key == "0")
                        is_working = false;
                    else std::cout << "Команда отсутствует! Попробуйте снова!\n";
                }
                
            }
            else if(key == "1")
            {
                file_writer(output_path, rez);
                if(input_way == "file")
                    is_working = false;
                else
                {
                    std::cout << "Хотите продолжить? 1 - Да, 0 - Нет\nВаш выбор: ";
                    std::cin >> inner_key;
                    if(inner_key == "1")
                    {
                        input_way = "";
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