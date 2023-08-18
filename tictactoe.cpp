#include <iostream>
#include <vector>

bool want_to_play_again();

template<typename T> T get_value(const std::string prompt); //! Only for primitive data types
template<typename T> T get_value(const std::string prompt, const T min, const T max); //! Only for primitive data types
void play_tictactoe();
void draw_board(const std::vector<char>& slots);

int main(int argc, char** argv)
{
    do
    {
        play_tictactoe();
    } while (want_to_play_again());
}

void play_tictactoe()
{
    std::vector<char> slots(9, ' ');
    bool player = false;
    std::vector<char> symbols;

    // TODO: Migrate to get_symbol()
    {
        int user_selection = 0;
        do
        {
            user_selection = get_value<int>("Choose the symbol for Player 1 (o=1 or x=2): ", 0, 2);
        } while (!(user_selection == 1 || user_selection == 2));

        if (user_selection == 1)
        {
            symbols.push_back('o');
            symbols.push_back('x');
        }
        else
        {
            symbols.push_back('x');
            symbols.push_back('o');
        }
    }
    

    while (true)
    {
        std::cout << "Player " << player + 1 << " turn.\n";
        draw_board(slots);
        int position = get_value<int>("Enter the desired position: ", 0, 8);

        if (slots[position] != ' ')
        {
            std::cout << "Please try again with an empty slot.\n";
            continue;
        }
        else
        {
            slots[position] = player ? symbols[1] : symbols[0];
        }
        player = !player;
    }
}

void draw_board(const std::vector<char>& slots)
{
    std::vector<char> out_slots;
    for (int i = 0; i < slots.size(); i++)
    {
        if(slots[i] != ' ')
            out_slots.push_back(slots[i]);
        else
            out_slots.push_back(i + '0');
    }

    std::string board = std::string("+---+---+---+\n") +
                        "| " + out_slots[0] + " | " + out_slots[1] + " | " + out_slots[2] + " |\n"
                        "+---+---+---+\n"
                        "| " + out_slots[3] + " | " + out_slots[4] + " | " + out_slots[5] + " |\n"
                        "+---+---+---+\n"
                        "| " + out_slots[6] + " | " + out_slots[7] + " | " + out_slots[8] + " |\n"
                        "+---+---+---+\n";

    std::cout << board;
}

bool want_to_play_again()
{
    char user_input = get_value<char>("Want to play again? (y=yes, n=no): ");

    return tolower(user_input) == 'y';
}

template<typename T> T get_value(const std::string prompt)
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

template<typename T> T get_value(const std::string prompt, const T min, const T max) //! Only for primitive data types
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

    } while (failure);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return value;
}
