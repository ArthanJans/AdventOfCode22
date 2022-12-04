#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_LINES = 2254;

int main() {
    char input[10000];

    gets(input);
    int a = 0;
    int b = 0;
    int c = 0;
    int this = 0;
    for(int j = 0; j < NUM_LINES; ++j) {
        if (input[0] != '\0') {
            this += atoi(input);
        } else {
            if (this > a) {
                c = b;
                b = a;
                a = this;
            } else if(this > b) {
                c = b;
                b = this;
            } else if(this > c) {
                c = this;
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
    printf("%d\n", a+b+c);
    return 0;
}