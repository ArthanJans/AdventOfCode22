#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_LINES = 2501;

int main() {
    char input[4];

    gets(input);
    int total = 0;
    for(; NUM_LINES > 1; --NUM_LINES) {
        if(input[2] == 'X') {
            total += 0;
            if(input[0] == 'A') {
                total += 3;
            }
            if(input[0] == 'B') {
                total += 1;
            }
            if(input[0] == 'C') {
                total += 2;
            }
        }
        if(input[2] == 'Y') {
            total += 3;
            if(input[0] == 'A') {
                total += 1;
            }
            if(input[0] == 'B') {
                total += 2;
            }
            if(input[0] == 'C') {
                total += 3;
            }
        }
        if(input[2] == 'Z') {
            total += 6;
            if(input[0] == 'A') {
                total += 2;
            }
            if(input[0] == 'B') {
                total += 3;
            }
            if(input[0] == 'C') {
                total += 1;
            }
        }
        gets(input);
    }
    printf("%d\n", total);
    return 0;
}