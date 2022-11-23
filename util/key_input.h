#pragma once

#include "../head.h"

namespace key_input_namesp
{

struct ProcessedKeyInput;


/**
 * @brief Get parsed keyboard input from raw. Console must be non-blocking and non-echo-input now!
 *
 * @param parsed_data_out Pass the structure for receiving parsed data.
 * @return true: Valid data got.
 * @return false: Non-valid data.
 */
bool getConsoleInput(ProcessedKeyInput& parsed_data_out);

// Function returning `stdin` or "stdin handle"
#ifdef _env_linux
static let  stdin = stdio::stdin;
static char buffer[6];
static int  num_readed;
#elif _env_windows
static let          stdin = GetStdHandle(STD_INPUT_HANDLE);
static INPUT_RECORD buffer[2];
static DWORD        num_readed;
#endif

// If using local console
bool checkAndStoreIfConsoleLocal();
#ifdef _env_linux
#elif _env_windows
#endif


struct ProcessedKeyInput
{
    enum class KbdChar
    {
        colon     = 58,
        semicolon = 59,
        a         = 97,
        b,
        c,
        d,
        e,
        f,
        g,
        h,
        i,
        j,
        k,
        l,
        m,
        n,
        o,
        p,
        q,
        r,
        s,
        t,
        u,
        v,
        w,
        x,
        y,
        z,
    };

    enum class Modifier
    {
        none,
        alt,
        ctrl,
        shift,
        alt_shift
    };

    char     key;
    Modifier modifier;
};
} // namespace key_input_namesp

using key_input_namesp::ProcessedKeyInput;
using key_input_namesp::getConsoleInput;