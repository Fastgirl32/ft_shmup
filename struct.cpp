
#include "ft_shmup.hpp"

int move_player(int *x, int *y, int *max_x, int *max_y, WINDOW *window, t_game *game)
{
    static int k;
    char c = wgetch(window);
    mvwprintw(window, *y, *x, "%s", "    ");
    if (c == 'w' || c == 'W')
    {
        if (*y > 1)
            (*y)--;
    }
    else if (c == 'a' || c == 'A')
    {
        if (*x > 1)
            (*x)--;
    }
    else if (c == 's' || c == 'S')
    {
        if (*y < *max_y - 2)
            (*y)++;
    }
    else if (c == 'd' || c == 'D')
    {
        if (*x < *max_x - 5)
            (*x)++;
    }
    else if (c == ' ')
    {
        if (k % 2 == 0 && !game->spawn_boss)
        {
            if (game->pshot == 1000)
                game->pshot = 0;
            game->s_x[game->pshot] = *x + 1;
            game->s_y[game->pshot] = *y - 1;
            game->pshot++;
            wattron(game->window, COLOR_PAIR(3));
            mvwprintw(window, *y - 1, *x + 1, "|");
            wattroff(game->window, COLOR_PAIR(3));
        }
        else if (k % 3 == 0)
        {
            if (game->pshot == 1000)
                game->pshot = 0;
            game->s_x[game->pshot] = *x + 1;
            game->s_y[game->pshot] = *y - 1;
            game->pshot++;
            wattron(game->window, COLOR_PAIR(3));
            mvwprintw(window, *y - 1, *x + 1, "|");
            wattroff(game->window, COLOR_PAIR(3));
        }
        k++;
    }
    else if (c == 'q')
    {
        //endwin();
        game->quit = true;
        printf("Game over\n");
        return (1);
    }
    mvwprintw(window, *y, *x, "🚀");
    wrefresh(window);
    return (0);
}

int conflict(t_game *game, int x, int y)
{
    t_enemy *proxy = game->enemies;

    while (proxy)
    {
        if (proxy->active == true)
        {
            if (proxy->y >= y - 1 && proxy->y <= y + 1)
            {
                if (proxy->x >= x - 1 && proxy->x <= x + 1)
                    return (1);
            }
        }
        proxy = proxy->next;
    }
    return (0);
}

int check_collision(t_game *game)
{
    t_enemy *proxy = game->enemies;

    while (proxy)
    {
        if (proxy->active)
        {
            if ((game->player_x - proxy->x >= -1 && game->player_x - proxy->x <= 1) && (game->player_y == proxy->y))
                return (1);
        }
        proxy = proxy->next;
    }
    int i = 0;
    while (game->e_y[i] != 0)
    {
        if (game->e_y[i] == game->player_y && (game->e_x[i] <= game->player_x + 1 && game->e_x[i] >= game->player_x - 1))
        {
            game->lives--;
            game->e_y[i] = 1000;
            game->e_x[i] = 1000;
        }
        i++;
    }
    if (game->spawn_boss == true)
    {
        if (game->player_y == game->k && (game->player_x + 2 >= (game->max_x / 2) - 6 && game->player_x <= (game->max_x / 2) + 6))
            return (1);
        if (game->player_y == game->k - 1 && (game->player_x + 2 >= (game->max_x / 2) - 7 && game->player_x <= (game->max_x / 2) + 7))
            return (1);
        if (game->player_y == game->k - 2 && (game->player_x + 2 >= (game->max_x / 2) - 18 && game->player_x <= (game->max_x / 2) + 18))
            return (1);
        if (game->player_y == game->k - 3 && (game->player_x + 2 >= (game->max_x / 2) - 18 && game->player_x <= (game->max_x / 2) + 18))
            return (1);
        if (game->player_y == game->k - 4 && (game->player_x + 2 >= (game->max_x / 2) - 17 && game->player_x <= (game->max_x / 2) + 17))
            return (1);
        if (game->player_y == game->k - 5 && (game->player_x + 2 >= (game->max_x / 2) - 12 && game->player_x <= (game->max_x / 2) + 12))
            return (1);
        if (game->player_y == game->k - 6 && (game->player_x + 2 >= (game->max_x / 2) - 11 && game->player_x <= (game->max_x / 2) + 11))
            return (1);
        if (game->player_y == game->k - 7 && (game->player_x + 2 >= (game->max_x / 2) - 9 && game->player_x <= (game->max_x / 2) + 9))
            return (1);
        if (game->player_y == game->k - 8 && (game->player_x + 2 >= (game->max_x / 2) - 6 && game->player_x <= (game->max_x / 2) + 6))
            return (1);
    }
    if (game->lives == 2)
        mvprintw(1, game->max_x - 6, "-💜💜*");
    else if (game->lives == 1)
        mvprintw(1, game->max_x - 6, "---💜");
    if (game->lives < 1)
    {
        mvprintw(0, game->max_x - 6, "  ");
        return (1);
    }
    return (0);
}

