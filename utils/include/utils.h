#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include <string>

//! Only primitive data types
template<typename T> 
extern T get_value(const std::string& prompt);

//! Only primitive data types
template<typename T> 
extern T get_value(const std::string& prompt, const T& min, const T& max);

#endif // GAME_UTILS_H
