#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct pos{
    int x;
    int y;
} pos;

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

int get(pos* positions, int* values, int len, pos position, int def) {
    for(int i = 0; i < len; ++i) {
        if(positions[i].x == position.x && positions[i].y == position.y) {
            return values[i];
        }
    }
    return def;
}

pos getPos(pos* positions, pos* values, int len, pos position) {
    for(int i = 0; i < len; ++i) {
        if(positions[i].x == position.x && positions[i].y == position.y) {
            return values[i];
        }
    }
    return position;
}

int add(pos** positions, int** values, int len, pos position, int value) {
    for(int i = 0; i < len; ++i) {
        if((*positions)[i].x == position.x && (*positions)[i].y == position.y) {
            (*values)[i] = value;
            return len;
        }
    }
    (*positions) = realloc((*positions), sizeof(pos) * (len+1));
    (*values) = realloc(*values, sizeof(int) * (len + 1));
    (*positions)[len] = position;
    (*values)[len] = value;
    return len + 1;
}

int addPos(pos** positions, pos** values, int len, pos position, pos value) {
    for(int i = 0; i < len; ++i) {
        if((*positions)[i].x == position.x && (*positions)[i].y == position.y) {
            (*values)[i] = value;
            return len;
        }
    }
    (*positions) = realloc((*positions), sizeof(pos) * (len+1));
    (*values) = realloc(*values, sizeof(pos) * (len + 1));
    (*positions)[len] = position;
    (*values)[len] = value;
    return len + 1;
}

void drop(pos* positions, int len, pos position) {
    int i = 0;
    int found = 0;
    while(i < len) {
        if(!found) {
            if (positions[i].x == position.x && positions[i].y == position.y) {
                found = 1;
            }
        } else {
            positions[i-1] = positions[i];
        }
        ++i;
    }
}

int main() {
    char input[1000] = "";
    gets(input);

    char** grid = malloc(0);
    int numRows = 0;
    int numCols = 0;

    pos* position = malloc(sizeof(pos));
    pos* goal = malloc(sizeof(pos));

    while(input[0] != '\0') {
        char *row = malloc(0);
        numCols = 0;
        int i = 0;
        while(input[i] != '\0') {
            row = realloc(row, sizeof(char) * (numCols + 1));
            row[numCols] = input[i];
            if (input[i] == 'S') {
                row[numCols] = 'a';
                position->x = numCols;
                position->y = numRows;
            }
            if (input[i] == 'E') {
                row[numCols] = 'z';
                goal->x = numCols;
                goal->y = numRows;
            }
            ++numCols;
            ++i;
        }
        grid = realloc(grid, (numRows + 1) * sizeof(char*));
        grid[numRows] = row;
        ++numRows;
        clear(input);
        gets(input);
    }
    int lowest = INT_MAX;
    int points = 0;
    for(int xa = 0; xa < numCols; ++xa) {
        for(int ya = 0; ya < numRows; ++ya) {
            if (grid[ya][xa] != 'a') {
                continue;
            }
            points ++;
        }
    }
    printf("%d\n", points);
    for(int xa = 0; xa < numCols; ++xa) {
        for(int ya = 0; ya < numRows; ++ya) {
            if (grid[ya][xa] != 'a') {
                continue;
            }
            printf("remaining: %d\n", points--);
            position->x = xa;
            position->y = ya;
            pos* openSet = malloc(sizeof(pos));
            int openSetLen = 1;
            openSet[0].x = position->x;
            openSet[0].y = position->y;

            pos* cameFrom = malloc(0);
            pos* cameFromVals = malloc(0);
            int cameFromLen = 0;

            pos* gScore = malloc(sizeof(pos));
            int* gScoreVals = malloc(sizeof(int));
            int gScoreLen = 1;
            gScore[0].x = position->x;
            gScore[0].y = position->y;
            gScoreVals[0] = 0;

            pos* fScore = malloc(sizeof(pos));
            int* fScoreVals = malloc(sizeof(int));
            int fScoreLen = 1;
            fScore[0].x = position->x;
            fScore[0].y = position->y;
            fScoreVals[0] = abs(goal->x - position->x) + abs(goal->y - position->y);
            int steps = INT_MAX;
            
            while(openSetLen != 0) {
            
                pos current = (pos){0, 0};
                int lowest = INT_MAX;
                for(int i = 0; i < openSetLen; ++i) {
                    int val = get(fScore, fScoreVals, fScoreLen, openSet[i], INT_MAX);
                    if (val < lowest) {
                        lowest = val;
                        current = openSet[i];
                    }
                }
                if(current.x == goal->x && current.y == goal->y) {
                    steps = 0;
                    while(current.x != position->x || current.y != position->y) {
                        current = getPos(cameFrom, cameFromVals, cameFromLen, current);
                        ++steps;
                    }
                    break;
                }
                drop(openSet, openSetLen--, current);
                for(int i = 0; i < 4; ++i) {
                    pos neighbour = (pos){current.x, current.y};
                    if(i == 0) {
                        neighbour.x--;
                    }
                    if(i == 1){
                        neighbour.x++;
                    }
                    if(i == 2){
                        neighbour.y--;
                    }
                    if(i == 3) {
                        neighbour.y++;
                    }
                    if(neighbour.x < 0 || neighbour.y < 0 || neighbour.x >= numCols || neighbour.y >= numRows || grid[neighbour.y][neighbour.x] - grid[current.y][current.x] > 1) {
                        continue;
                    }
                    int tentative_gScore = get(gScore, gScoreVals, gScoreLen, current, INT_MAX) + 1;
                    if(tentative_gScore < get(gScore, gScoreVals, gScoreLen, neighbour, INT_MAX)) {
                        cameFromLen = addPos(&cameFrom, &cameFromVals, cameFromLen, neighbour, current);
                        gScoreLen = add(&gScore, &gScoreVals, gScoreLen, neighbour, tentative_gScore);
                        fScoreLen = add(&fScore, &fScoreVals, fScoreLen, neighbour, tentative_gScore + abs(goal->x - neighbour.x) + abs(goal->y - neighbour.y));
                        for(int j = 0; j < openSetLen; ++j) {
                            if (openSet[j].x == neighbour.x && openSet[j].y == neighbour.y) {
                                goto added;
                            }
                        }
                        openSet = realloc(openSet, sizeof(pos) * (openSetLen + 1));
                        openSet[openSetLen] = neighbour;
                        openSetLen++;
                        added:
                        
                    } 
                }

            }
            if (steps < lowest) {
                lowest = steps;
            }
        
        }
    }

    printf("%d\n", lowest);




}