#include <iostream>
#include <random>
#include <cmath>


// Create a program called number guesser.
// There will be a secret number that is set at the start of the program without any user input.
// - The secret number should be picked from a certain range.
// - The range of the number should be output to the player.
// - The player should be prompted to enter his guess.
// - The prompt should show how many guesses the player has left.
// - The player will then enter his guess.
// - If the guess is too high then the game will output that the guess was too high.
// - If the guess was too low then the game will output that it was too low.
// - The player only has a certain number of guesses.
// - The number of guesses should be based on the range of the secret number.
// - Any wrong guess will decrement the number of guesses left.
// - The game ends by saying what the secret number was regardless of if the player guessed the right number.
// - When the game is over, the player should be prompted if he would like to play again.
// - If yes then the secret number should change.
// - Any input errors by the player should have proper handling.

void play_number_guesser();
bool want_to_play_again();
bool is_game_over(int guess, int attempts_left, int secret_number);
int  get_guess(int attempts_left);
void display_result(int last_guess, int secret_number);

int main(int argc, char **argv)
{
    do
    {
        play_number_guesser();
    } while (want_to_play_again());
    

    return 0;
}

void play_number_guesser()
{
    constexpr int SECRET_MIN = 1;
    constexpr int SECRET_MAX = 999;

    std::random_device random_device;
    std::uniform_int_distribution<int> dist(SECRET_MIN, SECRET_MAX);

    std::cout << "The secret number is between " << SECRET_MIN << " and ";
    std::cout << SECRET_MAX << ".\n";

    int secret_number = dist(random_device);
    int attempts_left = static_cast<int>(std::ceil(std::log2(SECRET_MAX - SECRET_MIN)));
    int guess = 0;

    do
    {
        guess = get_guess(attempts_left);

        if (guess > secret_number)
        {
            std::cout << "Too big.\n";
        }
        if (guess < secret_number)
        {
            std::cout << "Too small.\n";
        }

        attempts_left--;
    } while (!is_game_over(guess, attempts_left, secret_number));

    display_result(guess, secret_number);
}

bool want_to_play_again()
{
    char user_input = 0;
    bool failure = true;

    do
    {
        std::cout << "\n" << "Want to play again? (y=yes, n=no): ";
        std::cin >> user_input;

        if(std::cin.fail())
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

    return tolower(user_input) == 'y';
}

bool is_game_over(int guess, int attempts_left, int secret_number)
{
    return (guess == secret_number) || (attempts_left <= 0);
}

int  get_guess(int attempts_left)
{
    int guess = 0;
    bool failure = true;

    do
    {
        std::cout << "Enter your guess (" << attempts_left << " attempts left): ";
        std::cin >> guess;

        if(std::cin.fail())
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

    return guess;
}

void display_result(int last_guess, int secret_number)
{
    if (last_guess == secret_number)
        std::cout << "You got it! It was: " << secret_number << "\n";
    else
        std::cout << "Good luck next time. It was: " << secret_number << "\n";
}
