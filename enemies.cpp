/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:10:10 by mhuszar           #+#    #+#             */
/*   Updated: 2024/04/14 22:22:38 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"

int draw_enemies(int player_x, int player_y, int max_x, int max_y, t_game *game)
{
    int x;
    int y;
    unsigned int counter = 1;
    t_enemy *proxy = game->enemies;

    while (proxy)
    {
        if (proxy->active == false)
        {
            while (1)
            {
                srand(time(NULL) * counter);
                x = (rand() % (max_x - 4)) + 2;
                y = (rand() % (max_y / 8 * 5)) + 2;
                counter++;
                if (x != player_x && y != player_y && !conflict(game, x, y))
                    break;
            }
            proxy->x = x;
            proxy->y = y;
            mvwprintw(game->window, y, x, "👾");
            wrefresh(game->window);
            proxy->active = true;
        }
        proxy = proxy->next;
    }
    return (1);
}

int move_enemies_down(t_game *game)
{
    game->e1_y++;
    game->e2_y++;
    wrefresh(game->window);
    return (0);
}

int move_enemies_side(t_game *game)
{
    t_enemy *proxy = game->enemies;

    unsigned int counter = 1;
    while (proxy)
    {
        srand(time(NULL) * counter);
        mvwprintw(game->window, proxy->y, proxy->x, " ");
        if (rand() % 2 == 1 && proxy->x < game->max_x - 6 /*&& proxy->x > 3*/)
            proxy->x++;
        else if (proxy->x > 3)
            proxy->x--;
        mvwprintw(game->window, proxy->y, proxy->x, "👾");
        wrefresh(game->window);
        counter++;
        proxy = proxy->next;
    }
    return (0);
}

int drawboss(t_game *game)
{
    static int k;
    t_enemy *proxy = game->enemies;

    if (game->kill_count >= 25)
        game->spawn_boss = true;
    while (proxy && game->spawn_boss)
    {
        if (proxy->active)
        {
            mvwprintw(game->window, proxy->y, proxy->x, " ");
            wrefresh(game->window);
            proxy->active = false;
        }
        proxy = proxy->next;
    }
    if (game->spawn_boss == true)
    {
        if (k < 10)
        {
            k++;
            game->k = k;
        }
        if (k > 8)
            mvwprintw(game->window, k - 8, game->max_x / 2 + 12 - 18, "_.-'~~~~'-._");
        if (k > 7)
            mvwprintw(game->window, k - 7, game->max_x / 2 + 9 - 18, ".-~ \\__/  \\__/ ~-.");
        if (k > 6)
            mvwprintw(game->window, k - 6, game->max_x / 2 + 7 - 18, ".-~   (oo)  (oo)    ~-.");
        if (k > 5)
            mvwprintw(game->window, k - 5, game->max_x / 2 + 6 - 18, "(_____//~~\\\\//~~\\\\______)");
        if (k > 4)
            mvwprintw(game->window, k - 4, game->max_x / 2 + 1 - 18, "_.-~`                         `~-._");
        if (k > 3)
            mvwprintw(game->window, k - 3, game->max_x / 2 - 18, "/O=O=O=O=O=O=O=O=O=O=O=O=O=O=O=O=O=O\\");
        if (k > 2)
            mvwprintw(game->window, k - 2, game->max_x / 2 - 18, "\\___________________________________/");
        if (k > 1)
            mvwprintw(game->window, k - 1, game->max_x / 2 + 11 - 18, "\\x x x x x x x/");
        mvwprintw(game->window, k, game->max_x / 2 + 12 - 18, "\\x_x_x_x_x_x/");
    }
    return (0);
}