int drawbackground(t_game *game, int k)
{
    int i;

    i = 1;
    while (i < game->max_y - 1)
    {
        if (k % 4 == 0)
            mvwaddnstr(game->window, game->max_y - 1 - i, 1, "    *    *  *      *       *  *       *      *          *           *         *    *         *      *             *           *    *          *          *       *          *       *      *         *    ", game->max_x - 2);
        if (k % 4 == 3)
            mvwaddnstr(game->window, game->max_y - 1 - i, 1, "*    *         *      *           *  *       *      *          *           *   *            *           *  *             *          *      *          *         *         *    *       *      *       *   *      *       ", game->max_x - 2);
        if (k % 4 == 2)
            mvwaddnstr(game->window, game->max_y - 1 - i, 1, "  *    *  *      *       *      *       *      *       *              *           *    *           *  *             *            *    *       *            *       *   *       *      *           *         *     ", game->max_x - 2);
        if (k % 4 == 1)
            mvwaddnstr(game->window, game->max_y - 1 - i, 1, "    *   *          *  *      *           *         *      *          *           *         *      *           *  *             *            *    *          *         *         *   *       *       *      *       *     ", game->max_x - 2);
        i++;
        k++;
    }
    wrefresh(game->window);
    return (0);
}

int main(void)
{
    t_game game;

    if (!init_struct(&game))
        return (dprintf(2, "Error: malloc failure\n"), -1);
    setlocale(LC_ALL, "");
    if (initscr() == NULL)
        return (error(&game, "Initialization failed\n"));
    curs_set(0);
    noecho();
    if (!has_colors())
        return (error(&game, "Color failed!\n"));
    getmaxyx(stdscr, game.max_y, game.max_x);
    if (game.max_y < 15 || game.max_x < 60)
        return (error(&game, "Window too small. Minimum is 15x60\n"));
    game.max_y -= 1;
    game.window = subwin(stdscr, game.max_y, game.max_x, 1, 0);
    if (game.window == NULL)
        return (error(&game, "Window initialization failure\n"));
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_RED);
    wborder(game.window, '|', '|', '-', '-', '*', '*', '*', '*');
    game.player_y = game.max_y - 2;
    game.player_x = game.max_x / 2;
    mvprintw(1, game.max_x - 6, "💜💜💜");
    refresh();
    wrefresh(game.window);

    game.ticks_interval = 0.5 * CLOCKS_PER_SEC;
    game.last_time = clock();
    game.last_time2 = clock();
    game.last_time3 = clock();
    game.last_time4 = clock();
    game.last_time5 = clock();
    game.beginning = clock();
    nodelay(game.window, true); // i put this so wgetchar doesnt block while waiting for input

    int k;
    k = 0;
    while (1)
    {
        game.current_time = clock();
        if (game.current_time - game.last_time >= game.ticks_interval)
        {
            drawbackground(&game, k++);
            if (!game.spawn_boss)
            {
                draw_enemies(game.player_x, game.player_y, game.max_x, game.max_y, &game);
                move_enemies_side(&game);
            }
            wrefresh(game.window);
            drawboss(&game);
            game.last_time = game.current_time;
            if (k > 1000000)
                k = 0;
        }
        if (game.current_time - game.last_time3 >= 0.1 * CLOCKS_PER_SEC)
        {
            // eshots(&game);
            pshots(&game);
            game.last_time3 = game.current_time;
        }
        if (game.current_time - game.last_time4 >= 0.2 * CLOCKS_PER_SEC)
        {
            eshots(&game);
            game.last_time4 = game.current_time;
        }
        if (game.current_time - game.last_time2 >= 3 * CLOCKS_PER_SEC)
        {
            spawnshot(&game);
            game.last_time2 = game.current_time;
        }
        if (game.current_time - game.last_time5 >= 0.2 * CLOCKS_PER_SEC)
        {
            spawnbossshot(&game);
            game.last_time5 = game.current_time;
        }
        if (move_player(&game.player_x, &game.player_y, &game.max_x, &game.max_y, game.window, &game))
            break;
        if (check_collision(&game))
            break;
        refresh();
        check_negate(&game);
        if (check_hits(&game))
            break;
    }
    if (check_collision(&game))
        return (error(&game, NULL), printf("YOU DIED!!!!"));
    else if (game.quit)
        return (error(&game, NULL));
    return (error(&game, NULL), printf("YOU WON!!!!"));
}