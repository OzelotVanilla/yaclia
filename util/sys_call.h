#pragma once
#include "../head.h"

namespace sys_call_namesp
{

#include <stdio.h>
#include <stdlib.h>

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