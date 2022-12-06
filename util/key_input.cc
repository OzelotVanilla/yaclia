#include "key_input.h"


bool key_input_namesp::getAndWriteKeyInputToBuffer(KeyInputBuffer& key_input_buffer)
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

        // Size of `buffer` is 6 here.
        // If only one char is readed, that might be a normal input, or `ctrl + alphabet`

        bool has_previous_seq = false;
        bool alt_code_found   = false;

        // printf("raw: ");
        // for (size_t i = 0; i < length_readed; i++)
        // {
        //     printf("%3d, ", buffer[i]);
        // }
        // printf("\b\r\n");


        for (isize i = 0; i < length_readed; i++)
        {
            // If there is a modifier such as alt.
            if (has_previous_seq)
            {
                // Arrow key, read next key
                if (alt_code_found)
                {
                    // Now `i` is at the second position. Or to say, just after code `27`.
                    ProcessedKeyInput key_input;
                    switch (length_readed - i + 1)
                    {
                    case 2: // `ctrl + alt + key`, or normal `alt + key`.
                        // Notice that `ctrl + alt + m` works.
                        if (buffer[i] <= 26) { key_input = { KbdChar(int(KbdChar::a) + buffer[i] - 1), KbdModifier::ctrl_alt }; }
                        else { key_input = { KbdChar(buffer[i]), KbdModifier::alt }; }
                        break;

                    case 3: // Arrow key, `27 91 65~68`.
                        if (buffer[i] == 91)
                        {
                            const let second_code = isize(buffer[i + 1]);
                            if (second_code >= 65 and second_code <= 68)
                            {
                                key_input = { KbdChar(int(KbdChar::arrow_up) + (buffer[i + 1] - 65)),
                                              KbdModifier::none };
                            }
                            else if (second_code == 90) { key_input = { KbdChar::tab, KbdModifier::none }; }
                            else { throw UnknownKeyInputSeq("27 91 " + parseString(second_code)); }
                        }
                        else { throw UnknownKeyInputSeq("27 " + parseString(buffer[i]) + " " + parseString(buffer[++i])); }
                        break;

                    case 6: // Arrow key with modifier.
                        if (buffer[i] == 91 and buffer[i + 1] == 49 and buffer[i + 2] == 59)
                        {
                            KbdModifier modifier;
                            switch (buffer[i + 3])
                            {
                            case 50:
                                modifier = KbdModifier::shift;
                                break;
                            case 51:
                                modifier = KbdModifier::alt;
                                break;
                            case 53:
                                modifier = KbdModifier::ctrl;
                                break;
                            case 55:
                                modifier = KbdModifier::ctrl_alt;
                                break;
                            }
                            key_input = { KbdChar(int(KbdChar::arrow_up) + (buffer[i + 4] - 65)), modifier };
                        }
                        // Get a scroll up
                        else if (buffer[3] == '\e' and buffer[2] == buffer[5])
                        {
                            key_input = { KbdChar(int(KbdChar::scroll_up) + (buffer[2] - 65)), KbdModifier::none };
                        }
                        else
                        {
                            throw UnknownKeyInputSeq(
                                "27 " + parseString(buffer[i]) + " "
                                + parseString(buffer[i + 1]) + " "
                                + parseString(buffer[i + 2]) + " "
                                + parseString(buffer[i + 3]) + " "
                                + parseString(buffer[i + 4])
                            );
                        }
                        break;

                    default:
                        string unknow_seq;
                        break;
                    } // end of alt sequence `switch`.

                    key_input_buffer.push(key_input);

                    alt_code_found = false;
                    i += length_readed - i - 1;
                } // if alt code

                has_previous_seq = false;
            }
            // It is a pure new sequence to read, no previous state or modifier.
            else
            {
                ProcessedKeyInput key_input;

                // If a `ctrl + alphabet` or a enter.
                if (buffer[i] <= 26)
                {
                    // But it can be a `tab`.
                    if (buffer[i] == 9) { key_input = { KbdChar::tab, KbdModifier::none }; }
                    // Or a `enter`.
                    else if (buffer[i] == 13) { key_input = { KbdChar::enter, KbdModifier::none }; }

                    // Or it is a `ctrl + alphabet`, remember `ctrl + a` is `1` not `0`.
                    // Because `0` for `ctrl + space`.
                    else if (buffer[i] == 0) { key_input = { KbdChar::space, KbdModifier::ctrl }; }
                    else { key_input = { KbdChar(96 + buffer[i]), KbdModifier::ctrl }; }
                }
                else if (buffer[i] == 27) // Might be a `esc` or `alt`, or something like arrow key.
                {
                    // If simple `esc`, there should not be text after
                    if (i + 1 >= length_readed) { key_input = { KbdChar::esc, KbdModifier::none }; }
                    // Else it is an `alt`, or something arrow key.
                    else
                    {
                        alt_code_found = has_previous_seq = true;
                        continue;
                    }
                }
                else // Trival sequence, convert using ASCII code.
                {
                    key_input = { KbdChar(buffer[i]), KbdModifier::none };
                }

                key_input_buffer.push(key_input);
            }
        }



