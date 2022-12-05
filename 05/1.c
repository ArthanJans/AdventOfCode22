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

void push(char** list, int size, char item) {
    *list = realloc(*list, (size+1) * sizeof(char));
    (*list)[size] = item;
}

char pop(char** list, int size) {
    char item = (*list)[size - 1];
    *list = realloc(*list, (size-1) * sizeof(char));
    return item;
}

int main() {
    
    char input[1000];
    gets(input);
    
    char* stacks[9] = {malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0)};
    int lens[9] = {0};
    char* temps[9] = {malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0),malloc(0)};
    int templens[9] = {0};
    
    while(input[0] != '\0') {
        if(input[1] != '1') {
            for(int i = 0; i < 9; ++i) {
                char c = input[(i)*4 + 1];
                if(c != ' ') {
                    push(&temps[i], templens[i], c);
                    ++templens[i];
                }
            }
        }

        clear(input);
        gets(input);
    }
    for (int i = 0; i < 9; ++i) {
        while (templens[i] > 0) {
            push(&stacks[i], lens[i], pop(&temps[i], templens[i]));
            --templens[i];
            ++lens[i];
        }
    }
    clear(input);
    gets(input);
    int bufi = 0;
    char buf[5];
    int x = 0;
    while(input[0] != '\0') {
        int i = 0;
        int move;
        int from;
        int to;
        
        // read "move "
        while(input[i] != ' ') {
            ++i;
        }
        ++i;
        while(input[i] != ' ') {
            buf[bufi++] = input[i++];
        }
        ++i;
        move = atoi(buf);
        clear(buf);
        bufi = 0;
        // read "from "
        while(input[i] != ' ') {
            ++i;
        }
        ++i;
        while(input[i] != ' ') {
            buf[bufi++] = input[i++];
        }
        ++i;
        from = atoi(buf);
        clear(buf);
        bufi = 0;
        // read "to "
        while(input[i] != ' ') {
            ++i;
        }
        ++i;
        while(input[i] != '\0') {
            buf[bufi++] = input[i++];
        }
        ++i;
        to = atoi(buf);
        clear(buf);
        bufi = 0;
        for(; move > 0; --move) {
            push(&stacks[to-1], lens[to-1]++, pop(&stacks[from-1], lens[from-1]--));
        }
        clear(input);
        gets(input);
    }

    for(int i = 0; i < 9; ++i) {
        printf("%c", pop(&stacks[i], lens[i]));
    }
    printf("\n");

    return 1;
}