#include <iostream>
#include <string>

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

struct Position
{
    int x;
    int y;
};

enum struct ShipModel
{
    AircraftCarrier,
    Battleship,
    Cruiser,
    Destroyer,
    Submarine
};

struct Ship
{

    int size = 0;
    Position position = {0, 0};
    ShipModel model;
    Ship (ShipModel m) : model(m){};
};

// constexpr int AircraftCarrier = 0;
// constexpr int Battleship      = 1;
// constexpr int Cruiser         = 2;
// constexpr int Destroyer       = 3;
// constexpr int Submarine       = 4;

struct Board
{
    
    Ship aircraft_carrier = Ship(ShipModel::AircraftCarrier);
    Ship battleship;
    Ship cruiser;
    Ship destroyer;
    Ship submarine;
};

// Function Prototypes
void play_battleship();
bool want_to_play_again();
void get_position(Position& p);

int main(int argc, char **argv)
{
    do
    {
        play_battleship();
    } while (want_to_play_again());
    return 0;
}

void play_battleship()
{
    Position target = {0, 0};

    get_position(target);
    do
    {
        
    } while (true); //! TODO: Add stop condition
}

void get_position(Position& p)
{
    p.x = get_value<int>("Enter the x coordinate: ", 0, 10);
    p.y = get_value<char>("Enter the y coordinate: ", 'a', 'j');
}

bool want_to_play_again()
{
    char user_input = get_value<char>("Want to play again? (y=yes, n=no): ");

    return tolower(user_input) == 'y';
}

// TODO: Get coordinate from user
// TODO: Board structure
//   2 grids each board
//   Overload board cout


