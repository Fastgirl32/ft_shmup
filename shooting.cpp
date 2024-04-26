/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shooting.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:13:14 by mhuszar           #+#    #+#             */
/*   Updated: 2024/04/14 21:40:39 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"

int check_hits(t_game *game)
{
    int i = 0;
    t_enemy *proxy = game->enemies;

    while (game->s_y[i])
    {
        while (proxy)
        {
            if (proxy->active && game->s_y[i] == proxy->y && (game->s_x[i] >= proxy->x && game->s_x[i] <= proxy->x + 1))
            {
                mvwprintw(game->window, proxy->y, proxy->x, " ");
                wrefresh(game->window);
                proxy->active = false;
                game->kill_count++;
            }
            proxy = proxy->next;
        }
        proxy = game->enemies;
        i++;
    }
    mvprintw(0, 0, "Num of kills: %d", game->kill_count);
    mvprintw(1, 0, "Time: %ld", (game->current_time - game->beginning) / CLOCKS_PER_SEC);
    refresh();
    i = 0;
    while (game->s_y[i])
    {
        if (game->s_y[i] == game->k + 1 && (game->s_x[i] >= (game->max_x / 2) - 6 && game->s_x[i] <= (game->max_x / 2) + 6))
        {
            game->s_y[i] = 1000;
            game->s_x[i] = 1000;
            game->boss_health--;
        }
        if (game->s_y[i] == game->k && (game->s_x[i] >= (game->max_x / 2) - 7 && game->s_x[i] <= (game->max_x / 2) + 7))
        {
            game->s_y[i] = 1000;
            game->s_x[i] = 1000;
            game->boss_health--;
        }
        if (game->s_y[i] == game->k - 1 && (game->s_x[i] >= (game->max_x / 2) - 18 && game->s_x[i] <= (game->max_x / 2) + 18))
        {
            game->s_y[i] = 1000;
            game->s_x[i] = 1000;
            game->boss_health--;
        }
        if (game->boss_health <= 0)
            return (1);
        i++;
    }
    if (game->spawn_boss == true)
    {
        mvprintw(0, game->max_x / 2 - 15, "|");
        attron(COLOR_PAIR(4));
        mvprintw(0, game->max_x / 2 - 14, "              %d               ", game->boss_health);
        attroff(COLOR_PAIR(4));
        mvprintw(0, game->max_x / 2 - 14 + game->boss_health, "               ");
        if (game->boss_health <= 15)
        {
            mvprintw(0, game->max_x / 2 - 14 + 15 + game->boss_health, "               ");
            mvprintw(0, game->max_x / 2, "%d", game->boss_health);
        }
        mvprintw(0, game->max_x / 2 + 15, "|");
    }
    return (0);
}

int check_negate(t_game *game)
{
    int i = 0;
    int j = 0;
    while (i < 999)
    {
        while (j < 999)
        {
            if (game->e_x[i] != 0 && game->e_y[i] == game->s_y[j] && game->e_x[i] == game->s_x[j])
            {
                mvwprintw(game->window, game->e_y[i], game->e_x[i], " ");
                mvwprintw(game->window, game->s_y[j], game->s_x[j], " ");
                wrefresh(game->window);
                game->e_y[i] = game->s_y[j] = 1000;
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (1);
}

int pshots(t_game *game)
{
    int i;

    i = 0;
    while (game->s_y[i] != 0)
    {
        if (game->s_y[i] <= 0 && game->s_x[i] <= 0)
            continue;
        srand(time(NULL) + 50);
        mvwprintw(game->window, game->s_y[i], game->s_x[i], " ");
        if (game->s_y[i] > 1)
        {
            game->s_y[i]--;
            wattron(game->window, COLOR_PAIR(3));
            mvwprintw(game->window, game->s_y[i], game->s_x[i], "|");
            wattroff(game->window, COLOR_PAIR(3));
        }
        if (game->s_y[i] == 1)
        {
            game->s_y[i] = 1000;
            game->s_x[i] = 1000;
        }

        wrefresh(game->window);
        i++;
    }
    return (0);
}

int eshots(t_game *game)
{
    int i;

    i = 0;
    while (game->e_y[i] != 0 && game->e_x[i] != 0)
    {
        srand(time(NULL) + 50);
        mvwprintw(game->window, game->e_y[i], game->e_x[i], " ");
        if (game->e_y[i] < game->max_y - 2)
        {
            game->e_y[i]++;
            wattron(game->window, COLOR_PAIR(2));
            mvwprintw(game->window, game->e_y[i], game->e_x[i], "|");
            wattroff(game->window, COLOR_PAIR(2));
        }
        else
            game->e_y[i] = game->e_x[i] = 1000;
        wrefresh(game->window);
        i++;
    }
    wrefresh(game->window);
    return (0);
}

int spawnshot(t_game *game)
{
    t_enemy *proxy = game->enemies;

    while (proxy)
    {
        if (proxy->active == true)
        {
            game->e_x[game->eshot] = proxy->x;
            game->e_y[game->eshot] = proxy->y + 1;
            game->eshot++;
            if (game->eshot == 1000)
                game->eshot = 0;
            wattron(game->window, COLOR_PAIR(2));
            mvwprintw(game->window, game->e_y[game->eshot], game->e_x[game->eshot], "|");
            wattroff(game->window, COLOR_PAIR(2));
        }
        proxy = proxy->next;
    }
    wrefresh(game->window);
    return (0);
}

int spawnbossshot(t_game *game)
{
    if (game->spawn_boss && game->k > 3)
    {
        srand(time(NULL) * game->eshot);
        game->e_x[game->eshot] = (game->max_x / 2) + 18 - (rand() % 37);
        if (game->e_x[game->eshot] >= (game->max_x / 2) - 7 && game->e_x[game->eshot] <= (game->max_x / 2) + 7)
            game->e_y[game->eshot] = game->k;
        else if (game->e_x[game->eshot] >= (game->max_x / 2) - 8 && game->e_x[game->eshot] <= (game->max_x / 2) + 8)
            game->e_y[game->eshot] = game->k - 1;
        else
            game->e_y[game->eshot] = game->k - 2;
        game->eshot++;
        if (game->eshot == 1000)
            game->eshot = 0;
        wattron(game->window, COLOR_PAIR(2));
        mvwprintw(game->window, game->e_y[game->eshot], game->e_x[game->eshot], "|");
        wattroff(game->window, COLOR_PAIR(2));
    }
    wrefresh(game->window);
    return (0);
}
