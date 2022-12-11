#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct monkey{
    int* items;
    int numItems;
    char* operation;
    int divisible;
    int t;
    int f;
} monkey;

void push(int** items, int len, int item) {
    *items = realloc(*items, sizeof(int) * (len+1));
    (*items)[len] = item;
}

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

void addMonkey(monkey*** monkeys, int len, monkey* add) {
    *monkeys = realloc(*monkeys, sizeof(monkey*) * (len+1));
    (*monkeys)[len] = add;
}

int operation(char* op, int old) {
    int ret = old;
    if(op[0] == '+') {
        if(op[2] == 'o') {
            ret += old;
        } else {
            ret += atoi(op + 2);
        }
    } else {
        if(op[2] == 'o') {
            ret *= old;
        } else {
            ret *= atoi(op + 2);
        }
    }
    return ret;
}

int main() {
    char input[1000] = "";
    gets(input);

    monkey** monkeys = malloc(0);
    int numMonkeys = 0;
    monkey* temp;
    while(input[0] != '\0'){
        while(input[0] != '\0'){
            if(input[0] == 'M') {
                temp = malloc(sizeof(monkey));
            } else if(input[2] == 'S') {
                char buf[5] = "";
                int j = 0;
                int* items = malloc(0);
                int monkeyItemsLen = 0;
                int i = 18;
                while(input[i] != '\0') {
                    if(input[i] != ',') {
                        buf[j++] = input[i];
                    } else {
                        push(&items, monkeyItemsLen++, atoi(buf));
                        clear(buf);
                        j = 0;
                        ++i;
                    }
                    ++i;
                }
                push(&items, monkeyItemsLen++, atoi(buf));
                temp->items = items;
                temp->numItems = monkeyItemsLen;
            } else if(input[2] == 'O') {
                char* buf = calloc(sizeof(char), 20);
                strcpy(buf, input + 23);
                temp->operation = buf;
            } else if(input[2] == 'T') {
                temp->divisible = atoi(input + 21);
            } else if(input[7] == 't') {
                temp->t = atoi(input + 29);
            } else if(input[7] == 'f') {
                temp->f = atoi(input + 30);
            }
            clear(input);
            gets(input);
        }
        addMonkey(&monkeys, numMonkeys++, temp);
        clear(input);
        gets(input);
    }
    int* inspections = calloc(sizeof(int), numMonkeys);
    for(int i = 0; i < numMonkeys; ++i) {
        inspections[i] = 0;
    }

    for(int i = 0; i < 20; ++i) {
        for(int j = 0; j < numMonkeys; ++j) {
            for(int k = 0; k < monkeys[j]->numItems; ++k) {
                inspections[j]++;
                monkeys[j]->items[k] = operation(monkeys[j]->operation, monkeys[j]->items[k]);
                monkeys[j]->items[k] = floor(monkeys[j]->items[k] / 3.0f);
                if(monkeys[j]->items[k] % monkeys[j]->divisible == 0) {
                    push(&monkeys[monkeys[j]->t]->items, monkeys[monkeys[j]->t]->numItems++, monkeys[j]->items[k]);
                } else {
                    push(&monkeys[monkeys[j]->f]->items, monkeys[monkeys[j]->f]->numItems++, monkeys[j]->items[k]);
                }
            }
            free(monkeys[j]->items);
            monkeys[j]->items = malloc(0);
            monkeys[j]->numItems = 0;
        }
    }

    int m1 = 0;
    int m2 = 0;
    for(int i = 0; i < numMonkeys; ++i) {
        if (inspections[i] > m1) {
            m2 = m1;
            m1 = inspections[i];
        } else if(inspections[i] > m2) {
            m2 = inspections[i];
        }
    }

    printf("%d\n", m1*m2);
    printf("%d\n", 89/10);

}