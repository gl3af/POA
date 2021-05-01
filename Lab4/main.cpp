#include <iostream>
#include <fstream>

const char predicate = 'a';
const std::string d_in = "Lab4/input.txt";
const std::string d_out = "Lab4/output.txt";
std::string in, out, input_way = "", checker = "";
int size = 0;
bool is_working = true, opened;

size_t worker(std::string& input)
{
    for (size_t i = 0; i < input.size() - 1; ++i)
    {
        if(input[i] == predicate and input[i + 1] == predicate)
            return i;
    }
    return 0;
}

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
    if(file.is_open())
    {  
        opened = true;
        getline(file, checker);
        if(!valid_input(checker)) 
        {
            std::cout << "Неверный ввод n! Измените значение в файле и перезапустите программу!\n";
            is_working = false;
        }
        else size = std::stoi(checker);
        getline(file, read_to);
        if(read_to.size() != size) 
        {
            std::cout << "Строка имеет не n символов. Измените значение в файле и перезапустите программу!\n";
            is_working = false;
        }
    }
    else
    {   
        opened = false;
        std::cout << "Невозможно открыть файл по данному пути! Попробуйте заново!\n";
    }
    file.close();
}

void file_writer(std::string path, std::string& to_write)
{
    std::ofstream file(path);
    if(file.is_open()) 
    {
        opened = true;
        file << worker(to_write);
    }
    else 
    {
        std::cout << "Невозможно открыть файл по данному пути! Попробуйте заново!\n";
        opened = false;
    }
    file.close();
}

std::string input_menu()
{
    std::string key;
    std::cout << "Доступные команды: \n" <<
        "0 - Ввод данных из консоли\n"  <<
        "1 - Ввод данных из файла\n" <<
        "Ваш выбор: ";
    std::cin >> key;

    return key;
}

std::string output_menu()
{
    std::string key;
    std::cout << "Доступные команды: \n" <<
        "0 - Вывод результата в консоль\n"  <<
        "1 - Вывод результата в файл\n" <<
        "Ваш выбор: ";
    std::cin >> key;

    return key;
}

int main()
{
    std::string key, inner_key;
    std::string input = "";
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
                    std::cout << "Введите кол-во символов n: ";
                    std::cin >> checker;
                    if(!valid_input(checker)) std::cout << "Это не число! Повторите попытку!\n";
                    else
                    {
                        size = std::stoi(checker);
                        break;
                    }
                }
                while(true)
                {
                    std::cout << "Введите n символов, не разделя их: ";
                    std::cin >> input;
                    if(input.size() != size) std::cout << "Здесь не n символов. Повторите ввод!\n";
                    else break;
                }
            }
            else if(key == "1")
            {
                opened = false;
                input_way = "file";
                while(!opened)
                {
                    std::cout << "Укажите файл для ввода результатов работы программы[Введите d для выбора Lab4/input.txt]: ";
                    std::cin >> in;
                    if(in == "d") file_reader(d_in, input);
                    else file_reader(in, input);
                }
            }
            else std::cout << "Команда отсутствует! Попробуйте снова!\n";
        }
        else
        {
            key = output_menu();
            if(key == "0")
            {
                std::cout << "Результат: " + std::to_string(worker(input)) + "\n";
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
                opened = false;
                while(!opened)
                {
                    std::cout << "Укажите файл для вывода результатов работы программы[Введите d для выбора Lab4/output.txt]: ";
                    std::cin >> out;
                    if(out == "d") file_writer(d_out, input);
                    else file_writer(out, input);
                }
                if(out == "d") file_writer(d_out, input);
                else file_writer(out, input);
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