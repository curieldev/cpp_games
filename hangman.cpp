#include <iostream>
#include <string>
#include <algorithm>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

// Create the program Hangman. Prompt the player to enter a phrase.
// That phrase will be hidden by a series of dashes (excluding spaces).
// The player can then guess letters. If they guess correctly all the letters 
// that match will be revealed.
// If they guess incorrectly, then 1 more body part will be added to the gallows.
// If they lose the gallows should look like this:

//  +---+
//  |   |
//  |   o
//  |  /|\
//  |  / \
// -+-

// If the player loses, the phrase should be revealed.
// After the game is over the player should be prompted if they want to play again.

template<typename T> T get_input(std::string prompt);
bool want_to_play_again();
void play_hangman();
std::string get_secret_phrase();
void ClearScreen();
std::string make_hidden_phrase(const std::string& phrase);
bool is_game_over(const struct Hangman& man);
void insert_letter(Hangman& man, const char& letter);
void display_result(Hangman& man);
void draw_gallows(int attempts_left);

struct Hangman
{
    const std::string secret_phrase = "";
    std::string hidden_phrase = "";
    int attempts_left = 6;

    Hangman(std::string str) : secret_phrase(str){
        hidden_phrase = make_hidden_phrase(str);
    };
};

int main(int argc, char **argv)
{
    do
    {
        play_hangman();
    } while (want_to_play_again());
}

void play_hangman()
{
    struct Hangman hangman(get_secret_phrase());
    ClearScreen();
    
    do // TODO: Read guess and update hidden phrase
    {
        draw_gallows(hangman.attempts_left);
        std::cout << hangman.hidden_phrase << "\n";
        std::cout << "You have " << hangman.attempts_left << " attempts left. ";
        char guess = get_input<char>("Enter your guess: ");
        if (hangman.secret_phrase.find(guess) != std::string::npos)
            insert_letter(hangman, guess);
        else
            hangman.attempts_left--;

    //     draw_board()
    } while (!is_game_over(hangman));

    draw_gallows(hangman.attempts_left);
    std::cout << "The secret phrase is " << hangman.secret_phrase << ".\n";
    display_result(hangman);
}

void draw_gallows(int attempts_left)
{
    static std::string gallows = "";

    if (attempts_left == 6)
    gallows = " +---+ \n"
              " |   | \n"
              " |     \n"
              " |     \n"
              " |     \n"
              "-+-\n";
    if (attempts_left == 5)
        gallows[21] = 'o';
    else if (attempts_left == 4)
        gallows[29] = '|';
    else if (attempts_left == 3)
        gallows[28] = '/';
    else if (attempts_left == 2)
        gallows[30] = '\\';
    else if (attempts_left == 1)
        gallows[38] = '\\';
    else if (attempts_left == 0)
        gallows[36] = '/';
    
    std::cout << gallows;
}

void display_result(Hangman& man)
{
    std::string result = "";

    if (man.secret_phrase == man.hidden_phrase)
        result = "You won!";
    else
        result = "You lost, try again if you have the guts.";
    
    std::cout << result << '\n';
}

void insert_letter(Hangman& man, const char& letter)
{
    for(int i = 0; i < man.secret_phrase.size(); i++)
    {
        if (man.secret_phrase[i] == letter)
            man.hidden_phrase[i] = letter;
    }
}

bool is_game_over(const struct Hangman& man)
{
    return man.secret_phrase == man.hidden_phrase || man.attempts_left <= 0;
}

bool want_to_play_again()
{
    char user_input = get_input<char>("Want to play again? (y=yes, n=no): ");

    return tolower(user_input) == 'y';
}

template<typename T> T get_input(std::string prompt)
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

    } while (failure);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return input;
}

bool is_alpha_or_blank(char c)
{
    return isalpha(c) || isblank(c);
}

std::string get_secret_phrase()
{
    std::string phrase = "";

    bool failure = true;
    do
    {
        std::cout << "Enter the secret phrase: ";
        std::getline(std::cin, phrase, '\n');

        std::transform(phrase.begin(), phrase.end(), phrase.begin(), tolower);

        bool is_phrase_alpha = std::find_if_not(phrase.begin(), phrase.end(),
                                                is_alpha_or_blank) == phrase.end();

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Input error! Please try again.\n";
            failure = true;
        }
        else if (phrase.length() == 0)
        {
            std::cout << "There's no phrase with 0 letters. C'mon try again.\n";
            failure = true;
        }
        else if (!is_phrase_alpha)
        {
            std::cout << "Only letters and spaces allowed. Try again.\n";
            failure = true;
        }
        else
        {
            failure = false;
        }
    } while (failure);
    return phrase;
}

void ClearScreen()
{
    HANDLE                     hStdOut;

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

std::string make_hidden_phrase(const std::string& phrase)
{
    std::string hidden_phrase = "";
    int i = 0;
    while (phrase[i] != '\0')
    {
        if (isalpha(phrase[i]))
            hidden_phrase += '_';
        else
            hidden_phrase += ' ';
        i++;
    }
    
    return hidden_phrase;
}
