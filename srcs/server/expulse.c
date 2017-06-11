/*
** map1.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Mon Jun 20 15:09:14 2016
** Last update Sun Jun 26 12:27:20 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

t_client_ia			*convert_player_to_client(t_player *player)
{
  t_client_ia			ia;

  return ((t_client_ia *)((size_t)player - ((size_t)&ia.player - (size_t)&ia)));
}

int		get_expulsed(int push, int facing)
{
  if (push == UP)
    return (((facing * 2 - 1) + 4) % 8);
  if (push == RIGHT)
    return (((facing * 2 - 1) + 2) % 8);
  if (push == DOWN)
    return (((facing * 2 - 1)) % 8);
  return (((facing * 2 - 1) + 6) % 8);
}

void		expulse_each_player(void *content, void *data)
{
  t_zappy_move	*tmp;
  t_player	*player;
  char		nb[30];
  t_client_ia	*client;

  player = *(t_player **)content;
  tmp = (t_zappy_move *)data;
  if (player != tmp->player)
    {
      if (tmp->player->facing == RIGHT)
	player->x = MOD(player->x + 1, (int)(tmp->width));
      else if (tmp->player->facing == LEFT)
	player->x = MOD(player->x - 1, (int)(tmp->width));
      else if (tmp->player->facing == UP)
	player->y = MOD(player->y - 1, (int)(tmp->height));
      else
	player->y = MOD(player->y + 1, (int)(tmp->height));
      player->expulsed_from = get_expulsed(tmp->player->facing, player->facing);
      list_push_back(tmp->dest, &player);
      client = convert_player_to_client(player);
      if (sprintf(nb, "deplacement: %d\n", player->expulsed_from) > 0)
	string_push_back(&(client->client.msg), nb);
      msg_expulse_pos_player(&tmp->graph, client);
    }
}

void		expulse_players(t_world *w, t_player *p, t_list *graph)
{
  t_list	*src;
  t_list	*dest;
  t_zappy_move	data;

  data.player = p;
  data.width = w->width;
  data.height = w->height;
  src = &(w->map[POS(p->x, p->y, w->width)].list);
  if (p->facing == RIGHT)
    dest = &(w->map[POS(MOD(p->x + 1, (int)(w->width)), p->y, w->width)].list);
  else if (p->facing == LEFT)
    dest = &(w->map[POS(MOD(p->x - 1, (int)(w->width)), p->y, w->width)].list);
  else if (p->facing == UP)
    dest = &(w->map[POS(p->x, MOD(p->y - 1, (int)(w->height)), w->width)].list);
  else
    dest = &(w->map[POS(p->x, MOD(p->y + 1, (int)(w->height)), w->width)].list);
  data.dest = dest;
  msg_expulse_exe(&data.graph, convert_player_to_client(p)->client.id);
  list_foreach_data(src, expulse_each_player, &data);
  data.graph.data[data.graph.length] = '\0';
  list_foreach_data(graph, set_msg_all_client, data.graph.data);
  string_clear(&data.graph);
  list_clear(src, NULL);
  list_push_back(src, &p);
}
