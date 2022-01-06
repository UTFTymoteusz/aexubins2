#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "getty: Not enough arguments\n");
        return 1;
    }

    char* filename = argv[1];

    FILE* tty_0 = fopen(filename, "r");
    if (!tty_0) {
        perror("open new stdin");
        return 1;
    }

    FILE* tty_1 = fopen(filename, "w");
    if (!tty_1) {
        perror("open new stdout");
        return 1;
    }

    FILE* tty_2 = fopen(filename, "w");
    if (!tty_2) {
        perror("open new stderr");
        return 1;
    }

    dup2(fileno(tty_0), 0);
    dup2(fileno(tty_1), 1);
    dup2(fileno(tty_2), 2);

    printf("it works [%s]\n", filename);

    FILE* bong = fopen("/out.txt", "w");
    /*if (!bong) {
        perror("fopen");
        return 1;
    }*/

    while (true) {
        int c = getchar();
        if (c == '\r')
            c = '\n';

        if (c == -1)
            perror("getchar");

        if (c == EOF)
            break;

        if (putc(c, bong) == -1) {
            perror("write");
            break;
        }
    }

    fclose(bong);
    return 0;
}