/*
** fork.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Sat Jun 25 16:55:44 2016
** Last update Sat Jun 25 22:52:50 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

static void	       	send_msg_begin_fork_graph(t_list *graph, uint32_t id)
{
  char			data[16];
  unsigned int		size;

  if ((size = sprintf(data, "pfk %u\n", id)) > 0)
    {
      data[size] = '\0';
      list_foreach_data(graph, set_msg_all_client, data);
    }
}

static void	        send_msg_end_fork_graph(t_list *graph, uint32_t id,
						t_egg *egg)
{
  char			data[46];
  unsigned int		size;

  if ((size = sprintf(data, "enw %u %u %d %d\n", egg->id, id,
		      egg->x, egg->y)) > 0)
    {
      data[size] = '\0';
      list_foreach_data(graph, set_msg_all_client, data);
    }
}

void			fatherfork(t_client_ia *client, t_zappy *zappy)
{
  send_msg_begin_fork_graph(&zappy->server.clients_graphic, client->client.id);
}

void			motherfork(t_client_ia *client, t_zappy *zappy)
{
  t_egg			egg;

  egg.x = client->player.x;
  egg.y = client->player.y;
  egg.tick = 600;
  egg.id = ++(zappy->server.last_id_egg);
  egg.team = client->player.team;
  list_push_back(&(zappy->server.eggs), &(egg));
  send_msg_end_fork_graph(&zappy->server.clients_graphic, client->client.id,
			  &egg);
  set_answer_ok_ko(&client->client, TRUE);
}
