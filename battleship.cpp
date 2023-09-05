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
constexpr int cells_per_side = 10; // 10x10 grid
constexpr char const * const grid_padding = "   ";
constexpr int fleet_size = 5;
constexpr int grid_length = 42; // Total characters


enum struct ShipModel
{
    AircraftCarrier,
    Battleship,
    Cruiser,
    Destroyer,
    Submarine,
    Unknown,
    None
};

struct Ship
{
    std::string name;
    ShipModel model;
    int size;
    int health;
    char symbol;
};

struct ShipPose
{
    int x;
    int y;
    int orientation;
};

struct Cell
{
    bool is_hit = false;
    char show = ' ';
    ShipModel model;
};

struct Player
{
    std::string name = "";
    Ship ship[fleet_size];
    // [y][x] or [rows][columns]
    Cell location[cells_per_side][cells_per_side];
    // [y][x] or [rows][columns]
    Cell enemy_location[cells_per_side][cells_per_side];

    Player ()
    {
        ship[0].model  = ShipModel::AircraftCarrier;
        ship[0].name   = "Aircraft Carrier";
        ship[0].symbol = 'A';
        ship[0].size   = 5;
        ship[0].health = 5;

        ship[1].model  = ShipModel::Battleship;
        ship[1].name   = "Battleship";
        ship[1].symbol = 'B';
        ship[1].size   = 4;
        ship[1].health = 4;

        ship[2].model  = ShipModel::Cruiser;
        ship[2].symbol = 'C';
        ship[2].name   = "Cruiser";
        ship[2].size   = 3;
        ship[2].health = 3;

        ship[3].model  = ShipModel::Destroyer;
        ship[3].name   = "Destroyer";
        ship[3].symbol = 'D';
        ship[3].size   = 3;
        ship[3].health = 3;

        ship[4].model  = ShipModel::Submarine;
        ship[4].name   = "Submarine";
        ship[4].symbol = 'S';
        ship[4].size   = 2;
        ship[4].health = 2;
    }

};

void play_battleship();
bool want_to_play_again();
std::string get_name(const std::string& prompt);
void print_board(const Player& p);
void init_board(Player& p);
ShipPose get_pose();
bool is_pose_valid(const ShipPose& pose, const int ship_index, const Player& p);

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


    init_board(player_1);
    init_board(player_2);
}

void init_board(Player& p)
{
    
    for (int i = 0; i < fleet_size; i++)
    {
        print_board(p);
        std::cout << "Establish your " << p.ship[i].name;
        std::cout << " position (length " << p.ship[i].size << ").\n";

        ShipPose pose;
        do
        {
            pose = get_pose();
        }
        while (!is_pose_valid(pose, i, p));

        if (pose.orientation == 0)
            for (int j = 0; j < p.ship[i].size; j++)
                p.location[pose.y + j][pose.x].show = p.ship[i].symbol;
        else
            for (int j = 0; j < p.ship[i].size; j++)
                p.location[pose.y][pose.x + j].show = p.ship[i].symbol;
        clear_screen;

    }

    print_board(p);
}

ShipPose get_pose()
{
    ShipPose pose;

    std::string orientation_prompt = "orientation (vertical=0, horizontal=1): ";
    pose.orientation = get_value<int>(orientation_prompt, 0, 1);
    pose.x = get_value<int>("x position (0-9): ", 0, 9);
    pose.y = get_value<char>("y position (A-J): ", 'A', 'J') - 'A';

    return pose;
}

bool is_pose_valid(const ShipPose& pose, const int ship_index, const Player& p)
{
    bool is_valid = false;
    if (pose.orientation == 0) // Vertical
    {
        is_valid = pose.y + p.ship[ship_index].size - 1 < cells_per_side;
    }
    else
    {
        is_valid = pose.x + p.ship[ship_index].size - 1 < cells_per_side;
    }

    if (!is_valid)
    {
        clear_screen();
        print_board(p);
        std::cout << "Ship is out of bounds, please try again\n";
    }

    return is_valid;
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
        else if (name.length() > grid_length - 1) // grid length - left padding
        {
            std::cout << "Your name is too long buddy, try a shorter one.\n";
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
    for (int x = 0; x < cells_per_side; x++)
    {
        std::cout << ' ' << ' ' << ' ' << x;
    }
    std::cout << ' ' << ' ' << grid_padding;
}

void print_border()
{
    std::cout << ' ';
    for (int x = 0; x < cells_per_side; x++)
    {
        std::cout << "+---";
    }
    std::cout << '+' << grid_padding;
}

void print_row(const Cell row[cells_per_side], int number)
{
    std::cout << static_cast<char>(number + 'A') << '|';
    for (int x = 0; x < cells_per_side; x++)
    {
         std::cout << ' ' << row[x].show << " |";
    }
    std::cout << grid_padding;
}

void print_board(const Player& p)
{
    clear_screen();

    std::cout << ' ' << p.name;

    for (int i = 0; i < grid_length - p.name.length() - 1; i++)
        std::cout << ' ';

    std::cout << grid_padding;
    
    std::cout << ' ' <<  "Enemy\n";

    print_column_headers();
    print_column_headers();
    std::cout << '\n';

    print_border();
    print_border();
    std::cout << '\n';

    for (int y = 0; y < cells_per_side; y++)
    {
        print_row(p.location[y], y);
        print_row(p.enemy_location[y], y);
        std::cout << '\n';

        print_border();
        print_border();
        std::cout << '\n';
    }
}

