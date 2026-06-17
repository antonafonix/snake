#include <time.h>

#include "game.h"
#include "menu.h"

int main() {
    srand(time(NULL));
    int highlight = 0;

    while (true) {
        initscr();
        raw();
        cbreak();
        noecho();
        curs_set(0);

        WINDOW* menu_win = create_menu(highlight);
        draw_menu(menu_win, highlight);

        wclear(menu_win);
        wrefresh(menu_win);
        delwin(menu_win);

        clear();
        refresh();

        game_loop();
    }

    endwin();
    return 0;
}
