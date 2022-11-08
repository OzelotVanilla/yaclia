#pragma once
#include <ciso646> // VS need this to recognize alternative operator
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <algorithm>
#include <map>
#include <queue>
#include <vector>

#include <cmath>
#include <functional>
#include <random>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;

using std::function;
using std::string;

typedef int8_t byte;

#define lambda(...) [](__VA_ARGS__)
#define lambda_ref(...) [&](__VA_ARGS__)

#define let auto
#define constructor
#define destructor ~constructor
#define delegate new (this) constructor

using std::for_each;
using std::sort;

using std::abs;

const double pi = 2 * std::asin(1);

inline int parseInt(string s)
{
    return std::stoi(s);
}

inline int parseInt(string s, int radix)
{
    if (radix > 36)
    {
        string reason = "Radix that is greater than 36 is invalid, current set to ";
        throw std::invalid_argument(reason.append(std::to_string(radix)).append("."));
    }

    return std::stoi(s, nullptr, radix);
}

inline string input()
{
    string s = "";
    cin >> std::noskipws >> s >> std::skipws;
    return s;
}

inline string input(string prompt)
{
    cout << prompt;
    return input();
}

inline void clearScreen()
{
    // cout << "\033[J";
    cout << "\033[H\033[J";
}

inline bool approxEqual(double a, double b)
{
    return abs(a - b) < 0.000001;
}

/**
 * @brief Function to get the first index of the value fulfill checker.
 *
 * This function is problematic.
 * Use form like (function<bool(SomeType)>)(lambda(){}) to avoid problem.
 *
 * @tparam EleType
 * @param container
 * @param checker
 * @return int
 */
template <typename EleType>
inline int indexOfFirst(const std::vector<EleType>& container, function<bool(EleType)> checker)
{
    return std::distance(container.begin(), std::find_if(container.begin(), container.end(), checker));
}

// template <typename EleType>
// inline EleType& getRandomElement(std::vector<EleType>& container)
// {
//     return container.at(randInt(0, container.size() - 1));
// }