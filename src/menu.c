#include "menu.h"

#include <ncurses.h>

int n_choices = 2;
char* menu_choices[] = {"Start", "Exit"};

WINDOW* create_menu(int highlight) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    
    int start_menu_x = (max_x - WIDTH) / 2;
    int start_menu_y = (max_y - HEIGHT) / 2;

    WINDOW* menu_win = newwin(HEIGHT, WIDTH, start_menu_y, start_menu_x);
    keypad(menu_win, TRUE);

    return menu_win;
}

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
            mvwprintw(menu_win, y, x, "%s   ", menu_choices[i]);
        }
        y++;
    }
    wrefresh(menu_win);
}

void draw_menu(WINDOW* menu_win, int highlight) {
    int choice = -1;
    int c;

    mvprintw(0, 0, "Use arrow keys to navigate, press Enter to select.");
    refresh();

    print_menu(menu_win, highlight);

    while (1) {
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

    if (choice == 0) {
        wclear(menu_win);
        wrefresh(menu_win);
        return;
    } else if (choice == 1) {
        delwin(menu_win);
        endwin();
        exit(0);
        return;
    }
}
