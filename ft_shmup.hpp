/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shmup.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 21:39:33 by mhuszar           #+#    #+#             */
/*   Updated: 2024/04/14 22:23:56 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHMUP_HPP
#define FT_SHMUP_HPP

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

typedef struct s_enemy
{
	bool active;
	int x;
	int y;
	struct s_enemy *next;
} t_enemy;

typedef struct s_game
{
	WINDOW *window;
	int player_x;
	int player_y;
	int max_y;
	int max_x;
	clock_t beginning;
	clock_t current_time;
	clock_t last_time;
	clock_t last_time2;
	clock_t last_time3;
	clock_t last_time4;
	clock_t last_time5;
	clock_t ticks_interval;
	bool e1_active;
	int e1_x;
	int e1_y;
	bool e2_active;
	bool spawn_boss;
	int boss_health;
	int e2_x;
	int k;
	int e2_y;
	int *s_y;
	int *s_x;
	int pshot;
	int *e_y;
	int *e_x;
	int eshot;
	int kill_count;
	int lives;
	bool quit;
	t_enemy *enemies;
} t_game;

//init
int init_struct(t_game *game);
int create_enemy(t_game *game);

//enemies
int draw_enemies(int player_x, int player_y, int max_x, int max_y, t_game *game);
int drawboss(t_game *game);
int conflict(t_game *game, int x, int y);
int move_enemies_down(t_game *game);
int move_enemies_side(t_game *game);

//shooting
int check_hits(t_game *game);
int check_negate(t_game *game);
int spawnbossshot(t_game *game);
int spawnshot(t_game *game);
int eshots(t_game *game);
int pshots(t_game *game);

//freeing and utils
void free_list(t_enemy **proxy);
int error(t_game *game, const char *str);
void ft_lstadd_back(t_enemy **lst, t_enemy *nw);


#endif
