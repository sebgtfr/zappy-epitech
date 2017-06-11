/*
** manager.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 15 16:23:42 2016 Sébastien Le Maire
** Last update Sun Jun 26 18:42:37 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

static t_zappy_error   		server_manage(t_zappy_server *server, int *max,
					      t_world *world)
{
  t_zappy_error			ret;

  if (FD_ISSET(server->socket.fd, &(server->fd_sets.fd_read)))
    if ((ret = new_client(server, max, world)) != ZAPPY_NO_ERROR)
      return (ret);
  if (FD_ISSET(server->socket.fd, &(server->fd_sets.fd_error)))
    return (ZAPPY_FD_ERROR);
  return (ZAPPY_NO_ERROR);
}

static t_zappy_error		fd_set_management(t_client_read manage_read,
						  t_zappy *zappy,
						  t_item **node_client)
{
  t_client			*client;
  t_zappy_error			err;

  client = (t_client *)((*node_client)->data);
  if ((manage_read) &&
      (FD_ISSET(client->socket.fd, &(zappy->server.fd_sets.fd_read))))
    if ((err = manage_read(node_client, zappy)) != ZAPPY_NO_ERROR)
      return (err);
  if (CMP_CLIENT_PTR(client, *node_client) &&
      (FD_ISSET(client->socket.fd, &(zappy->server.fd_sets.fd_write))))
    write_client_manager(client, zappy);
  if (CMP_CLIENT_PTR(client, *node_client) &&
      FD_ISSET(client->socket.fd, &(zappy->server.fd_sets.fd_error)))
    client->connection = ZAPPY_DISCONNECTE;
  return (ZAPPY_NO_ERROR);
}

static t_zappy_error		clients_manage(t_list *clients, t_zappy *zappy,
					       t_client_read manage_read,
					       t_zappy_error ret)
{
  t_item			*client_node;
  t_zappy_error		        err;
  t_item			*current_node;

  client_node = clients->begin;
  while (client_node)
    {
      current_node = client_node;
      if ((err = fd_set_management(manage_read, zappy,
				   &client_node)) != ZAPPY_NO_ERROR)
	return (err);
      if (current_node == client_node)
	client_node = client_node->next;
    }
  return (ret);
}

static void			check_egg_state(t_zappy *zappy)
{
  t_item			*del;
  t_item			*item;
  t_egg				*egg;
  char				data[16];

  item = zappy->server.eggs.begin;
  while (item)
    {
      egg = (t_egg *)(item->data);
      if (!(--egg->tick))
	{
	  (void)memset(data, 0, 16);
	  if (sprintf(data, "eht %u\n", egg->id) > 0)
	    list_foreach_data(&zappy->server.clients_graphic,
			      set_msg_all_client, data);
	  egg_client(&zappy->server, (t_team *)zappy->teams_manager.teams.data,
		     &zappy->world, egg);
	  del = item;
	  item = item->next;
	  list_erase(&zappy->server.eggs, del, NULL);
	}
      if (item)
	item = item->next;
    }
}

t_zappy_error	       	        manager(t_zappy *z, int *max,
					uint32_t *ticks_gen_resource)
{
  t_zappy_error			ret;
  t_bool			err;
  t_item			*node_client;

  ret = server_manage(&z->server, max, &z->world);
  ret = clients_manage(&z->server.clients_ia, z, &read_ia_manager, ret);
  ret = clients_manage(&z->server.clients_graphic, z, read_graph_manager, ret);
  if (check_tick_time(&z->timer, &err))
    {
      gen_resources(ticks_gen_resource, &z->world, z->server.clients_ia.length,
		    &z->server.clients_graphic);
      check_egg_state(z);
      node_client = z->server.clients_ia.begin;
      while (node_client)
	{
	  if ((((t_client *)(node_client->data))->connection
	       != ZAPPY_DISCONNECTE)
	      && (((t_client_ia *)(node_client->data))->player.team >= 0))
	    world_manage((t_client_ia *)node_client->data, z);
	  node_client = node_client->next;
	}
    }
  return ((err && ret == ZAPPY_NO_ERROR) ? ZAPPY_TIMER : ret);
}
