#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_LINES = 2254;

int main() {
    char input[10000];

    gets(input);
    int max = 0;
    int this = 0;
    for(int j = 0; j < NUM_LINES; ++j) {
        if (input[0] != '\0') {
            this += atoi(input);
        } else {
            if (this > max) {
                max = this;
            }
            this = 0;
            int i = 0;
            while(input[i] != '\0') {
                input[i] = '\0';
                ++i;
            }
        }
        gets(input);
    }
    printf("%d\n", max);
    return 0;
}