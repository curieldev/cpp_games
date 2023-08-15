cmake_minimum_required(VERSION "3.1")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(NumberGuesser VERSION 1.0)
add_executable(NumberGuesser number_guesser.cpp)

project(TheGameOfEight VERSION 1.0)
add_executable(TheGameOfEight the_game_of_eight.cpp)

project(Hangman VERSION 1.0)
add_executable(Hangman hangman.cpp)
