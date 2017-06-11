/*
** broadcast.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 22 21:31:52 2016 Sébastien Le Maire
** Last update Sun Jun 26 14:04:52 2016 Sébastien Le Maire
*/

#include <string.h>
#include <stdio.h>
#include "zappy_server.h"

void				set_dir(t_player *p, int dir)
{
  t_client_ia			*client;
  t_client_ia			ia;
  char				nb[2];

  client = (t_client_ia *)((size_t)p - ((size_t)&ia.player - (size_t)&ia));
  string_push_back(&(client->client.msg), "message ");
  if (dir == 0 || p->facing == UP)
    sprintf(nb, "%d", dir);
  else if (p->facing == LEFT)
    sprintf(nb, "%d", (dir + 5) % 8 + 1);
  else if (p->facing == DOWN)
    sprintf(nb, "%d", (dir + 3) % 8 + 1);
  else
    sprintf(nb, "%d", (dir + 1) % 8 + 1);
  string_push_back(&(client->client.msg), nb);
  string_push_back_char(&(client->client.msg), ',');
}

int				determine_with_coef(double coef, int sens)
{
  if (coef <= -3)
    return (1);
  if (coef <= -0.33 && sens > 0)
    return (4);
  else if (coef <= -0.33)
    return (8);
  if (coef <= 0.33 && sens > 0)
    return (3);
  else if (coef <= 0.33)
    return (7);
  if (coef <= 3 && sens > 0)
    return (2);
  else if (coef <= 3)
    return (6);
  return (5);
}

void				get_dir(int coor[], t_player *p, int x, int y)
{
  int				dir;

  if (coor[0] == x && coor[1] == y)
    dir = 0;
  else if (coor[0] == x)
    {
      if (coor[1] < y)
	dir = 5;
      else
	dir = 1;
    }
  else if (coor[1] == y)
    {
      if (coor[0] < x)
	dir = 7;
      else
	dir = 3;
    }
  else
    dir = determine_with_coef(((double)(coor[1]) - (double)y) /
			      ((double)(coor[0]) - (double)x), coor[0] - x);
  set_dir(p, dir);
}

void				hear(t_player *p, t_world *w, int x, int y)
{
  int				new_x;
  int				new_y;
  double			dist[4];
  int				final_coor[2];

  new_x = (x > p->x) ? (p->x + w->width) : (p->x - w->width);
  new_y = (y > p->y) ? (p->y + w->height) : (p->y - w->height);
  dist[0] = (x - p->x) * (x - p->x) + (y - p->y) * (y - p->y);
  dist[1] = (x - new_x) * (x - new_x) + (y - p->y) * (y - p->y);
  dist[2] = (x - p->x) * (x - p->x) + (y - new_y) * (y - new_y);
  dist[3] = (x - new_x) * (x - new_x) + (y - new_y) * (y - new_y);
  if ((dist[0] <= dist[1] && dist[0] <= dist[3]) ||
      (dist[2] <= dist[1] && dist[2] <= dist[3]))
    final_coor[0] = p->x;
  else
    final_coor[0] = new_x;
  if ((dist[0] <= dist[2] && dist[0] <= dist[3]) ||
      (dist[1] <= dist[2] && dist[1] <= dist[3]))
    final_coor[1] = p->y;
  else
    final_coor[1] = new_y;
  get_dir(final_coor, p, x, y);
}

void				broadcast(t_client_ia *ia, t_zappy *zappy)
{
  char const			*msg;
  size_t			size;
  t_item			*list_ia;
  t_client_ia			*client;

  msg = ia->player.action[LAST_ORDER(ia->player.id_order)].arg;
  size = strlen(msg);
  list_ia = zappy->server.clients_ia.begin;
  while (list_ia)
    {
      client = (t_client_ia *)list_ia->data;
      if ((client->client.connection == ZAPPY_CONNECTE) &&
	  (client->player.team >= 0) &&
	  (client != ia) &&
	  (string_resize(&client->client.msg,
			 (client->client.msg.capacity + size + 2))
	   != EXIT_FAILURE))
	{
	  hear(&(client->player), &(zappy->world), ia->player.x, ia->player.y);
	  string_push_back(&client->client.msg, msg);
	  string_push_back_char(&client->client.msg, '\n');
	}
      list_ia = list_ia->next;
    }
  set_msg_broadcast(ia->client.id, msg, &zappy->server.clients_graphic);
}
