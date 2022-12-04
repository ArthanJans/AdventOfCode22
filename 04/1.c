#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NUM_LINES = 1000;

void clear(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = '\0';
        ++i;
    }
}

int main() {
    char input[15];

    gets(input);
    int total = 0;
    for(; NUM_LINES > 0; --NUM_LINES) {
        int nums[4] = {0};
        int i = 0;
        int x = 0;
        char buf[3] = {0};
        int j = 0;
        while(input[i] != '\0') {
            if (input[i] == '-' || input[i] == ',') {
                nums[j] = atoi(buf);
                ++j;
                clear(buf);
                x = 0;
            } else {
                buf[x] = input[i];
                ++x;
            }
            ++i;
        }
        nums[j] = atoi(buf);
        if ((nums[0] <= nums[2] && nums[1] >= nums[3]) || (nums[2] <= nums[0] && nums[3] >= nums[1])) {
            ++total;
        }
        clear(input);
        gets(input);
    }
    printf("%d\n", total);
    return 0;
}