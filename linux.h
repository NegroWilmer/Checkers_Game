#ifndef LINUX_H
#define LINUX_H

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>

inline int _getch() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

#endif 

