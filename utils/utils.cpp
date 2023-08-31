#include <iostream>
#include <string>
#include <limits>

#include "utils.h"

template<typename T> T get_value(const std::string& prompt)
{
    T input = 0;
    bool failure = true;
    do
    {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Input error! Please try again.\n";
            failure = true;
        }
        else
        {
            failure = false;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (failure);

    return input;
}

template<typename T> T get_value(const std::string& prompt, const T& min, const T& max)
{
    T value = 0;
    bool failure;
    do
    {
        failure = true;
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Input error! Please try again.\n";
        }
        else if (value < min || value > max)
        {
            std::cout << "Value is out of range: [" << min << ", " << max << "].";
            std::cout << " Please try again.\n";
        }
        else
        {
            failure = false;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (failure);

    return value;
}

template char get_value(const std::string&);
template int get_value(const std::string&);
template int get_value<int>(const std::string&, const int&, const int&);
template char get_value<char>(const std::string&, const char&, const char&);

