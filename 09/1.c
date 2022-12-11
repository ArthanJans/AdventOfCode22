#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct coord{
    int x;
    int y;
} coord;

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

int len(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        ++i;
    }
    return i;
}

int isAdjacent(coord* h, coord* t) {
    return (abs(h->x-t->x) <= 1 && abs(h->y-t->y) <=1);
}

int addVisited(coord*** list, int len, coord* pos) {
    for(int i = 0; i < len; ++i) {
        if ((*list)[i]->x == pos->x && (*list)[i]->y == pos->y) {
            return len;
        }
    }
    *list = realloc(*list, (len+1) * sizeof(coord*));
    (*list)[len] = pos;
    return len +1;
} 

int main() {
    char input[6] = "";
    coord* h = malloc(sizeof(coord));
    h->x = 0;
    h->y = 0;
    coord* t = malloc(sizeof(coord));
    t->x = 0;
    t->y = 0;
    coord** visited = malloc(0);
    int len = 0;
    len = addVisited(&visited, len, t);
    gets(input);
    while (input[0] != '\0') {
        char buf[4] = "";
        strcpy(buf, input+2);
        int n = atoi(buf);
        for(; n > 0; --n){
            coord* prev = malloc(sizeof(coord));
            prev->x = h->x;
            prev->y = h->y;
            switch(input[0]){
                case 'U':
                    h->y--;
                    break;
                case 'D':
                    h->y++;
                    break;
                case 'R':
                    h->x++;
                    break;
                case 'L':
                    h->x--;
            }
            if (!isAdjacent(h, t)) {
                t = prev;
                len = addVisited(&visited, len, t);
            }
        }

        clear(input);
        gets(input);
    }

    printf("%d\n", len);
    
}