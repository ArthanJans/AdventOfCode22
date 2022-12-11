#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

int main() {
    char input[10] = "";
    gets(input);

    int x = 1;
    int cycle = 0;

    while(input[0] != '\0') {
        if(input[0] == 'n') {
            if(abs((cycle%40) - x) <= 1) {
                printf("#");
            } else {
                printf(".");
            }
            if(cycle%40 == 39) {
                printf("\n");
            }
            ++cycle;
        } else {
            if(abs((cycle%40) - x) <= 1) {
                printf("#");
            } else {
                printf(".");
            }
            if(cycle%40 == 39) {
                printf("\n");
            }
            ++cycle;
            if(abs((cycle%40) - x) <= 1) {
                printf("#");
            } else {
                printf(".");
            }
            if(cycle%40 == 39) {
                printf("\n");
            }
            ++cycle;
            x += atoi(input + 5);
        }

        clear(input);
        gets(input);
    }
}