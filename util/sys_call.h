#pragma once
#include "../head.h"

namespace sys_call_namesp
{

#include <stdio.h>
#include <stdlib.h>
#include "../signal/UnixSignal.h"

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

/**
 * @brief Register a handler to a signal. Notice this will be effective in this program.
 *
 * @param sig Signal to listen.
 * @param f Action to do.
 */
void registerSignalHandler(UnixSignal sig, SignalHandlerFunc f);

void unregisterSignalHandler(UnixSignal sig);

} // namespace sys_call_namesp

using sys_call_namesp::getFromStream;
using sys_call_namesp::getShellOutput;
using sys_call_namesp::registerSignalHandler;
using sys_call_namesp::unregisterSignalHandler;