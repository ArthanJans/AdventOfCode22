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
    coord* segments[10];
    for(int i = 0; i < 10; ++i){
        coord* seg = malloc(sizeof(coord));
        seg->x = 0;
        seg->y = 0;
        segments[i] = seg;
    }
    coord** visited = malloc(0);
    int len = 0;
    len = addVisited(&visited, len, segments[9]);
    gets(input);
    while (input[0] != '\0') {
        char buf[4] = "";
        strcpy(buf, input+2);
        int n = atoi(buf);
        for(; n > 0; --n){
            switch(input[0]){
                case 'U':
                    segments[0]->y--;
                    break;
                case 'D':
                    segments[0]->y++;
                    break;
                case 'R':
                    segments[0]->x++;
                    break;
                case 'L':
                    segments[0]->x--;
            }
            for(int i = 0; i < 9; ++i) {
                if (!isAdjacent(segments[i], segments[i+1])) {
                    coord* new = malloc(sizeof(coord));
                    new->x = segments[i+1]->x;
                    new->y = segments[i+1]->y;
                    segments[i+1] =  new;
                    if (segments[i+1]->y < segments[i]->y) {
                        ++segments[i+1]->y;
                    } else if (segments[i+1]->y > segments[i]->y) {
                        --segments[i+1]->y;
                    }
                    if (segments[i+1]->x < segments[i]->x) {
                        ++segments[i+1]->x;
                    } else if(segments[i+1]->x > segments[i]->x) {
                        --segments[i+1]->x;
                    }
                    if (i == 8) {
                        len = addVisited(&visited, len, segments[9]);
                    }
                } else {
                    break;
                }
            }
        }

        clear(input);
        gets(input);
    }

    printf("%d\n", len);
    
}