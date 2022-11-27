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
#include <list>
#include <bitset>

#include <cmath>
#include <functional>
#include <random>
#include <time.h>


// Macro flags for system
#ifdef __linux__
#define _env_linux 1
#elif _WIN32
#define _env_windows 1
#endif

// Fix for missing types
#ifdef _env_linux
// Arm signal.h need this to understand type like `__u64`
#include <bits/types.h>
#include <linux/types.h>
#endif

// IO-related functions
#ifdef _env_linux
// In Linux, it is under stdio namespace
namespace stdio
{
#include <stdio.h>
// #ifdef stdin
// #undef stdin
// #endif
// #ifdef stdout
// #undef stdout
// #endif
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
static FILE* stdin     = stdin;
static int   stdin_fd  = STDIN_FILENO;
static FILE* stdout    = fopen("/dev/stdout", "rw");
static int   stdout_fd = STDOUT_FILENO;
} // namespace stdio
#elif _env_windows
// In Windows, due to too many macro define, currently not in namespace
#include <windows.h>
#ifdef stdin
#undef stdin
#endif
#endif

namespace std
{
#include <stdlib.h>
#include <cstdlib>
} // namespace std

#ifdef _env_linux
#include <stdarg.h>
#endif

using std::cin;
using std::cout;
using std::endl;

using std::function;
using std::string;
using std::vector;
using std::array;
using std::list;

// Conflict with windows, not used here
#ifdef _env_linux
typedef int8_t byte;
#endif

typedef char uchar;

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

inline string parseString(int num)
{
    return std::to_string(num);
}

inline string parseBinString(int num)
{
    return std::bitset<2 << sizeof(int)>(num).to_string();
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

inline bool approxEqual(double a, double b)
{
    return abs(a - b) < 0.000001;
}

template <typename EleType>
inline size_t len(const vector<EleType>& container)
{
    return container.size();
}

template <typename EleType>
inline size_t len(const list<EleType>& container)
{
    return container.size();
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