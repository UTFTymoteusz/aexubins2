#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "getty: Not enough arguments\n");
        return 1;
    }

    char* filename = argv[1];

    FILE* tty_r = fopen(filename, "r");
    FILE* tty_w = fopen(filename, "w");

    dup2(fileno(tty_r), 0);
    dup2(fileno(tty_w), 1);
    dup2(fileno(tty_w), 2);

    fclose(tty_r);
    fclose(tty_w);

    printf("it works [%s]\n", filename);

    while (true) {
        char c = getchar();
        if (c == '\r')
            c = '\n';

        putchar(c);
    }

    while (true)
        sleep(1);

    return 0;
}