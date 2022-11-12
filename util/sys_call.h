#pragma once
#include "../head.h"

namespace sys_call_namesp
{

#include <stdio.h>
#include <stdlib.h>

/**
 * Get the 
 * 
 * @param command The command to execute, and get result
 * @return The result of 
 */
string getShellOutput(string command);

/**
 * @brief Read from a FILE stream until finished
 *
 * @param stream FILE stream object
 * @return Content in the FILE
 */
string getFromStream(FILE* stream);

} // namespace sys_call_namesp

using sys_call_namesp::getFromStream;
using sys_call_namesp::getShellOutput;