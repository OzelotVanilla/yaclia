#pragma once

#include "../head.h"

namespace key_input_namesp
{

struct ProcessedKeyInput
{
    enum class Modifier
    {
        none,
        alt,
        ctrl,
        shift,
        alt_gr
    };

    char     key;
    Modifier modifier;
};

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
static char buffer[8];
static int  num_readed;
#elif _env_windows
static let          stdin = GetStdHandle(STD_INPUT_HANDLE);
static INPUT_RECORD buffer[8];
static DWORD        num_readed;
#endif

#ifdef _env_linux
#elif _env_windows
#endif

} // namespace key_input_namesp

using key_input_namesp::ProcessedKeyInput;
using key_input_namesp::getConsoleInput;