#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include "core_ui.h"
#include "core_input.h"
#include "init_info.h"

void print_logo_from_file() {
    FILE *fp = fopen("assets/welcome.txt", "r");
    if (fp) {
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), fp)) {
            printf("%s", buffer);
        }
        fclose(fp);
    } else {
        printf("ArBin Game System\n"); 
    }
    printf("\n");
}

int show_welcome_message() {
    struct winsize ws;
    int width = 50;
    
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        if (ws.ws_col < width) {
            printf("Your screen is too small.\n");
            exit(0);
        }
    }
    
    clear_screen();
    print_logo_from_file();
    
    draw_line(width);
    draw_content(width, "Author", "ArBin");
    draw_content(width, "Version", "0.1.0");
    draw_line(width);
    draw_content(width, "Release Info", "This is first release");
    draw_content(width, "", "now only support Sudoku game.");
    draw_line(width);
    draw_content(width, "[Arrow Keys]", "Move Cursor");
    draw_content(width, "[1-9]", "       Input Number");
    draw_content(width, "[0/Del]", "     Erase Number");
    draw_content(width, "[q]", "         Quit Game");
    draw_line(width);
    
    printf("\nPress any key to start...\n");
    enableRawMode();
    readKey();
    disableRawMode();
    return 0;
}