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

int len(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        ++i;
    }
    return i;
}

int main() {
    char input[1000] = "";
    int** grid = NULL;
    int numLines = 0;
    int lineLen = 0;

    gets(input);
    lineLen = len(input);
    while (input[0] != '\0') {
        int* gridLine = calloc(lineLen, sizeof(int));
        char buf[2] = "";
        for(int i = 0; i < lineLen; ++i) {
            buf[0] = input[i];
            gridLine[i] = atoi(buf);
        }
        grid = realloc(grid, (numLines+1) * sizeof(int*));
        grid[numLines] = gridLine;
        numLines++;
        clear(input);
        gets(input);
    }

    int max = 0;

    for(int y = 0; y < numLines; ++y) {
        for(int x = 0; x < lineLen; ++x) {
            int size = grid[y][x];
            int d;
            int score = 1;
            if((x == lineLen-1) || (x == 0) || (y == numLines-1) || (y == 0)) {
                continue;
            }
            //+x
            for(d = 1; x+d < lineLen-1; ++d) {
                if(grid[y][x+d] >= size){
                    break;
                }
            }
            score *= d;
            //-x
            for(d = -1; x+d > 0; --d) {
                if(grid[y][x+d] >= size){
                    break;
                }
            }
            score *= d;
            //+y
            for(d = 1; y+d < numLines-1; ++d) {
                if(grid[y+d][x] >= size){
                    break;
                }
            }
            score *= d;
            //-y
            for(d = -1; y+d > 0; --d) {
                if(grid[y+d][x] >= size){
                    break;
                }
            }
            score *= d;
            if (score > max)
                max = score;
        }
    }

    printf("%d\n", max);
    
}