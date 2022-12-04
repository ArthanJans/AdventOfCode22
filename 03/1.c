#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_LINES = 300;

int len(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

int priority(char c) {
    if (c >= 'a') {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int main() {
    char input[100];

    gets(input);
    int total = 0;
    for(; NUM_LINES > 0; --NUM_LINES) {
        int l = len(input);
        int compl = l/2;
        char *first = input;
        char *second = input + (compl);
        for (int i = 0; i < compl; ++i) {
            for (int j =0; j<compl; ++j) {
                if (first[i] == second[j]) {
                    total += priority(first[i]);
                    goto endloop;
                }
            }
        }


        endloop:
        clear(input);
        gets(input);
    }
    printf("%d\n", total);
    return 0;
}