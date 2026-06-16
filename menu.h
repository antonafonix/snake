#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <stdbool.h>

#define HEIGHT 20
#define WIDTH 40

const char* menu_choices[] = {"Start Game", "Exit"};

const int n_choices = sizeof(menu_choices) / sizeof(char*);

void print_menu(WINDOW* menu_win, int highlight);

void draw_menu(WINDOW* menu_win, int highlight);

#endif