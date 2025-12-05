#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

#define COLOR_RESET  "\033[0m"
#define COLOR_CURSOR "\033[7m"    // 反白
#define COLOR_ERROR  "\033[1;31m" // 錯誤 紅
#define COLOR_BORDER "\033[0;37m" // 邊框 白
#define COLOR_FIXED  "\033[1;33m" // 題目 粗黃 
#define COLOR_USER   "\033[1;36m" // 玩家輸入 粗青

#define KEY_UP    1001
#define KEY_DOWN  1002
#define KEY_LEFT  1003
#define KEY_RIGHT 1004
#define KEY_ENTER 10
#define KEY_ESC   27
#define KEY_DEL   127
#define KEY_BACKSPACE 127

#endif