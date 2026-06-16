#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int x;
    int y;
} coordinates;

typedef struct player {
    coordinates position;
    struct player* next;
    char symbol;
} player;

struct food {
    coordinates position;
    char symbol;
};

player* add_tail(player* head, int y, int x, char symbol);

void move_snake(player* head, int next_y, int next_x);

void draw_snake(WINDOW* window, player* head);

void free_snake(player* head);

bool check_collision(WINDOW* win, int next_y, int next_x, int* out_y,
                     int* out_x);

void random_position(WINDOW* win, int* y, int* x);

void game_loop();

#endif