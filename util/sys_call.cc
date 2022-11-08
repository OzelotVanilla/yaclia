#include <boost/algorithm/string.hpp>
#include "sys_call.h"


string sys_call_namesp::getShellOutput(string command)
{
    return getFromStream(popen(command.c_str(), "r"));
}


/**
 * @brief Read from a FILE stream until finished
 *
 * @param stream FILE stream object
 * @return Content in the FILE
 */
string sys_call_namesp::getFromStream(FILE* stream)
{
    let*  result_buf = new std::stringstream();
    char  buffer[64];
    char* output_line;

    while ((output_line = fgets(buffer, 64, stream)) != nullptr)
    {
        *result_buf << buffer;
    }

    // Trim result
    let result = result_buf->str();
    boost::trim(result);
    delete result_buf;
    return result;
}
