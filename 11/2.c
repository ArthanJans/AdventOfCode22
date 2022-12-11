#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct monkey{
    unsigned long long int* items;
    int numItems;
    char* operation;
    int divisible;
    int t;
    int f;
} monkey;

void push(unsigned long long int** items, int len, unsigned long long int item) {
    *items = realloc(*items, sizeof(unsigned long long int) * (len+1));
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

unsigned long long int operation(char* op, unsigned long long int old) {
    unsigned long long int ret = old;
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
                unsigned long long int* items = malloc(0);
                int monkeyItemsLen = 0;
                int i = 18;
                while(input[i] != '\0') {
                    if(input[i] != ',') {
                        buf[j++] = input[i];
                    } else {
                        push(&items, monkeyItemsLen++, atol(buf));
                        clear(buf);
                        j = 0;
                        ++i;
                    }
                    ++i;
                }
                push(&items, monkeyItemsLen++, atol(buf));
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
    unsigned long long int* inspections = calloc(sizeof(unsigned long long int), numMonkeys);
    for(int i = 0; i < numMonkeys; ++i) {
        inspections[i] = 0;
    }

    int commonDivisor = monkeys[0]->divisible;
    while(1) {
        for(int i = 0; i < numMonkeys; ++i) {
            if(commonDivisor % monkeys[i]->divisible != 0) {
                goto repeat;
            }
        }
        break;
        repeat:
        commonDivisor += monkeys[0]->divisible;
    }

    for(int i = 0; i < 10000; ++i) {
        for(int j = 0; j < numMonkeys; ++j) {
            for(int k = 0; k < monkeys[j]->numItems; ++k) {
                // printf("monkey %d has item %d ", j, monkeys[j]->items[k]);
                inspections[j]++;
                monkeys[j]->items[k] = operation(monkeys[j]->operation, monkeys[j]->items[k]);
                // printf("after op %d ", monkeys[j]->items[k]);
                monkeys[j]->items[k] = monkeys[j]->items[k] % commonDivisor;
                if(monkeys[j]->items[k] % monkeys[j]->divisible == 0) {
                    push(&monkeys[monkeys[j]->t]->items, monkeys[monkeys[j]->t]->numItems++, monkeys[j]->items[k]);
                    // printf("sent to monkey %d\n", monkeys[j]->t);
                } else {
                    push(&monkeys[monkeys[j]->f]->items, monkeys[monkeys[j]->f]->numItems++, monkeys[j]->items[k]);
                    // printf("sent to monkey %d\n", monkeys[j]->f);
                }
            }
            free(monkeys[j]->items);
            monkeys[j]->items = malloc(0);
            monkeys[j]->numItems = 0;
        }
    }

    for(int i = 0; i < numMonkeys; ++i) {
        printf("%d\n", inspections[i]);
    }

    unsigned long long int m1 = 0;
    unsigned long long int m2 = 0;
    for(int i = 0; i < numMonkeys; ++i) {
        if (inspections[i] > m1) {
            m2 = m1;
            m1 = inspections[i];
        } else if(inspections[i] > m2) {
            m2 = inspections[i];
        }
    }

    printf("%llu\n%llu\n%llu\n", m1, m2, m1*m2);

}