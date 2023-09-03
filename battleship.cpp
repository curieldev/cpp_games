#include <iostream>
#include <string>
#include <algorithm>

#include "utils.h"

// Battleship

// The game is played on four 10x10 grids by 2 players, with each player having
// 2 grids each.
// The rows of the grid go from A to J in the rows and 1 to 10 in the columns.
// Each player will arrange their ships on their respective ship board before 
// the main game starts. Each ship occupies a number of consecutive squares on
// the grid, arranged either horizontally or vertically. The number of squares
// for each ship is determined by the type of the ship. The ships cannot overlap.

// The ships are as follows:

// Ship Type          Size
// -----------------+------
// Aircraft carrier |  5
// Battleship       |  4
// Cruiser          |  3
// Destroyer        |  3
// Submarine        |  2

// After the ship have been positioned, the game proceeds in a series of rounds.
// In each round, each player takes a turn to announce a target square in the
// opponent's grid which is to be shot at. The opponent announces whether or not
// the square is occupied by a ship, and if it is a miss, the player marks their
// guess board as a miss; if it is a hit they mark it as a hit. This is to build
// up a picture of the opponent's fleet. If the guess was a hit, the attacked
// player will mark their ship as hit in the guessed location. That will end the
// turn.

// When all of the squares of a ship have been hit, the ship will sunk and there
// is output about what ship was sunk. If all the player's ships have been sunk,
// the game is over and their opponent wins.

// TODO: Set ships positions
constexpr int grid_size = 10; // 10x10 grid
constexpr char const * const grid_space = "   ";

enum struct Ship
{
    AircraftCarrier,
    Battleship,
    Cruiser,
    Destroyer,
    Submarine,
    Unknown,
    None
};

struct Square
{
    bool is_hit = false;
    char show = 'x';
    Ship ship;
};

struct Player
{
    std::string name = "";
    Square location[grid_size][grid_size]; // [y][x] or [rows][columns]
    Square enemy_location[grid_size][grid_size]; // [y][x] or [rows][columns]
};

void play_battleship();
bool want_to_play_again();
std::string get_name(const std::string& prompt);
void print_board(const Player& p);

int main (int argc, char *argv[])
{
    do
    {
        play_battleship();
    } while (want_to_play_again());
    return 0;
}

void play_battleship()
{
    
    Player player_1;
    Player player_2;

    std::cout << "Player 1\n";
    player_1.name = get_name("My name is: ");
    std::cout << "Player 2\n";
    player_2.name = get_name("My name is: ");

    print_board(player_1);
}

bool want_to_play_again()
{
    char c = get_value<char>("Want to play again? (y=yes, n=no): ");
    return c == 'y';
}

bool is_alpha_or_blank(char c)
{
    return isalpha(c) || isblank(c);
}

std::string get_name(const std::string& prompt)
{
    std::string name = "";

    bool failure = true;
    do
    {
        std::cout << prompt;
        std::getline(std::cin, name, '\n');

        bool is_name_alpha = std::find_if_not(name.begin(), name.end(),
                                                is_alpha_or_blank) == name.end();

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cout << "Input error! Please try again.\n";
            failure = true;
        }
        else if (name.length() == 0)
        {
            std::cout << "Null is not a name. C'mon try again.\n";
            failure = true;
        }
        else if (!is_name_alpha)
        {
            std::cout << "Only letters and spaces allowed. Try again.\n";
            failure = true;
        }
        else
        {
            failure = false;
        }
    } while (failure);
    return name;
}

void print_column_headers()
{
    for (int x = 0; x < grid_size; x++)
    {
        std::cout << ' ' << ' ' << ' ' << x;
    }
    std::cout << grid_space;
}

void print_border()
{
    std::cout << ' ';
    for (int x = 0; x < grid_size; x++)
    {
        std::cout << "+---";
    }
    std::cout << '+' << grid_space;
}

void print_row(const Square row[grid_size], int number)
{
    std::cout << static_cast<char>(number + 'A') << '|';
    for (int x = 0; x < grid_size; x++)
    {
         std::cout << ' ' << row[x].show << " |";
    }
    std::cout << grid_space;
}

void print_board(const Player& p)
{
    print_column_headers();
    print_column_headers();
    std::cout << '\n';

    print_border();
    print_border();
    std::cout << '\n';

    for (int y = 0; y < grid_size; y++)
    {
        print_row(p.location[y], y);
        print_row(p.enemy_location[y], y);
        std::cout << '\n';

        print_border();
        print_border();
        std::cout << '\n';
    }
}

