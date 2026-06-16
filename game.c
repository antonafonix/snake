#include "game.h"

player* add_tail(player* head, int y, int x, char symbol) {
    player* newNode = (player*)malloc(sizeof(player));
    if (newNode == NULL) return head;

    newNode->position.y = y;
    newNode->position.x = x;
    newNode->symbol = symbol;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    player* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    return head;
}

void move_snake(player* head, int next_y, int next_x) {
    if (head == NULL) return;

    int prev_y = head->position.y;
    int prev_x = head->position.x;

    head->position.y = next_y;
    head->position.x = next_x;

    player* current = head->next;
    while (current != NULL) {
        int temp_y = current->position.y;
        int temp_x = current->position.x;

        current->position.y = prev_y;
        current->position.x = prev_x;

        prev_y = temp_y;
        prev_x = temp_x;

        current = current->next;
    }
}

void draw_snake(WINDOW* window, player* head) {
    player* current = head;
    while (current != NULL) {
        mvwaddch(window, current->position.y, current->position.x,
                 current->symbol);
        current = current->next;
    }
}

void free_snake(player* head) {
    player* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

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
    int max_safe_y = max_y - 2;

    int min_x = 1;
    int max_safe_x = max_x - 2;

    *y = rand() % (max_safe_y - min_y + 1) + min_y;
    *x = rand() % (max_safe_x - min_x + 1) + min_x;
}

void game_loop() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int height = 20;
    int width = 40;
    int start_y = (max_y - height) / 2;
    int start_x = (max_x - width) / 2;

    const char* msg1 = "GAME OVER";
    const char* msg2 = "Press 'y' to replay";
    const char* msg3 = "or any key to quit";

    int center_x1 = (width / 2) - (strlen(msg1) / 2);
    int center_x2 = (width / 2) - (strlen(msg2) / 2);
    int center_x3 = (width / 2) - (strlen(msg3) / 2);
    int center_y = height / 2;

    bool play_again = false;

    do {
        int vel_y = 0;
        int vel_x = 1;
        int points = 0;
        bool game_over = false;

        clear();
        refresh();

        WINDOW* window = newwin(height, width, start_y, start_x);
        keypad(window, TRUE);
        nodelay(window, TRUE);
        box(window, 0, 0);

        int start_snake_y, start_snake_x;
        random_position(window, &start_snake_y, &start_snake_x);

        player* snake = NULL;
        snake = add_tail(snake, start_snake_y, start_snake_x, 'O');

        struct food apple;
        random_position(window, &apple.position.y, &apple.position.x);
        apple.symbol = '@';
        mvwaddch(window, apple.position.y, apple.position.x, apple.symbol);

        mvwprintw(window, 0, 2, "[ Score: %d ]", points);
        wrefresh(window);

        while (!game_over) {
            int ch = wgetch(window);

            if (snake->position.y == apple.position.y &&
                snake->position.x == apple.position.x) {
                points += 100;
                mvwprintw(window, 0, 2, "[ Score: %d ]", points);

                snake =
                    add_tail(snake, snake->position.y, snake->position.x, '#');

                random_position(window, &apple.position.y, &apple.position.x);
                mvwaddch(window, apple.position.y, apple.position.x,
                         apple.symbol);
                wrefresh(window);
            }

            switch (ch) {
                case 'q':
                    game_over = true;
                    play_again = false;
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

            player* clear_ptr = snake;
            while (clear_ptr != NULL) {
                mvwaddch(window, clear_ptr->position.y, clear_ptr->position.x,
                         ' ');
                clear_ptr = clear_ptr->next;
            }

            int next_y = snake->position.y + vel_y;
            int next_x = snake->position.x + vel_x;
            int out_y, out_x;

            if (check_collision(window, next_y, next_x, &out_y, &out_x)) {
                mvwprintw(window, center_y - 1, center_x1, "%s", msg1);
                mvwprintw(window, center_y, center_x2, "%s", msg2);
                mvwprintw(window, center_y + 1, center_x3, "%s", msg3);
                wrefresh(window);

                nodelay(window, FALSE);
                int choice = wgetch(window);

                if (choice == 'y' || choice == 'Y') {
                    play_again = true;
                } else {
                    play_again = false;
                }
                game_over = true;
            } else {
                move_snake(snake, next_y, next_x);

                mvwaddch(window, apple.position.y, apple.position.x,
                         apple.symbol);
                draw_snake(window, snake);
                wrefresh(window);
            }

            usleep(100000);
        }

        free_snake(snake);
        delwin(window);

    } while (play_again);
    
}