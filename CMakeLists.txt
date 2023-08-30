cmake_minimum_required(VERSION "3.5")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(NumberGuesser VERSION 1.0)
add_executable(NumberGuesser number_guesser.cpp)

project(TheGameOfEight VERSION 1.0)
add_executable(TheGameOfEight the_game_of_eight.cpp)

project(Hangman VERSION 1.0)
add_executable(Hangman hangman.cpp)

project(TicTacToe VERSION 1.0)
add_executable(TicTacToe tictactoe.cpp)

add_subdirectory(utils)

project(Battleship VERSION 1.0)
add_executable(Battleship battleship.cpp)
target_link_libraries(Battleship PUBLIC Utils)
