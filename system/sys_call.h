#pragma once

#include "../head.h"
#include "signal/UnixSignal.h"



namespace sys_call_namesp
{

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>


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


void setCurrentConsoleNonBlocking();


void setCurrentConsoleDefault();


termios getDefaultConsole();


static termios default_console = getDefaultConsole();

} // namespace sys_call_namesp

using sys_call_namesp::getFromStream;
using sys_call_namesp::getShellOutput;
using sys_call_namesp::registerSignalHandler;
using sys_call_namesp::unregisterSignalHandler;
using sys_call_namesp::getANSIResponse;