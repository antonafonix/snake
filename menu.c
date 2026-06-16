#include "menu.h"

void print_menu(WINDOW* menu_win, int highlight) {
    int x = 2;
    int y = 2;

    box(menu_win, 0, 0);

    for (int i = 0; i < n_choices; i++) {
        if (highlight == i) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", menu_choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", menu_choices[i]);
        }
        y++;
    }
    wrefresh(menu_choices);
}

void draw_menu(WINDOW* menu_win, int highlight) {
    int choice = -1;
    int c;

    mvprintw(0, 0, "Use arrow keys to navigate, press Enter to select.");
    refresh();

    print_menu(menu_win, highlight);

    while (true) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 0) {
                    highlight = n_choices - 1;
                } else {
                    highlight--;
                }
                break;
            case KEY_DOWN:
                if (highlight == n_choices - 1) {
                    highlight = 0;
                } else {
                    highlight++;
                }
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }

        print_menu(menu_win, highlight);

        if (choice != -1) break;
    }

    mvprintw(23, 0, "You chose: %s. Press any key to quit.",
             menu_choices[choice]);
    clrtoeol();
    refresh();
}