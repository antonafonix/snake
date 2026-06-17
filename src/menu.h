#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdbool.h>
#include "game.h"

#define HEIGHT 20
#define WIDTH 40

extern char* menu_choices[];

extern int n_choices;

WINDOW* create_menu(int highlight);

void print_menu(WINDOW* menu_win, int highlight);

void draw_menu(WINDOW* menu_win, int highlight);


#endif