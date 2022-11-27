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
    string_process::trim(result);
    delete result_buf;
    return result;
}


#ifdef _env_linux
void sys_call_namesp::registerSignalHandler(UnixSignal sig, SignalHandlerFunc f)
{
    let result = signal_unix_namesp::signal(int(sig), f);
    if (result == SIG_ERR) { }
}


void sys_call_namesp::unregisterSignalHandler(UnixSignal sig)
{
    signal_unix_namesp::signal(int(sig), SIG_DFL);
}
#elif _env_windows
#endif


string sys_call_namesp::getANSIResponse(const string& command, const char& ending_sign)
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


void sys_call_namesp::prepareConsole()
{
    // Idea from: https://stackoverflow.com/questions/46142246/getchar-with-non-canonical-mode-on-unix-and-windows
#ifdef _env_linux
    // Set non-buffering output. What you write to stdout will immediately appear.
    setvbuf(stdio::stdout, nullptr, _IONBF, 0);

    // Set the console.
    termios current_console_setting;
    tcgetattr(stdio::stdin_fd, &current_console_setting);
    current_console_setting.c_iflag &= ~(IXON | ICRNL);
    current_console_setting.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
    current_console_setting.c_cc[VMIN]  = 0;
    current_console_setting.c_cc[VTIME] = 1;
    tcsetattr(stdio::stdin_fd, TCSANOW, &current_console_setting);

    // Set keyboard.
    ioctl(stdio::stdin_fd, KDSKBMODE, K_MEDIUMRAW);


#elif _env_windows
    DWORD  current_console_mode;
    HANDLE current_console = GetStdHandle(STD_INPUT_HANDLE);

    GetConsoleMode(current_console, &current_console_mode);
    SetConsoleMode(current_console, current_console_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
#endif
}


void sys_call_namesp::restoreConsole()
{
#ifdef _env_linux
    tcsetattr(stdio::stdin_fd, TCSANOW, &default_console_state);
    ioctl(stdio::stdin_fd, KDSKBMODE, &default_keyboard_state);
#elif _env_windows
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), default_console_state);
#endif
}


#ifdef _env_linux
sys_call_namesp::termios sys_call_namesp::getDefaultConsoleState()
{
    termios state;
    tcgetattr(0, &state);
    return state;
}


int sys_call_namesp::getDefaultKeyboardState()
{
    int kbd_mode;
    ioctl(stdio::stdin_fd, KDGKBMODE, &kbd_mode);
    return kbd_mode;
}
#elif _env_windows
DWORD sys_call_namesp::getDefaultConsoleState()
{
    DWORD mode;
    GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
    return mode;
}


int sys_call_namesp::getDefaultKeyboardState()
{
    // TODO: No need to get?
    return 0;
}
#endif


void sys_call_namesp::changeToAlternativeScreen()
{
#ifdef _env_linux
    system("tput smcup");
#elif _env_windows
#endif
}
void sys_call_namesp::backFromAlternativeScreen()
{
#ifdef _env_linux
    system("tput rmcup");
#elif _env_windows
#endif
}

#ifdef _env_windows
CONSOLE_SCREEN_BUFFER_INFO sys_call_namesp::getConsoleScreenBufferInfo()
{
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_buffer_info);
    return screen_buffer_info;
}
#endif