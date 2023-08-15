#include <iostream>
#include <string>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
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
std::string get_hidden_phrase();

int main(int argc, char **argv)
{
    do
    {
        play_hangman();
    } while (want_to_play_again());
    
}

void play_hangman()
{
    const std::string secret_phrase = get_secret_phrase();
    ClearScreen();
    
    std::string hidden_phrase = get_hidden_phrase(); // TODO: Implement get_hidden_phrase()
    // do
    // {
    //     draw_board()
    // } while (is_game_over());
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

std::string get_secret_phrase()
{
    std::string secret_phrase = "";
    std::cout << "Enter the secret phrase: ";
    std::getline(std::cin, secret_phrase, '\n');

    return secret_phrase;
}

void ClearScreen()
{
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = {0, 0};

  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition(hStdOut, homeCoords);
}

std::string get_hidden_phrase()
{
    std::string hidden_phrase = "";
    return hidden_phrase;
}
