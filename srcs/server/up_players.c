/*
** up_players.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy/srcs
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Fri Jun 24 13:11:59 2016
** Last update Sun Jun 26 19:48:58 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <string.h>
#include "zappy_map.h"
#include "zappy_server.h"
#include "client_action.h"

void		up_players(void *content, void *data)
{
  t_player	*player;
  t_client_ia	*client;
  char		nb[29];
  t_up_data	*param;
  t_team	*team;

  param = (t_up_data *)data;
  player = *(t_player **)content;
  if (param->can_up)
    player->level += 1;
  client = convert_player_to_client(player);
  team = (t_team *)(param->teams->data);
  team = &(team[player->level]);
  if (player->level == 8)
    team->max_lvl_player += 1;
  (void)memset(nb, 0, 29);
  sprintf(nb, "niveau actuel : %d\n", player->level);
  string_push_back(&(client->client.msg), nb);
}

void		up_all(t_vector *teams, t_list *list, int can_up,
		       t_zappy *z)
{
  t_up_data	data;
  char		msg[30];
  t_string	str;
  int		size;
  t_player	*ref;

  data.teams = teams;
  data.can_up = can_up;
  list_foreach_data(list, up_players, &data);
  ref = (*((t_player **)(list->begin->data)));
  string_init(&str, 0);
  if ((size = sprintf(msg, "pie %d %d %d\n", ref->x, ref->y, can_up)))
    {
      msg[size] = '\0';
      string_push_back(&str, msg);
    }
  msg_incantation_player_end(list, &str, &z->world, ref);
  string_push_back_char(&str, '\0');
  list_foreach_data(&z->server.clients_graphic, set_msg_all_client, str.data);
  string_clear(&str);
}

void		clean_case(t_zappy_map *m)
{
  m->resources[ZAPPY_LINEMATE] = 0;
  m->resources[ZAPPY_DERAUMERE] = 0;
  m->resources[ZAPPY_SIBUR] = 0;
  m->resources[ZAPPY_MENDIANE] = 0;
  m->resources[ZAPPY_PHIRAS] = 0;
  m->resources[ZAPPY_THYSTAME] = 0;
}

void set_start_pos(t_player *p)
{
  p->startx = p->x;
  p->starty = p->y;
}
