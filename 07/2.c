#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    struct node* parent;
    struct node** children;
    int numChildren;
    char* name;
    int size;
} node;

void addChild(node* parent, node* child) {
    parent->children = realloc(parent->children, (parent->numChildren + 1) * sizeof(node*));
    parent->children[parent->numChildren] = child;
    parent->numChildren++;
}

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

node* createNode(node* parent, char* name, int size) {
    node* new = malloc(sizeof(node));
    new->parent = parent;
    new->name = name;
    new->size = size;
    new->children = malloc(0);
    new->numChildren = 0;
    return new;
}

void printNode(node* n) {
    printf("%s->[", n->name);
    for(int i = 0; i < n->numChildren; ++i) {
        printNode(n->children[i]);
        if(i < n->numChildren-1) {
            printf(", ");
        }
    }
    printf("]");
}

int findSmallestBiggerThan(node* root, int biggerThan) {
    int smallest = root->size;
    if (smallest <= biggerThan) {
        return 0;
    }
    for(int i = 0; i < root->numChildren; ++i) {
        int newSmallest = findSmallestBiggerThan(root->children[i], biggerThan);
        if(newSmallest >= biggerThan && newSmallest < smallest)
            smallest = newSmallest;
    }
    return smallest;
}

int main() {

    node root = (node){NULL, malloc(0), 0, "/", 0}; 
    char input[1000];
    gets(input);

    node* current = &root;
    while(input[0] != '\0') {
        if(input[2] == 'l') {
            clear(input);
            gets(input);
            while(input[0] != '$' && input[0] != '\0') {
                int size = 0;
                int i = 0;
                if (input[0] != 'd') {
                    char buf[100] = "";
                    while(input[i] != ' ') {
                        buf[i] = input[i];
                        ++i;
                    }
                    size = atoi(buf);
                    clear(buf);
                } else {
                    i = 3;
                }
                ++i;
                char* name = malloc(100 * sizeof(char));
                strcpy(name, input + i);
                node* child = createNode(current, name, size);
                addChild(current, child);
                clear(input);
                gets(input);
            }
        } else if(input[2] == 'c') {
            if(input[5] == '/') {
                current = &root;
            } else if(input[5] == '.' && input[6] == '.') {
                int size = 0;
                for(int i = 0; i < current->numChildren; ++i) {
                    size += current->children[i]->size;
                }
                current->size = size;
                current = current->parent;
            } else {
                char* name = input + 5;
                for(int i = 0; i < current->numChildren; ++i) {
                    if (strcmp(current->children[i]->name, name) == 0) {
                        current = current->children[i];
                        break;
                    }
                }
            }
            clear(input);
            gets(input);
        }
    }
    while(current != NULL) {
        int size = 0;
        for(int i = 0; i < current->numChildren; ++i) {
            size += current->children[i]->size;
        }
        current->size = size;
        current = current->parent;
    }
    int needed = root.size - 40000000;

    printf("%d\n", findSmallestBiggerThan(&root, needed));

    return 0;
}