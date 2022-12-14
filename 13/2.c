#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

typedef struct list {
    struct intlistitem* l;
    int len;
} list;

typedef union intlist {
    int num;
    struct list l;
} intlist;

typedef struct intlistitem {
    union intlist value;
    int islist;
} intlistitem;


list parse(char* string) {
    int i = 0;
    list l = *(list*)malloc(sizeof(list));
    l.l = (intlistitem*)malloc(0);
    l.len = 0;
    while(string[i] !='\0') {
        if(string[i] == ',') {
            ++i;
            continue;
        }
        if(string[i] == '[') {
            char buf[1000] = "";
            clear(buf);
            int j = 0;
            int depth = 1;
            ++i;
            while(depth > 0) {
                if(string[i] == '[') {
                    ++depth;
                }
                if (string[i] == ']') {
                    --depth;
                    if (depth == 0) {
                        break;
                    }
                }
                buf[j++] = string[i++];
            }
            list new = parse(buf);
            intlist item;
            item.l = new;
            l.l = (intlistitem*)realloc(l.l, (l.len+1) * sizeof(intlistitem));
            l.l[l.len].islist = 1;
            l.l[l.len].value = item;
            l.len++;
        } else {
            char buf[1000] = "";
            clear(buf);
            int j = 0;
            while(string[i] != ',' && string[i] != '\0') {
                buf[j++] = string[i++];
            }
            intlist item;
            item.num = atoi(buf);
            l.l = (intlistitem*)realloc(l.l, (l.len+1) * sizeof(intlistitem));
            l.l[l.len].islist = 0;
            l.l[l.len].value = item;
            l.len++;
        }
        ++i;
    }
    return l;
}

void print(list l) {
    for(int i = 0; i < l.len; ++i) {
        if(l.l[i].islist) {
            printf("[");
            print(l.l[i].value.l);
            printf("]");
        } else {
            printf("%d", l.l[i].value.num);
        }
        if(i != l.len - 1) {
            printf(", ");
        }
    }
}

int compare(list a, list b) {
    int i = 0;
    while(i < a.len && i < b.len) {
        if(a.l[i].islist && b.l[i].islist) {
            int result = compare(a.l[i].value.l, b.l[i].value.l);
            if (result == 1) {
                return 1;
            }
            if(result == 0) {
                return 0;
            }
        } else if(!a.l[i].islist && !b.l[i].islist) {
            if(a.l[i].value.num < b.l[i].value.num) {
                return 1;
            } else if(a.l[i].value.num > b.l[i].value.num) {
                return 0;
            }
        } else if(a.l[i].islist && !b.l[i].islist) {
            list l;
            l.l = (intlistitem*)malloc(sizeof(intlistitem));
            l.len = 1;
            l.l[0] = b.l[i];
            int result = compare(a.l[i].value.l, l);
            if (result == 1) {
                return 1;
            }
            if(result == 0) {
                return 0;
            }
        } else if(!a.l[i].islist && b.l[i].islist) {
            list l;
            l.l = (intlistitem*)malloc(sizeof(intlistitem));
            l.len = 1;
            l.l[0] = a.l[i];
            int result = compare(l, b.l[i].value.l);
            if (result == 1) {
                return 1;
            }
            if(result == 0) {
                return 0;
            }
        }
        ++i;
    }
    if(i < a.len) {
        return 0;
    }
    if(i < b.len) {
        return 1;
    }
    return -1;

}

int main() {
    char input[1000] = "";
    gets(input);
    int i = 1;
    int total = 1;
    list* lists = (list*)malloc(0);
    int len = 0;
    while(input[0] != '\0') {
        list l1 = parse(input);
        clear(input);
        gets(input);
        list l2 = parse(input);
        clear(input);
        gets(input);
        lists = (list*)realloc(lists, sizeof(list) * (len+2));
        lists[len] = l1;
        lists[len+1] = l2;
        len += 2;
        gets(input);
    }

    list l1 = parse("[[2]]");
    list l2 = parse("[[6]]");
    lists = (list*)realloc(lists, sizeof(list) * (len+2));
    lists[len] = l1;
    lists[len+1] = l2;
    len += 2;

    for(int i = 0; i < len; ++i) {
        for(int j = 0; j < len-1; ++j) {
            if(compare(lists[j], lists[j+1]) == 0) {
                list l = lists[j];
                lists[j] = lists[j+1];
                lists[j+1] = l;
            }
        }
    }

    for(int i = 0; i < len; ++i) {
        if(compare(parse("[[2]]"), lists[i]) == -1) {
            total *= (i+1);
        }
        if(compare(parse("[[6]]"), lists[i]) == -1) {
            total *= (i+1);
        }
    }

    printf("%d\n", total);
 

    
}