#elif _env_windows
        // Since it is only possible to give one at a time, if more than one, it should be warning
        // Refer to: https://learn.microsoft.com/ja-jp/windows/console/key-event-record-str
        for (isize i = 0; i < key_input_namesp::num_readed; i++)
        {
            // cout << std::bitset<32>(int(irInBuf[i].Event.KeyEvent.dwControlKeyState)).to_string()
            //      << ", with char " << irInBuf[i].Event.KeyEvent.uChar.AsciiChar
            //      << ", with virtual code " << irInBuf[i].Event.KeyEvent.wVirtualKeyCode
            //      << endl;
        }
#endif
    } // Read is success `if` clause.

    return has_read_success;
}

bool ProcessedKeyInput::operator==(const ProcessedKeyInput& key_input) const
{
    // If any state is invalid, give error.
    if (
        this->key == KbdChar::invalid or key_input.key == KbdChar::invalid
        or this->modifier == KbdModifier::invalid or key_input.modifier == KbdModifier::invalid
    )
    {
        throw InvalidKeyState(*this, key_input);
    }

    // If upper case using shift in one operand
    if ((this->modifier == KbdModifier::shift and key_input.modifier == KbdModifier::none)
        or (this->modifier == KbdModifier::none and key_input.modifier == KbdModifier::shift))
    {
        let lhs_key = int(this->key);
        let rhs_key = int(key_input.key);
        // To lower case
        if (lhs_key >= 65 and lhs_key <= 90) { lhs_key += 32; }
        if (rhs_key >= 65 and rhs_key <= 90) { rhs_key += 32; }
        return lhs_key == rhs_key;
    }

    // Trival comparison.
    return this->key == key_input.key and this->modifier == key_input.modifier;
}


string key_input_namesp::str(const ProcessedKeyInput& key_input)
{
    std::stringstream result;
    result << "ProcessedKeyInput@{key: '";
    const let key_code = int(key_input.key);
    if (key_code >= 32 and key_code <= 126)
    {
        result << char(key_code) << "', ";
    }
    else { result << "code_" << key_code << "', "; }

    string modifier;
    switch (key_input.modifier)
    {
    case KbdModifier::invalid:
        modifier = "invalid";
        break;
    case KbdModifier::none:
        modifier = "none";
        break;
    case KbdModifier::alt:
        modifier = "alt";
        break;
    case KbdModifier::ctrl:
        modifier = "ctrl";
        break;
    case KbdModifier::shift:
        modifier = "shift";
        break;
    case KbdModifier::alt_shift:
        modifier = "alt_shift";
        break;
    case KbdModifier::ctrl_alt:
        modifier = "ctrl_alt";
        break;
    default:
        modifier = "[Unimplemented modifier " + parseString(int(key_input.modifier)) + "]";
        break;
    }
    result << "modifier: " << modifier << "}";

    return result.str();
}


ProcessedKeyInput::ProcessedKeyInput(KbdChar key, KbdModifier modifier)
{
    // Check if correct
    if (modifier == KbdModifier::ctrl)
    {
        let key_code = int(key);
        if (
            (key_code >= 48 and key_code <= 57)
            or (key_code == 73 or key_code == 105) // `i`
            or (key_code == 77 or key_code == 109) // `m`
        )
        {
            throw key_input_namesp::NotAllowedKeyCombination(string("ctrl + ") + char(key_code));
        }
    }

    this->key      = key;
    this->modifier = modifier;
}

ProcessedKeyInput::ProcessedKeyInput()
{
    this->key      = KbdChar::invalid;
    this->modifier = KbdModifier::invalid;
}