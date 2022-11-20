#pragma once

#include "../head.h"
#include "signal/UnixSignal.h"



namespace sys_call_namesp
{

#include <stdio.h>
#include <stdlib.h>

/* Console related files' include*/;
#ifdef _env_linux
#include <termios.h>
#elif _env_windows
#include <windows.h>
#endif
/* End of console related files' include*/;

/**
 * Function accepting int, return void, to handle signal.
 */
typedef void (*SignalHandlerFunc)(int);


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


/**
 * @brief Read a response of inputting ANSI escape sequence
 *
 * @param command ANSI escape sequence to input.
 * @param ending_sign The end sign for response.
 * @return Response typed string.
 */
string getANSIResponse(string command, char ending_sign);


/**
 * @brief Set the current console to
 *
 */
void setCurrentConsoleNonBlocking();


void setCurrentConsoleDefault();

#ifdef _env_linux
termios getDefaultConsole();
#elif _env_windows
DWORD getDefaultConsole();
#endif

static let default_console = getDefaultConsole();

// Alternative Screen Related

void changeToAlternativeScreen();
void backFromAlternativeScreen();

} // namespace sys_call_namesp

using sys_call_namesp::getFromStream;
using sys_call_namesp::getShellOutput;
using sys_call_namesp::registerSignalHandler;
using sys_call_namesp::unregisterSignalHandler;
using sys_call_namesp::getANSIResponse;
using sys_call_namesp::setCurrentConsoleNonBlocking;
using sys_call_namesp::setCurrentConsoleDefault;