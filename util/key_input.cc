#include "key_input.h"


bool key_input_namesp::getConsoleInput(ProcessedKeyInput& parsed_data_out)
{
    bool has_read_success;
#ifdef _env_linux

#elif _env_windows
    has_read_success = ReadConsoleInput(key_input_namesp::stdin, key_input_namesp::buffer, 3, &key_input_namesp::num_readed);
#endif

    if (has_read_success)
    {
#ifdef _env_linux



#elif _env_windows
        // Since it is only possible to give one at a time, if more than one, it should be warning
        for (size_t i = 0; i < key_input_namesp::num_readed; i++)
        {
            // cout << std::bitset<32>(int(irInBuf[i].Event.KeyEvent.dwControlKeyState)).to_string()
            //      << ", with char " << irInBuf[i].Event.KeyEvent.uChar.AsciiChar
            //      << ", with virtual code " << irInBuf[i].Event.KeyEvent.wVirtualKeyCode
            //      << endl;
        }
        return true;
#endif
    }

    return has_read_success;
}