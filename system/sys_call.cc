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
    let result = signal_unix_namesp::signal(int(sig), f);
    if (result == SIG_ERR) { }
}


void sys_call_namesp::unregisterSignalHandler(UnixSignal sig)
{
    signal_unix_namesp::signal(int(sig), SIG_DFL);
}


string sys_call_namesp::getANSIResponse(string command, char ending_sign)
{
    printf("%s", command.c_str());

    char result_arr[20];
    int  c;
    int  i = 0;
    while (c = getchar())
    {
        result_arr[i++] = c;
        if (c == ending_sign) { break; }
    }
    result_arr[i] = '\0';

    return string(result_arr);
}


void sys_call_namesp::setCurrentConsoleNonBlocking()
{
    // Idea from: https://stackoverflow.com/questions/50884685/how-to-get-cursor-position-in-c-using-ansi-code
    // Get console previous setting
    termios current_console_setting;
    tcgetattr(0, &current_console_setting);
    current_console_setting.c_lflag &= ~(ICANON bitor ECHO);
    tcsetattr(0, TCSANOW, &current_console_setting);
}


void sys_call_namesp::setCurrentConsoleDefault()
{
    tcsetattr(0, TCSANOW, &default_console);
}



sys_call_namesp::termios sys_call_namesp::getDefaultConsole()
{
    termios state;
    tcgetattr(0, &state);
    return state;
}