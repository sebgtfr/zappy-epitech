/*
** client.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Tue Jun 14 12:06:47 2016 Sébastien Le Maire
** Last update Sun Jun 26 01:09:07 2016 Sébastien Le Maire
*/

#include <unistd.h>
#include "zappy_server.h"

void				client_set_com(t_list *list, t_zappy_com com)
{
  t_item			*client_node;

  client_node = list->begin;
  while (client_node)
    {
      ((t_client *)(client_node->data))->com = com;
      client_node = client_node->next;
    }
}

void				close_clients(void *clients)
{
  t_client			*client;

  client = (t_client *)clients;
  delete_socket(&client->socket);
  string_clear(&client->msg);
}

t_zappy_error			egg_client(t_zappy_server *server, t_team *team,
					   t_world *world, t_egg *egg)
{
  t_client_ia			cli;

  cli.client.socket.socklen = (socklen_t)(sizeof(cli.client.socket.sockaddr));
  cli.client.socket.fd = -1;
  cli.client.connection = ZAPPY_CONNECTION_UNDEFINE;
  cli.client.type = ZAPPY_CLIENT_UNDEFINED;
  cli.client.com = ZAPPY_COM_LAST;
  cli.client.id = 0;
  cli.client.id_egg = egg->id;
  cli.player.x = egg->x;
  cli.player.y = egg->y;
  cli.player.team = egg->team;
  string_init(&cli.client.msg, 0);
  if (list_push_back(&server->clients_ia, (void *)&cli) == EXIT_FAILURE)
    return (ZAPPY_BAD_ALLOC);
  init_player(&((t_client_ia *)(server->clients_ia.end->data))->player,
	      world, 0);
  ++(team[cli.player.team].nb_ghost);
  ++(team[cli.player.team].slot);
  return (ZAPPY_NO_ERROR);
}

t_zappy_error			new_client(t_zappy_server *server, int *max,
					   t_world *world)
{
  t_client_ia			cli;

  cli.client.socket.socklen = (socklen_t)(sizeof(cli.client.socket.sockaddr));
  if ((cli.client.socket.fd = accept(server->socket.fd,
				     (struct sockaddr *)&cli.client.socket.sockaddr,
				     &cli.client.socket.socklen)) < 0)
    return (ZAPPY_ACCEPT);
  if (cli.client.socket.fd > (*max))
    *max = cli.client.socket.fd;
  cli.client.connection = ZAPPY_CONNECTE;
  cli.client.type = ZAPPY_CLIENT_IA;
  cli.client.com = ZAPPY_COM_WELCOME;
  cli.client.id_egg = 0;
  cli.client.id = 0;
  string_init(&cli.client.msg, 0);
  if (list_push_back(&server->clients_ia, (void *)&cli) == EXIT_FAILURE)
    {
      close(cli.client.socket.fd);
      return (ZAPPY_BAD_ALLOC);
    }
  init_player(&((t_client_ia *)(server->clients_ia.end->data))->player,
	      world, 1);
  return (ZAPPY_NO_ERROR);
}

t_item				*delete_client(t_list *clients, t_item *client,
					       int *max, t_zappy *zappy)
{
  t_item			*ret;
  t_client_ia			*cur;
  unsigned int			*nb_player;
  t_vector			*teams;

  ret = client->next;
  teams = &zappy->teams_manager.teams;
  if ((*max) == ((t_client *)(client->data))->socket.fd)
    --(*max);
  if (((t_client *)(client->data))->type != ZAPPY_CLIENT_GRAPHIC)
    {
      cur = (t_client_ia *)(client->data);
      delete_player_on_map(&cur->player, &zappy->world);
      if ((cur->player.team >= 0) &&
	  ((unsigned int)cur->player.team < teams->length))
	{
	  nb_player = &(((t_team *)(teams->data))[cur->player.team].nb_player);
	  if ((nb_player) && ((*nb_player) > 0))
	    --(*nb_player);
	}
    }
  list_erase(clients, client, close_clients);
  return (ret);
}
