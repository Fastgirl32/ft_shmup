/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cleanup.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:07:24 by mhuszar           #+#    #+#             */
/*   Updated: 2024/04/14 22:25:59 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shmup.hpp"

int init_struct(t_game *game)
{
    int i = 0;
    game->enemies = NULL;
    while (i < 8)
    {
        if (!create_enemy(game))
            return (free_list(&game->enemies), 0);
        i++;
    }
    game->s_x = (int *)calloc(sizeof(int), 1000);
    if (!game->s_x)
        return (free_list(&game->enemies), 0);
    game->s_y = (int *)calloc(sizeof(int), 1000);
    if (!game->s_y)
        return (free_list(&game->enemies), free(game->s_x), 0);
    game->e_x = (int *)calloc(sizeof(int), 1000);
    if (!game->e_x)
        return (free_list(&game->enemies), free(game->s_x), free(game->s_y), 0);
    game->e_y = (int *)calloc(sizeof(int), 1000);
    if (!game->e_y)
        return (free_list(&game->enemies), free(game->s_x),
                free(game->s_y), free(game->e_x), 0);
    game->pshot = 0;
    game->eshot = 0;
    game->kill_count = 0;
    game->lives = 3;
    game->spawn_boss = false;
    game->quit = false;
    game->boss_health = 30;
    return (1);
}

int create_enemy(t_game *game)
{
    t_enemy *new_e;

    new_e = (t_enemy *)malloc(sizeof(t_enemy));
    if (!new_e)
        return (0);
    new_e->active = false;
    new_e->x = 0;
    new_e->y = 0;
    new_e->next = NULL;
    ft_lstadd_back(&game->enemies, new_e);
    return (1);
}

void free_list(t_enemy **proxy)
{
    t_enemy *prev;
    t_enemy *cur;

    if (!proxy || !(*proxy))
        return;
    cur = *proxy;
    while (cur)
    {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

int error(t_game *game, const char *str)
{
    free(game->s_x);
    free(game->s_y);
    free(game->e_x);
    free(game->e_y);
    free_list(&game->enemies);
    endwin();
    if (str)
    {
        printf("ERROR: %s", str);
        return (-1);
    }
    else
        return (0);
}

void ft_lstadd_back(t_enemy **lst, t_enemy *nw)
{
    t_enemy *proxy;

    if (!nw || !lst)
        return;
    proxy = *lst;
    if (!proxy)
        *lst = nw;
    else
    {
        while (proxy->next)
            proxy = proxy->next;
        proxy->next = nw;
    }
}

