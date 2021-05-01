#include <iostream>
#include <cmath>

int main()
{
    double x1, x2;
    int roots = 0;
    double a,b,c;
    std::cout << "Введите a: ";
    std::cin >> a;
    std::cout << "Введите b: ";
    std::cin >> b;
    std::cout << "Введите c: ";
    std::cin >> c;
    // x + a >= 0
    double root_of_D = sqrt(pow(a - c, 2) + 4 * (a * c - b));
    if (root_of_D == 0)
    {
        x1 = (c - a) / 2.0;
        if (x1 >= -1 * a && x1 != c)
        {
            ++roots;
            std::cout << "Корень уравнения: " << x1 << "\n";
        }
    }
    else if(root_of_D > 0)
    {
        x1 = (c - a + root_of_D) / 2.0;
        x2 = (c - a - root_of_D) / 2.0;
        if (x1 >= -1 * a && x1 != c)
        {
            ++roots;
            std::cout << "Корень уравнения: " << x1 << "\n";
        }
        if (x2 >= -1 * a && x2 != c)
        {
            ++roots;
            std::cout << "Корень уравнения: " << x2 << "\n";
        }
    }
    // x + a < 0
    root_of_D = sqrt(pow(a - c, 2) + 4 * (a * c + b));
    if (root_of_D == 0)
    {
        x1 = (c - a) / 2.0;
        if (x1 < -1 * a && x1 != c)
        {
            ++roots;
            std::cout << "Корень уравнения: " << x1 << "\n";
        }
    }
    else if(root_of_D > 0)
    {
        x1 = (c - a + root_of_D) / 2.0;
        x2 = (c - a - root_of_D) / 2.0;
        if (x1 < -1 * a && x1 != c)
        {
            ++roots;
            std::cout << "Корень уравнения: " << x1 << "\n";
        }
        if (x2 < -1 * a && x2 != c)
        {
            ++roots;
            std::cout << "Корень уравнения: " << x2 << "\n";
        }
    }
    if(roots == 0)
    {
        std::cout << "Корней нет :(\n";
    }
    return 0;
}