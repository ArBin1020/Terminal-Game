#include <stdio.h>
#include <string.h>
#include "core_ui.h"

void clear_screen() {
    printf("\033[H\033[2J");
}

void draw_line(int width) {
    printf("+");
    for (int i = 0; i < width-2; i++) printf("-");
    printf("+\n");
}

void draw_content(int width, const char *label, const char *text) {
    int used = strlen(label) + 2 + strlen(text);
    int space = width - 2 - used;
    if(space < 0) space = 0;
    if (strcmp(label, "") == 0) {
        printf("|%s", text);
    } else {
        printf("|%s: %s", label, text);
    }
    for (int i = 0; i < space; i++) printf(" ");
    printf("|\n");
}
