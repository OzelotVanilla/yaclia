#include "key_input.h"


bool key_input_namesp::getConsoleInput(ProcessedKeyInput& parsed_data_out)
{
    bool has_read_success;
#ifdef _env_linux
    let length_readed = stdio::read(stdio::stdin_fd, buffer, sizeof(buffer));
    has_read_success  = length_readed > 0;
#elif _env_windows
    has_read_success = ReadConsoleInput(key_input_namesp::stdin, key_input_namesp::buffer, 3, &key_input_namesp::num_readed);
#endif

    if (has_read_success)
    {
#ifdef _env_linux

        // This need to first changeto keyboard raw mode, then read and parse scan code
        // Refer to: https://www.linuxjournal.com/article/1080
        // Refer to: https://stackoverflow.com/questions/1409216/receiving-key-press-and-key-release-events-in-linux-terminal-applications

        // Size of `buffer` is 2 here.
        // If only one char is readed, that might be a normal input, or `ctrl + alphabet`

        // If a `ctrl + alphabet`
        if (buffer[0] <= 31)
        {
        }
        else if (buffer[0] = 27) { }

#elif _env_windows
        // Since it is only possible to give one at a time, if more than one, it should be warning
        // Refer to: https://learn.microsoft.com/ja-jp/windows/console/key-event-record-str
        for (size_t i = 0; i < key_input_namesp::num_readed; i++)
        {
            // cout << std::bitset<32>(int(irInBuf[i].Event.KeyEvent.dwControlKeyState)).to_string()
            //      << ", with char " << irInBuf[i].Event.KeyEvent.uChar.AsciiChar
            //      << ", with virtual code " << irInBuf[i].Event.KeyEvent.wVirtualKeyCode
            //      << endl;
        }
#endif
    }

    return has_read_success;
}