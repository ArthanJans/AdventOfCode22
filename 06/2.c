#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int difChars(char *chars) {
    int i = 0;
    while(chars[i] != '\0') {
        int j = i+1;
        while(chars[j] != '\0') {
            if (chars[i] == chars[j])
                return 0;
            ++j;
        }
        ++i;
    }
    return 1;
    
}

int main() {
    
    char input[10000];
    gets(input);

    char buf[15] = {0};
    for(int i = 0; i < 14; ++i) {
        buf[i] = input[i];
    }
    int pos = 14;
    while (!difChars(buf)) {
        for(int i = 0; i < 13; ++i) {
            buf[i] = buf[i+1];
        }
        buf[13] = input[pos];
        ++pos;
    }
    
    printf("%d\n", pos);

    return 0;
}