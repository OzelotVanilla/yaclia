#include "main.h"

bool main_process_can_run = true;

int main(int argc, char const* argv[])
{
    registerAllSignalHandler();

    // Start view manager
    // view_manager.start();

    //  Main Process
    // view_manager.run();

    char buffer[64];
    int  stdin_fd = stdio::open("/dev/stdin", O_RDONLY);

    int                      previous_kbd_mode;
    sys_call_namesp::termios previous_console_setting, current_console_setting;
    sys_call_namesp::tcgetattr(stdin_fd, &current_console_setting);
    previous_console_setting = current_console_setting;
    current_console_setting.c_iflag &= ~(IXON | ICRNL);
    current_console_setting.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
    // This will help differentiate `esc` and `alt`.
    // When `alt` + `key`, `read` function get two, not one.
    current_console_setting.c_cc[VMIN]  = 0;
    current_console_setting.c_cc[VTIME] = 1;
    sys_call_namesp::tcsetattr(stdin_fd, TCSANOW, &current_console_setting);
    sys_call_namesp::ioctl(stdin_fd, KDGKBMODE, &previous_kbd_mode);
    sys_call_namesp::ioctl(stdin_fd, KDSKBMODE, K_RAW);

    // Check if it is local, or non-local
    //  Key is: if it can get medium_raw
    //  SSH_TTY, SSH_CONNECTION, or SSH_CLIENT
    bool if_ssh = std::getenv("SSH_CLIENT") == nullptr
                  or std::getenv("SSH_TTY") == nullptr
                  or std::getenv("SSH_CONNECTION") == nullptr;

    struct stdio::stat input_device_info;
    bool               is_input_existed = stdio::stat("/dev/input/", &input_device_info) == 0;


    bool can_run = true;
    while (can_run)
    {
        let length_readed = stdio::read(stdin_fd, buffer, sizeof(buffer));
        for (size_t i = 0; i < length_readed; i++)
        {
            let keycode          = (buffer[i] & 0x7f);
            let press_or_release = (buffer[i] & 0x80); // true: press, false: release
            printf("%3d %s", keycode, press_or_release ? "press" : "release");
            printf(" with code %s\r\n", parseBinString(buffer[i]).c_str());

            if (keycode == 'q')
            {
                printf("%s\n", "Should terminate when 'q' pressed.");
                can_run = false;
            }
        }
        if (length_readed != 0) { printf("----\r\n"); }
    }



    // Restore
    sys_call_namesp::tcsetattr(STDIN_FILENO, TCSANOW, &previous_console_setting);
    sys_call_namesp::ioctl(STDIN_FILENO, KDSKBMODE, &previous_kbd_mode);



    // view_manager.end();
    return 0;
}


#ifdef _env_linux
void registerAllSignalHandler()
{
    registerSignalHandler(UnixSignal::interrupt, onInterrupt);
}


void onInterrupt(int sig)
{
    view_manager.handleInterrupt();
}
#elif _env_windows
void registerAllSignalHandler()
{
}
#endif