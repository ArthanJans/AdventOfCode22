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
    char a[100];
    char b[100];
    char c[100];

    gets(a);
    gets(b);
    gets(c);
    int total = 0;
    for(; NUM_LINES > 0; NUM_LINES -=3) {
        for(int x = 0; x < len(a); ++x) {
            for(int y = 0; y < len(b); ++y) {
                if (a[x] == b[y]) {
                    for(int z = 0; z < len(c); ++z) {
                        if (c[z] == b[y]) {
                            total += priority(a[x]);
                            goto endloop;
                        }
                    }
                }
            }
        }


        endloop:
        clear(a);
        gets(a);
        
        clear(b);
        gets(b);
        
        clear(c);
        gets(c);
    }
    printf("%d\n", total);
    return 0;
}