#pragma once

#include "../head.h"

#include <queue>
#include "../system/sys_call.h"


namespace key_input_namesp
{

/**
 * Suggest use `alt` for most shortcut.
 *
 * Do not use keys combination like:
 * * `ctrl` with numbers.
 * * `ctrl + I` (conflict with `tab`)
 * * `ctrl + M` (conflict with `enter`)
 * * Function key like `f1`, it is occupied for most system.
 */
struct ProcessedKeyInput;
typedef std::queue<ProcessedKeyInput> KeyInputBuffer;


/**
 * @brief Get parsed keyboard input from raw. Console must be non-blocking and non-echo-input now!
 *
 * @param key_input_buffer The buffer to contain the processed key input.
 * @return true: Valid data got.
 * @return false: Non-valid data.
 */
bool getAndWriteKeyInputToBuffer(KeyInputBuffer& key_input_buffer);

// Function returning `stdin` or "stdin handle"
#ifdef _env_linux
static let  stdin = stdio::stdin;
static char buffer[6];
static int  num_readed;
#elif _env_windows
static let          stdin = GetStdHandle(STD_INPUT_HANDLE);
static INPUT_RECORD buffer[2];
static DWORD        num_readed;
#endif

enum class KbdChar;

enum class KbdModifier;

struct ProcessedKeyInput
{
    KbdChar     key;
    KbdModifier modifier;

    ProcessedKeyInput();
    ProcessedKeyInput(KbdChar key, KbdModifier modifier);

    /**
     * Solve some problems like uppercase with `shift + alphabet`.
     */
    bool operator==(const ProcessedKeyInput& rhs);
}; // struct ProcessedKeyInput

string str(const ProcessedKeyInput& key_input);

class UnknownKeyInputSeq : public std::exception
{
  public:
    string reason;

    virtual const char* what() const noexcept override
    {
        return this->reason.c_str();
    }

    UnknownKeyInputSeq(string sequence)
    {
        this->reason = "\033[38;2;236;109;113m[ERR!] Unhandled input for unknown sequence "
                       + sequence
                       + ".\033[0m";
    }
};

class InvalidKeyState : public std::exception
{
  public:
    string reason;

    virtual const char* what() const noexcept override
    {
        return this->reason.c_str();
    }

    InvalidKeyState(const ProcessedKeyInput& lhs, const ProcessedKeyInput& rhs)
    {
        this->reason = string("\033[38;2;236;109;113m[ERR!] The key state is invalid for:\r\n")
                       + "operand left: key: "
                       + parseString(int(lhs.key)) + ", modifier: " + parseString(int(lhs.modifier)) + "\r\n"
                       + "operand right: key: "
                       + parseString(int(rhs.key)) + ", modifier: " + parseString(int(rhs.modifier)) + "\r\n"
                       + "\033[0m";
    }
};

class NotAllowedKeyCombination : public std::exception
{
  public:
    string reason;

    virtual const char* what() const noexcept override
    {
        return this->reason.c_str();
    }

    NotAllowedKeyCombination(string reason = "")
    {
        this->reason = "\033[38;2;236;109;113m[ERR!] Cannot allow key combination "
                       + reason
                       + " due to the design of console."
                         " It will lead to collision with more usual key. \033[0m";
    }
};

} // namespace key_input_namesp

using key_input_namesp::ProcessedKeyInput;
using key_input_namesp::KbdChar;
using key_input_namesp::KbdModifier;
using key_input_namesp::KeyInputBuffer;
using key_input_namesp::getAndWriteKeyInputToBuffer;
using key_input_namesp::str;

enum class key_input_namesp::KbdChar
{
    invalid = -1,
    enter   = 13,
    esc     = 27,
    space   = 32,
    exclamation,
    double_quote,
    hash_sign,
    dollar_sign,
    percent,
    ampersand,
    single_quote,
    left_parenthesis,
    right_parenthesis,
    asterisk,
    plus,
    comma,
    hyphen,
    dot,
    slash,
    number_0 = 48,
    number_1,
    number_2,
    number_3,
    number_4,
    number_5,
    number_6,
    number_7,
    number_8,
    number_9,
    colon = 58,
    semicolon,
    less_than,
    equal,
    greater_than,
    question,
    at_sign,
    A = 65,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    a = 97,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    left_brace,
    backslash,
    right_brace,
    tilde,
    arrow_up,
    arrow_down,
    arrow_right,
    arrow_left
};

enum class key_input_namesp::KbdModifier
{
    invalid = -1,
    none,
    alt,
    ctrl,
    shift,
    alt_shift,
    ctrl_alt
};