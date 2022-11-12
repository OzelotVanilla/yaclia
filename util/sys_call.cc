#include <boost/algorithm/string.hpp>
#include "sys_call.h"


string sys_call_namesp::getShellOutput(string command)
{
    return getFromStream(popen(command.c_str(), "r"));
}


string sys_call_namesp::getFromStream(FILE* stream)
{
    let* result_buf = new std::stringstream();
    char buffer[64];

    while (fgets(buffer, 64, stream) != nullptr)
    {
        *result_buf << buffer;
    }

    // Trim result
    let result = result_buf->str();
    boost::trim(result);
    delete result_buf;
    return result;
}


void sys_call_namesp::registerSignalHandler(UnixSignal sig, SignalHandlerFunc f)
{
    sys_call_namesp::signal_unix_namesp::signal(int(sig), f);
}


void sys_call_namesp::unregisterSignalHandler(UnixSignal sig)
{
    using sys_call_namesp::signal_unix_namesp::__sighandler_t;
    sys_call_namesp::signal_unix_namesp::signal(int(sig), SIG_DFL);
}