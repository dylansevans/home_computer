#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float win_or_loss();

int main() {
    printf("Hello!\n");
    printf("%f\n", win_or_loss());
    return 0;
}

float win_or_loss() {
    srand(time(NULL));
    int number = rand() & 1;

    return number;
}