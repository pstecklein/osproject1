#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *ere;

int main(int argc, char* argv[]) {
    int loc;
    int hidden;
    int arr[5] = {};
    for (int i = 0; i < 5; i++) {
        arr[i] = (int)(rand() % 3000);
    }
    ere = fopen("input.txt", "w");
    for (int i = 0; i < 3000; i++) {
        hidden = 0;
        loc = 0;
        for (int j = 0; j < 5; j++) {
            if (i == arr[j]) {
                hidden = 1;
                loc = j;
            }
        }
        if (hidden) {
            fprintf(ere, "%d\n", arr[loc]);
        } else {
            fprintf(ere, "%d\n", abs(rand()));
        }
    }
    return 0;
}