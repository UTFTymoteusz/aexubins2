#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("it works\n");

    while (true)
        sleep(1);

    return 0;
}