#include <stdio.h>

// 文本颜色
#define ANSI_COLOR_BLACK   "\x1b[30m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
// 高亮度文本颜色
#define ANSI_COLOR_BRIGHT_BLACK   "\x1b[90m"
#define ANSI_COLOR_BRIGHT_RED     "\x1b[91m"
#define ANSI_COLOR_BRIGHT_GREEN   "\x1b[92m"
#define ANSI_COLOR_BRIGHT_YELLOW  "\x1b[93m"
#define ANSI_COLOR_BRIGHT_BLUE    "\x1b[94m"
#define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[95m"
#define ANSI_COLOR_BRIGHT_CYAN    "\x1b[96m"
#define ANSI_COLOR_BRIGHT_WHITE   "\x1b[97m"
// 背景颜色
#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"
// 高亮度背景颜色
#define ANSI_BACKGROUND_BRIGHT_BLACK   "\x1b[100m"
#define ANSI_BACKGROUND_BRIGHT_RED     "\x1b[101m"
#define ANSI_BACKGROUND_BRIGHT_GREEN   "\x1b[102m"
#define ANSI_BACKGROUND_BRIGHT_YELLOW  "\x1b[103m"
#define ANSI_BACKGROUND_BRIGHT_BLUE    "\x1b[104m"
#define ANSI_BACKGROUND_BRIGHT_MAGENTA "\x1b[105m"
#define ANSI_BACKGROUND_BRIGHT_CYAN    "\x1b[106m"
#define ANSI_BACKGROUND_BRIGHT_WHITE   "\x1b[107m"

#define ANSI_COLOR_RESET  "\x1b[0m"

int main() {
    // 普通文本颜色
    printf("%sThis is black text.%s\n", ANSI_COLOR_BLACK, ANSI_COLOR_RESET);
    printf("%sThis is red text.%s\n", ANSI_COLOR_RED, ANSI_COLOR_RESET);
    printf("%sThis is green text.%s\n", ANSI_COLOR_GREEN, ANSI_COLOR_RESET);
    printf("%sThis is yellow text.%s\n", ANSI_COLOR_YELLOW, ANSI_COLOR_RESET);
    printf("%sThis is blue text.%s\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
    printf("%sThis is magenta text.%s\n", ANSI_COLOR_MAGENTA, ANSI_COLOR_RESET);
    printf("%sThis is cyan text.%s\n", ANSI_COLOR_CYAN, ANSI_COLOR_RESET);
    printf("%sThis is white text.%s\n", ANSI_COLOR_WHITE, ANSI_COLOR_RESET);

    // 高亮度文本颜色
    printf("%sThis is bright black text.%s\n", ANSI_COLOR_BRIGHT_BLACK, ANSI_COLOR_RESET);
    printf("%sThis is bright red text.%s\n", ANSI_COLOR_BRIGHT_RED, ANSI_COLOR_RESET);
    printf("%sThis is bright green text.%s\n", ANSI_COLOR_BRIGHT_GREEN, ANSI_COLOR_RESET);
    printf("%sThis is bright yellow text.%s\n", ANSI_COLOR_BRIGHT_YELLOW, ANSI_COLOR_RESET);
    printf("%sThis is bright blue text.%s\n", ANSI_COLOR_BRIGHT_BLUE, ANSI_COLOR_RESET);
    printf("%sThis is bright magenta text.%s\n", ANSI_COLOR_BRIGHT_MAGENTA, ANSI_COLOR_RESET);
    printf("%sThis is bright cyan text.%s\n", ANSI_COLOR_BRIGHT_CYAN, ANSI_COLOR_RESET);
    printf("%sThis is bright white text.%s\n", ANSI_COLOR_BRIGHT_WHITE, ANSI_COLOR_RESET);

    // 背景颜色
    printf("%sThis has a black background.%s\n", ANSI_BACKGROUND_BLACK, ANSI_COLOR_RESET);
    printf("%sThis has a red background.%s\n", ANSI_BACKGROUND_RED, ANSI_COLOR_RESET);
    printf("%sThis has a green background.%s\n", ANSI_BACKGROUND_GREEN, ANSI_COLOR_RESET);
    printf("%sThis has a yellow background.%s\n", ANSI_BACKGROUND_YELLOW, ANSI_COLOR_RESET);
    printf("%sThis has a blue background.%s\n", ANSI_BACKGROUND_BLUE, ANSI_COLOR_RESET);
    printf("%sThis has a magenta background.%s\n", ANSI_BACKGROUND_MAGENTA, ANSI_COLOR_RESET);
    printf("%sThis has a cyan background.%s\n", ANSI_BACKGROUND_CYAN, ANSI_COLOR_RESET);
    printf("%sThis has a white background.%s\n", ANSI_BACKGROUND_WHITE, ANSI_COLOR_RESET);

    // 高亮度背景颜色
    printf("%sThis has a bright black background.%s\n", ANSI_BACKGROUND_BRIGHT_BLACK, ANSI_COLOR_RESET);
    printf("%sThis has a bright red background.%s\n", ANSI_BACKGROUND_BRIGHT_RED, ANSI_COLOR_RESET);
    printf("%sThis has a bright green background.%s\n", ANSI_BACKGROUND_BRIGHT_GREEN, ANSI_COLOR_RESET);
    printf("%sThis has a bright yellow background.%s\n", ANSI_BACKGROUND_BRIGHT_YELLOW, ANSI_COLOR_RESET);
    printf("%sThis has a bright blue background.%s\n", ANSI_BACKGROUND_BRIGHT_BLUE, ANSI_COLOR_RESET);
    printf("%sThis has a bright magenta background.%s\n", ANSI_BACKGROUND_BRIGHT_MAGENTA, ANSI_COLOR_RESET);
    printf("%sThis has a bright cyan background.%s\n", ANSI_BACKGROUND_BRIGHT_CYAN, ANSI_COLOR_RESET);
    printf("%sThis has a bright white background.%s\n", ANSI_BACKGROUND_BRIGHT_WHITE, ANSI_COLOR_RESET);

    return 0;
}