#include <iostream>

// The Game of Eight
// The game of 8 is played by 2 players. The game starts with the initial number
// 8 (from here on refered to as the initial number).
// The first player will choose a number from 1 to 3 (from here on referred to
// as the chosen number).
// If the player inputs something outside of the 1 to 3 range it should be an
// error and the player must choose again. The initial number is subtracted by
// the chosen number. Then the next player's turn happens. The next player 
// cannot choose the number that the last player chose.
// If the initial number goes to 0 on your turn, then you win.
// Otherwise if the number goes below 0, your opponent wins.
// The player should always see what choices are available to him when prompted 
// to enter his choice. After the game is over, the user should be prompted 
// whether they want to play again.

template<typename T>
T get_input(std::string prompt);

template<typename T>
T is_value_valid(T value, T min_value, T max_value);

void play_the_game_of_eight();
bool want_to_play_again();

int main (int argc, char** argv)
{
    do
    {
        play_the_game_of_eight();
    } while (want_to_play_again());
    
    std::cout << "\n";
    return 0;
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

template<typename T>
T is_value_valid(T value, T min_value, T max_value)
{
    return (value >= min_value) && (value <= max_value);
}

int get_number();
void display_result(int number, int player_turn);

void play_the_game_of_eight()
{
    int the_number = 8;
    int player = 0;

    do
    {
        player %= 2;
        player++;
        std::cout << "Player " << player << "'s turn\n";
        int chosen_number = get_number();
        the_number -= chosen_number;
        std::cout << "Player " << player << " chose number: ";
        std::cout << chosen_number << "\n";
    } while (the_number > 0);
    display_result(the_number, player);
}

void display_result(int number, int player)
{
    if (number == 0)
        std::cout << "Player " << player << " you won!\n";
    else
        std::cout << "Player " << player << " you lost :(\n";
}

bool want_to_play_again()
{
    char user_input = get_input<char>("Want to play again? (y=yes, n=no): ");

    return tolower(user_input) == 'y';
}

int get_number()
{
    static int previous_number = 0;
    int number = 0;

    do
    {
        number = get_input<int>("Enter a value (1-3) and different than the last one: ");
    } while (!is_value_valid<int>(number, 1, 3) || number == previous_number);

    previous_number = number;
    return number;
}