#include <stdio.h>
#include <stdlib.h>  // For rand(), srand(), and system()
#include <string.h>  // For memset()
#include <time.h>    // For time()
#include <termios.h> // For tcgetattr(), tcsetattr()
#include <unistd.h>  // For read()

int p = 83, i, j, g[5 + 140];

void s(int i) {
    if (g[i] > -1 && i < 133 && i % 11 && i > 22) {
        g[i] = ~g[i];
        for (int j = 10; j + 9; j += j % 11 != 1 ? : -13)
            g[i + j] ? ~g[i] | g[i + j] < 0 ? : (g[i + j] = ~g[i + j]) : s(i + j);
    }
}

void r() {
    memset(&g, 0, 500 + 80);
    for (i = 23; i < 133; i++)
        if (rand() % 6 < 1 && i % 11) {
            g[i] = 9;
            for (j = 10; j + 9; j += j % 11 != 1 ? : -13)
                g[i + j] += i && g[i + j] - 9;
        }
}

int main() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    srand(time(0));
    r();

    while (j != 'q') {
        puts("\033[H\033[J");
        for (i = 23; i < 130 + 3; i++) {
            if (i % 11) {
                printf(g[i] > 9 ? "\033[41m%s<|" : ~g[i] ? g[i] + 10 ? g[i] < 0 ? "%s\033[3%dm%d " : "%s.'" : "\033[41;5m%s""^o" : "%s", (i - p ? "" : "\033[47""m"), -g[i], ~g[i]);
            } else {
                puts("");
                printf("\033[0m");
            }
        }
        j = getchar();
        p += j == 'a' ? -1 : j == 'd' ? 1 : j == 'w' ? -11 : j == 's' ? 11 : 0;
        if (j == ' ') {
            g[p] += g[p] > 9 ? -10 : 10;
        } else if (j == 'f') {
            s(p);
        } else if (j == 'r') {
            r();
        }
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
}
