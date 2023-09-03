#include <iostream>
#include <string>
#include <limits>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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

void clear_screen()
{
    HANDLE hStdOut;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Fetch existing console mode so we correctly add a flag and not turn off others
    DWORD mode = 0;
    if (!GetConsoleMode(hStdOut, &mode))
    {
        return;
    }

    // Hold original mode to restore on exit to be cooperative with other command-line apps.
    const DWORD originalMode = mode;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    // Try to set the mode.
    if (!SetConsoleMode(hStdOut, mode))
    {
        return;
    }

    // Write the sequence for clearing the display.
    DWORD written = 0;
    PCWSTR sequence = L"\x1b[2J";
    if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
    {
        // If we fail, try to restore the mode on the way out.
        SetConsoleMode(hStdOut, originalMode);
        return;
    }

    // To also clear the scroll back, emit L"\x1b[3J" as well.
    // 2J only clears the visible window and 3J only clears the scroll back.

    
    // Put the cursor at its home coordinates.
    COORD coordScreen = {0, 0};    // home for the cursor
    SetConsoleCursorPosition(hStdOut, coordScreen);

    // Restore the mode on the way out to be nice to other command-line applications.
    SetConsoleMode(hStdOut, originalMode);
}

