#include "main.h"

int main(int argc, char const* argv[])
{
    std::system("tput smcup");
    clearScreen();
    ConsoleConfig* console_config = new ConsoleConfig();
    input("Waiting: ");
    std::system("tput rmcup");
    return 0;
}
