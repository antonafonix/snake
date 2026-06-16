#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "menu.h"

int main() {
    initscr();
    raw();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    srand(time(NULL));

    int start__menu_x = (80 - WIDTH) / 2;
    int start_menu_y = (24 - HEIGHT) / 2;
    int highlight = 0;

    WINDOW* menu_win = newwin(HEIGHT, WIDTH, start__menu_x, start_menu_y);
    keypad(menu_win, TRUE);

    draw_menu(menu_win, highlight);

    game_loop();

    endwin();
    return 0;
}
