#include <ncurses.h>
#include <stdbool.h>
#include <string.h>

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

    *out_y  = next_y;
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

int main() {
    initscr();
    raw();
    cbreak();
    noecho();
    curs_set(0);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int height = 20;
    int width = 40;
    int start_y = (max_y - height) / 2;
    int start_x = (max_x - width) / 2;
    const char* msg = "END OF THE GAME";
    int center_x = (width / 2) - (strlen(msg) / 2);
    int center_y = height / 2;

    WINDOW* window = newwin(height, width, start_y, start_x);
    keypad(window, TRUE);
    box(window, 0, 0);

    struct player snake;
    snake.position.x = 5;
    snake.position.y = 10;
    snake.symbol = 'O';

    mvwaddch(window, snake.position.y, snake.position.x, snake.symbol);
    wrefresh(window);

    int ch;
    while ((ch = wgetch(window)) != 'q') {
        // Erase old position
        mvwaddch(window, snake.position.y, snake.position.x, ' ');

        int next_y = snake.position.y;
        int next_x = snake.position.x;
        switch (ch) {
            case KEY_UP:
                next_y--;
                break;
            case KEY_DOWN:
                next_y++;
                break;
            case KEY_LEFT:
                next_x--;
                break;
            case KEY_RIGHT:
                next_x++;
                break;
        }

        if (check_collision(window, next_y, next_x, &snake.position.y,
                            &snake.position.x)) {
            mvwprintw(window, center_y, center_x, "%s", msg);
            wrefresh(window);
            wgetch(window);
            break;
        }

        mvwaddch(window, snake.position.y, snake.position.x, snake.symbol);
        wrefresh(window);
    }

    delwin(window);
    endwin();

    return 0;
}