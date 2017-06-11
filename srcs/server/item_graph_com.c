/*
** item_graph_com.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sat Jun 25 14:59:35 2016 Sébastien Le Maire
** Last update Sat Jun 25 16:02:41 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

static void	       	set_msg_item(t_client *client, uint32_t id,
				     t_zappy_resource resource,
				     char const *cmd)
{
  char			data[18];
  unsigned int		size;

  if ((size = sprintf(data, "%s %d %d\n", cmd, id, resource)) > 0)
    {
      data[size] = '\0';
      string_push_back(&client->msg, data);
    }
}

void			set_all_client_msg_item(t_zappy *zappy,
						t_client_ia *ia,
						t_zappy_resource resource,
						char const *cmd)
{
  t_item		*node;
  t_client		*client;

  node = zappy->server.clients_graphic.begin;
  while (node)
    {
      client = (t_client *)(node->data);
      if (string_resize(&client->msg, client->msg.capacity + 60)
	  != EXIT_FAILURE)
	{
	  set_msg_item(client, ia->client.id, resource, cmd);
	  set_msg_inventory_player(client, ia);
	  set_answer_data_case(client, &zappy->world,
			       ia->player.x, ia->player.y);
	}
      node = node->next;
    }
}
