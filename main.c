#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int x;
    int y;
} coordinates;

struct player {
    coordinates position;
    char symbol;
};

struct food {
    coordinates position;
    char symbol;
};

bool check_collision(WINDOW* win, int next_y, int next_x, int* out_y,
                     int* out_x) {
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    *out_y = next_y;
    *out_x = next_x;
    bool collided = false;

    if (next_y < 1) {
        *out_y = 1;
        collided = true;
    } else if (next_y > max_y - 2) {
        *out_y = max_y - 2;
        collided = true;
    }

    if (next_x < 1) {
        *out_x = 1;
        collided = true;
    } else if (next_x > max_x - 2) {
        *out_x = max_x - 2;
        collided = true;
    }

    return collided;
}

void random_position(WINDOW* win, int* y, int* x) {
    int max_y, max_x;
    getmaxyx(win, max_y, max_x);

    int min_y = 1;
    int max_safe_y = max_y - 1;

    int min_x = 1;
    int max_safe_x = max_x - 2;

    *y = rand() % (max_safe_y - min_y + 1) + min_y;
    *x = rand() % (max_safe_x - min_x + 1) + min_x;
}

int main() {
    initscr();
    raw();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    srand(time(NULL));

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int height = 20;
    int width = 40;
    int start_y = (max_y - height) / 2;
    int start_x = (max_x - width) / 2;
    const char* msg = "END OF THE GAME";
    int center_x = (width / 2) - (strlen(msg) / 2);
    int center_y = height / 2;

    int vel_y = 0;
    int vel_x = 1;

    WINDOW* window = newwin(height, width, start_y, start_x);

    keypad(window, TRUE);
    nodelay(window, TRUE);

    box(window, 0, 0);

    struct player snake;
    random_position(window, &snake.position.y, &snake.position.x);
    snake.symbol = 'O';

    mvwaddch(window, snake.position.y, snake.position.x, snake.symbol);
    wrefresh(window);

    struct food apple;
    random_position(window, &apple.position.y, &apple.position.x);
    apple.symbol = '@';

    mvwaddch(window, apple.position.y, apple.position.x, apple.symbol);
    wrefresh(window);

    int ch;
    bool game_over = false;

    while (!game_over) {
        ch = wgetch(window);
        switch (ch) {
            case 'q':
                game_over = true;
                break;
            case KEY_UP:
                vel_y = -1;
                vel_x = 0;
                break;
            case KEY_DOWN:
                vel_y = 1;
                vel_x = 0;
                break;
            case KEY_LEFT:
                vel_y = 0;
                vel_x = -1;
                break;
            case KEY_RIGHT:
                vel_y = 0;
                vel_x = 1;
                break;
        }
        if (game_over) break;

        mvwaddch(window, snake.position.y, snake.position.x, ' ');

        int next_y = snake.position.y + vel_y;
        int next_x = snake.position.x + vel_x;

        if (check_collision(window, next_y, next_x, &snake.position.y,
                            &snake.position.x)) {
            mvwprintw(window, center_y, center_x, "%s", msg);
            wrefresh(window);

            nodelay(window, FALSE);
            wgetch(window);
            game_over = true;
        } else {
            mvwaddch(window, snake.position.y, snake.position.x, snake.symbol);
            wrefresh(window);
        }

        usleep(100000);
    }

    delwin(window);
    endwin();

    return 0;
}