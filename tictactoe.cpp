#include <iostream>
#include <limits>
#include <array>

constexpr int NUM_OF_SLOTS   = 9;
constexpr int NUM_OF_PLAYERS = 2;

//! Only primitive data types
template<typename T> T get_value(const std::string& prompt);
//! Only primitive data types
template<typename T> T get_value(const std::string& prompt, const T& min, const T& max);

struct TicTacToe
{
    std::array<char, NUM_OF_PLAYERS> symbols = {'x', 'o'};
    std::array<char, NUM_OF_SLOTS> slots;
    bool player = false; //? false = Player 1, true = Player 2
    int  turn   = 1;
    char winner = 0;
    TicTacToe () 
    {
        slots.fill(' ');
    };
};

bool want_to_play_again();
void play_tictactoe();
void draw_board(const std::array<char, NUM_OF_SLOTS>& slots);
char find_winner(const std::array<char, NUM_OF_SLOTS>& slots);
void assign_symbols(std::array<char, NUM_OF_PLAYERS>& symbols);
bool insert_symbol(TicTacToe& tic, const int pos);
void display_results(const bool player, const int winner);

int main(int argc, char** argv)
{
    do
    {
        play_tictactoe();
    } while (want_to_play_again());

    return 0;
}

void play_tictactoe()
{
    TicTacToe ttt;

    assign_symbols(ttt.symbols);

    do
    {
        std::cout << "Player " << ttt.player + 1 << " turn.\n";
        draw_board(ttt.slots);

        int position = get_value<int>("Enter the desired position: ", -1, 8);

        if(position == -1)
            break;

        if(!insert_symbol(ttt, position))
            continue;

        if(ttt.turn >= 5) // At least 5 turns are needed for someone to win.
            ttt.winner = find_winner(ttt.slots);

        ttt.player = !ttt.player;
        ttt.turn += 1;
    } while (!ttt.winner && ttt.turn <= NUM_OF_SLOTS);

    display_results(!ttt.player, ttt.winner); //! undo last player toggle
    draw_board(ttt.slots);
}

void assign_symbols(std::array<char, NUM_OF_PLAYERS>& symbols)
{
    int selection = 0;
    selection = get_value<int>("Choose the symbol for Player 1 (o=1, x=2): ", 1, 2);

    if (selection == 1)
    {
        std::swap(symbols[0], symbols[1]);
    }
}

bool insert_symbol(TicTacToe& tic, const int pos)
{
    bool success = false;
    if (tic.slots[pos] != ' ')
    {
        std::cout << "Please try again with an empty slot.\n";
    }
    else
    {
        tic.slots[pos] = tic.symbols[tic.player];
        success = true;
    }
    return success;
}

void display_results(const bool player, const int winner)
{
    if (winner)
        std::cout << "Player " << player + 1 << " won!\n";
    else
        std::cout << "No luck guys, no winner this time.\n";
}

char find_winner(const std::array<char, NUM_OF_SLOTS>& slots)
{
    std::array<std::array<int, 3>, 8> winning_paths{{{0, 1, 2},
                                                     {3, 4, 5},
                                                     {6, 7, 8},
                                                     {0, 3, 6},
                                                     {1, 4, 7},
                                                     {2, 5, 8},
                                                     {0, 4, 8},
                                                     {2, 4, 6}}};

    char winner;
    bool is_winner_found = false;

    for(int i = 0; i < winning_paths.size(); i++)
    {
        winner = 0x7F;
        for (int j = 0; j < winning_paths[i].size(); j++)
        {
            winner &= slots[winning_paths[i][j]];
        }

        if (winner == 'x' || winner == 'o')
        {
            is_winner_found = true;
            break;
        }
    }
    return is_winner_found ? winner : 0;
}

void draw_board(const std::array<char, NUM_OF_SLOTS>& slots)
{
    std::array<char, NUM_OF_SLOTS> out_slots;
    for (int i = 0; i < slots.size(); i++)
    {
        if(slots[i] != ' ')
            out_slots[i] = slots[i];
        else
            out_slots[i] = '0' + i;
    }

    std::cout << "+---+---+---+\n";
    std::cout << "| " << out_slots[0] << ' ';
    std::cout << "| " << out_slots[1] << ' ';
    std::cout << "| " << out_slots[2] << " |\n";
    std::cout << "+---+---+---+\n";
    std::cout << "| " << out_slots[3] << ' ';
    std::cout << "| " << out_slots[4] << ' ';
    std::cout << "| " << out_slots[5] << " |\n";
    std::cout << "+---+---+---+\n";
    std::cout << "| " << out_slots[6] << ' ';
    std::cout << "| " << out_slots[7] << ' ';
    std::cout << "| " << out_slots[8] << " |\n";
    std::cout << "+---+---+---+\n";
}

bool want_to_play_again()
{
    char user_input = get_value<char>("Want to play again? (y=yes, n=no): ");

    return tolower(user_input) == 'y';
}

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
