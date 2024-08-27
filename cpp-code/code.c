#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float run_many_times(int x, int y, int z);
int win_or_loss();
float score(int starting_amoung, int starting_bet);
int* get_parameters();

int main() {
    struct timespec currentTime;
    clock_gettime(CLOCK_REALTIME, &currentTime);
    srand(currentTime.tv_nsec);
    int *settings = get_parameters();
    printf("%.0f\n", run_many_times(10000, settings[0], settings[1]));
    printf("Stored Data:\n    Starting Amount: %d\n    Starting Bet: %d\n", get_parameters()[0], get_parameters()[1]);
    return 0;
}

int* get_parameters() {
    FILE *pntr;
    pntr = fopen("settings.txt", "r");
    char starting_amount[10];
    char starting_bet[10];
    fgets(starting_amount, 10, pntr);
    fgets(starting_bet, 10, pntr);
    static int data[2];
    data[0] = atoi(starting_amount);
    data[1] = atoi(starting_bet);
    return data;
}

int win_or_loss() {
    int number = rand() & 1;
    return number;
}

float score(int starting_amount, int starting_bet) {
    float total = starting_amount / starting_bet;
    int maximum_money = total;
    while (1) {
        int current_bet_amount = 1;
        while (!win_or_loss()) {
            total -= current_bet_amount;
            if (total < 0) {
                return maximum_money * starting_bet;
            }
            current_bet_amount *= 2;
        }
        total += current_bet_amount;
        maximum_money = total;
    }
}

float run_many_times(int times_to_run, int starting_amount, int starting_bet) {
    int i;
    unsigned long long int total = 0;
    for (i = 0; i < times_to_run; i++) {
        total += score(starting_amount, starting_bet);
    }
    return (total / times_to_run);
}