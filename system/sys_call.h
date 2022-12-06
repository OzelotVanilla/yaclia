#pragma once

#include "../head.h"

// Signal
#include "signal/signal.h"



namespace sys_call_namesp
{

#include "../util/string_process.h"


/* Console related files' include*/;
#ifdef _env_linux
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#elif _env_windows
// #include <windows.h>
#endif
/* End of console related files' include*/;

/**
 * Function accepting int, return void, to handle signal.
 */
using SignalHandlerFunc = void (*)(int);


/**
 * Get the output of a shell command (sync).
 *
 * @param command The command to execute, and get result
 * @return The result of
 */
string getShellOutput(string command);


/**
 * @brief Read from a @c FILE stream until finished
 *
 * @param stream @c FILE stream object
 * @return Content in the @c FILE stream object
 */
string getFromStream(FILE* stream);



// Signal Processing
#ifdef _env_linux

using signal_unix_namesp::__sighandler_t;


/**
 * @brief Register a handler to a signal. Notice this will be effective in this program.
 *
 * @param sig Signal to listen.
 * @param f Action to do.
 */
void registerSignalHandler(UnixSignal sig, SignalHandlerFunc f);


/**
 * @brief Unregister previous registered signal handler
 *
 * @param sig Signal to unregister handle
 */
void unregisterSignalHandler(UnixSignal sig);

#elif _env_windows

/**
 * @brief Register a handler to a signal. Notice this will be effective in this program.
 *
 * @param sig Signal to listen.
 * @param f Action to do.
 */
void registerSignalHandler(WindowsSignal sig, SignalHandlerFunc f);


/**
 * @brief Unregister previous registered signal handler
 *
 * @param sig Signal to unregister handle
 */
void unregisterSignalHandler(WindowsSignal sig);

#endif // End of signal processing



/**
 * @brief Read a response of inputting ANSI escape sequence
 *
 * @param command ANSI escape sequence to input.
 * @param ending_sign The end sign for response.
 * @return Response typed string.
 */
string getANSIResponse(const string& command, const char& ending_sign);


/**
 * @brief Set the current console to
 *
 */
void prepareConsole();


void restoreConsole();

#ifdef _env_linux
termios getDefaultConsoleState();
int     getDefaultKeyboardState();
#elif _env_windows
/**
 *
 */
DWORD getDefaultConsoleState();


#endif

static let default_console_state  = getDefaultConsoleState();
static let default_keyboard_state = getDefaultKeyboardState();

// Alternative Screen Related

void changeToAlternativeScreen();
void backFromAlternativeScreen();
#ifdef _env_linux
#elif _env_windows
/**
 *
 */
CONSOLE_SCREEN_BUFFER_INFO getConsoleScreenBufferInfo();

/**
 *
 */
static let previous_screen_buffer = getConsoleScreenBufferInfo();
#endif


// Print related

static char print_stdout_buffer[1024];


/**
 * @brief A non-buffer print to stdout
 *
 * @param format_str Format string for output. Same as `printf` family.
 * @param ...
 */
inline void printStdout(const char* format_str, ...)
{
    va_list args;

    va_start(args, format_str);
    vsprintf(print_stdout_buffer, format_str, args);
    stdio::write(stdio::stdout_fd, print_stdout_buffer, sizeof(print_stdout_buffer));
    // stdio::write(stdio::stdout_fd, print_stdout_buffer, sizeof(print_stdout_buffer));
    va_end(args);
}


inline void printStdout(const string& format_str, ...)
{
    va_list args;

    va_start(args, format_str);
    vsprintf(print_stdout_buffer, format_str.c_str(), args);
    stdio::write(stdio::stdout_fd, print_stdout_buffer, sizeof(print_stdout_buffer));
    va_end(args);
}


inline void writeStdout(const char* str, int length_to_write)
{
    stdio::write(stdio::stdout_fd, str, length_to_write);
}


inline void writeStdout(const string& str)
{
    writeStdout(str.c_str());
}


inline void writeStdout(const char* str)
{
    int length_to_write = 0;
    while (str[length_to_write] != '\0') { length_to_write++; }
    writeStdout(str, length_to_write);
}


inline void flushOutputToConsole()
{
    fflush(stdio::stdout);
}

} // namespace sys_call_namesp

using sys_call_namesp::getFromStream;
using sys_call_namesp::getShellOutput;
using sys_call_namesp::registerSignalHandler;
using sys_call_namesp::unregisterSignalHandler;
using sys_call_namesp::getANSIResponse;
using sys_call_namesp::prepareConsole;
using sys_call_namesp::restoreConsole;
using sys_call_namesp::changeToAlternativeScreen;
using sys_call_namesp::backFromAlternativeScreen;
using sys_call_namesp::printStdout;
using sys_call_namesp::writeStdout;
using sys_call_namesp::flushOutputToConsole;