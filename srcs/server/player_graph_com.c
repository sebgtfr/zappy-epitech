/*
** player_graph_com.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun 23 10:28:21 2016 Sébastien Le Maire
** Last update Sun Jun 26 15:59:38 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

void				set_msg_new_player(t_client_ia *ia,
						   t_string *msg,
						   t_team *team)
{
  char				data[40];
  unsigned int			size;
  unsigned int			size_alloc;

  if ((size = sprintf(data, "pnw %u %d %d %d %d ", ia->client.id, ia->player.x,
		      ia->player.y, ia->player.facing, ia->player.level)) > 0)
    {
      team += ia->player.team;
      data[size] = '\0';
      size += strlen(team->name) + 1;
      size_alloc = msg->capacity - msg->length;
      size_alloc = (size_alloc < size) ? (size - size_alloc) : 0;
      if ((string_resize(msg, msg->capacity + size_alloc)) == EXIT_FAILURE)
	return ;
      string_push_back(msg, data);
      string_push_back(msg, team->name);
      string_push_back_char(msg, '\n');
    }
}

void				set_msg_all_new_player(t_list *clients,
						       t_string *msg,
						       t_team *team)
{
  t_item			*client_node;
  t_client_ia			*ia;

  client_node = clients->begin;
  while (client_node)
    {
      if (((t_client *)(client_node->data))->type == ZAPPY_CLIENT_IA)
	{
	  ia = ((t_client_ia *)(client_node->data));
	  if (ia->player.team >= 0)
	    set_msg_new_player(ia, msg, team);
	}
      client_node = client_node->next;
    }
}

void				set_msg_pos_player(t_client *client,
						   t_client_ia *ia)
{
  char				data[37];
  unsigned int			size;

  if ((size = sprintf(data, "ppo %u %d %d %d\n", ia->client.id, ia->player.x,
		      ia->player.y, ia->player.facing)) > 0)
    {
      data[size] = '\0';
      string_push_back(&client->msg, data);
    }
}

void				set_msg_lvl_player(t_client *client,
						   t_client_ia *ia)
{
  push_msg_lvl_player(&client->msg, ia);
}

void				set_msg_inventory_player(t_client *client,
							 t_client_ia *ia)
{
  char				data[104];
  unsigned int			size;

  if ((size = sprintf(data, "pin %u %u %u %u %u %u %u %u %u %u\n",
		      ia->client.id, ia->player.x, ia->player.y,
		      ia->player.inventory[ZAPPY_FOOD],
		      ia->player.inventory[ZAPPY_LINEMATE],
		      ia->player.inventory[ZAPPY_DERAUMERE],
		      ia->player.inventory[ZAPPY_SIBUR],
		      ia->player.inventory[ZAPPY_MENDIANE],
		      ia->player.inventory[ZAPPY_PHIRAS],
		      ia->player.inventory[ZAPPY_THYSTAME])) > 0)

    {
      data[size] = '\0';
      string_push_back(&client->msg, data);
    }
}
