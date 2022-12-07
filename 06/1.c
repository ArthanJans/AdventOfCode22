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

    char buf[5] = {input[0], input[1], input[2], input[3], 0};
    int pos = 4;
    while (!difChars(buf)) {
        buf[0] = buf[1];
        buf[1] = buf[2];
        buf[2] = buf[3];
        buf[3] = input[pos];
        ++pos;
    }
    
    printf("%d\n", pos);

    return 0;
}