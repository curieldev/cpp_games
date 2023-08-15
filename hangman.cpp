#include <iostream>

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

template<typename T>
T get_input(std::string prompt);

bool want_to_play_again();
void play_hangman();

int main(int argc, char **argv)
{
    do
    {
        play_hangman();
    } while (want_to_play_again());
    
}

void play_hangman()
{
    // secret_phrase = get_secret_phrase();
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

template<typename T>
T get_input(std::string prompt)
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error! Please try again.\n";
            failure = true;
        }
        else
        {
            failure = false;
        }

    } while (failure);
    return input;
}
