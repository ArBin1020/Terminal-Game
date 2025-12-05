#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "../../include/common.h"
#include "../../include/core_input.h"
#include "../../include/core_ui.h"
#include "../../include/game_sudoku.h"

static int grid[9][9];
static int original[9][9];
static int solution[9][9];
static int cursor_r = 0;
static int cursor_c = 0;


static bool is_safe(int r, int c, int num) {
    for (int x = 0; x < 9; x++) {
        if (grid[r][x] == num) return false;
        if (grid[x][c] == num) return false;
    }
    int start_c = c - c % 3;
    int start_r = r - r % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[start_r + i][start_c + j] == num) return false;
        }
    }
    return true;
}

static bool fill_puzzle() {
    int row = -1, col = -1;
    bool isEmpty = false;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = true;
                goto fill;
            }
        }
    }
fill:
    if (!isEmpty) return true;

    for (int n = 1; n <= 9; n++){
        if (is_safe(row, col, n)) {
            grid[row][col] = n;
            if (fill_puzzle()) return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

static void dig_puzzle() {
    int attempts = 40;
    while (attempts > 0) {
        int r = rand() % 9;
        int c = rand() % 9;
        if (grid[r][c] != 0) {
            grid[r][c] = 0;
            attempts--;
        }
    }
}

static void generate_puzzle() {
    srand(time(0));
    for (int i = 0; i < 9; i++) 
        for (int j = 0; j < 9; j++) grid[i][j] = 0;

    for (int k = 0; k < 9; k += 3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int num;
                do { num = rand() % 9 + 1; } while(!is_safe(k+i, k+j, num));
                grid[k+i][k+j] = num;
            }
        }
    }
    
    fill_puzzle();
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) solution[i][j] = grid[i][j];

    dig_puzzle();
    for(int i=0; i<9; i++) 
        for(int j=0; j<9; j++) original[i][j] = grid[i][j];
}

static bool is_complete() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) return false;
            if (grid[i][j] != solution[i][j]) return false;
        }
    }
    return true;
}

static void sudoku_draw_interface() {
    printf("\033[H");
    printf(COLOR_BORDER "+-------+-------+-------+\n");
    for (int i = 0; i < 9; i++) {
        printf(COLOR_BORDER "| ");
        for (int j = 0; j < 9; j++) {
            char *color_code = COLOR_RESET;
            int val = grid[i][j];
            
            bool is_cursor = (i == cursor_r && j == cursor_c);
            bool is_fixed = (original[i][j] != 0);
            bool has_conflict = false;
            
            if (!is_fixed && val != 0) {
                grid[i][j] = 0;
                if (!is_safe(i, j, val)) has_conflict = true;
                grid[i][j] = val;
            }

            if (is_cursor) color_code = COLOR_CURSOR;
            else if (is_fixed) color_code = COLOR_FIXED;
            else if (has_conflict) color_code = COLOR_ERROR;
            else if (val != 0) color_code = COLOR_USER;

            if (val == 0) printf("%s. " COLOR_RESET, color_code);
            else printf("%s%d " COLOR_RESET, color_code, val);

            if ((j + 1) % 3 == 0) printf(COLOR_BORDER "| " COLOR_RESET);
        }
        printf("\n");
        if ((i + 1) % 3 == 0) printf(COLOR_BORDER "+-------+-------+-------+\n");
    }
}


void sudoku_run() {
    generate_puzzle();
    
    enableRawMode();
    clear_screen();

    while (1) {
        sudoku_draw_interface();
        int c = readKey();

        if (c == KEY_UP && cursor_r > 0) cursor_r--;
        if (c == KEY_DOWN && cursor_r < 8) cursor_r++;
        if (c == KEY_LEFT && cursor_c > 0) cursor_c--;
        if (c == KEY_RIGHT && cursor_c < 8) cursor_c++;

        if (c >= '1' && c <= '9') {
            if (original[cursor_r][cursor_c] == 0) {
                grid[cursor_r][cursor_c] = c - '0';
            }
        }
        
        if (c == '0' || c == KEY_DEL || c == KEY_BACKSPACE) {
            if (original[cursor_r][cursor_c] == 0) {
                grid[cursor_r][cursor_c] = 0;
            }
        }

        if (c == 'q') break;
        
        if (is_complete()) {
            sudoku_draw_interface();
            disableRawMode();
            printf("\nCongratulations! You have completed the puzzle!\n");
            getchar();
            break;
        }
    }
    
    disableRawMode();
}