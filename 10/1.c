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
    int cycle = 1;
    int total = 0;

    while(input[0] != '\0') {
        if(input[0] == 'n') {
            if(cycle % 40 == 20) {
                total += cycle * x;
            }
            ++cycle;
        } else {
            if(cycle % 40 == 20) {
                total += cycle * x;
            }
            ++cycle;
            if(cycle % 40 == 20) {
                total += cycle * x;
            }
            ++cycle;
            x += atoi(input + 5);
        }

        clear(input);
        gets(input);
    }
    printf("%d\n", total);
}