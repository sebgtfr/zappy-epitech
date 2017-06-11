/*
** team.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 15 17:31:52 2016 Sébastien Le Maire
** Last update Sun Jun 26 01:10:07 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "zappy_server.h"

static void		        send_new_player_to_graph(t_list *graph,
							 t_client_ia *ia,
							 t_team *team)
{
  t_item			*node;
  t_client			*client;

  if (ia)
    {
      node = graph->begin;
      while (node)
	{
	  client = ((t_client *)(node->data));
	  if (ia->client.id_egg)
	    set_msg_egg_player(&client->msg, ia->client.id_egg);
	  set_msg_new_player(ia, &client->msg, team);
	  node = node->next;
	}
    }
}

static char			add_on_team(t_client_ia *client,
					    unsigned int team,
					    t_team_manager *teams_manager,
					    t_list *list_ia)
{
  t_team			*current_team;

  current_team = ((t_team *)(teams_manager->teams.data)) + team;
  if (current_team->nb_player <
      (teams_manager->nb_client_max + current_team->slot))
    {
      client->player.team = team;
      ++(current_team->nb_player);
      client->client.com = ZAPPY_COM_INFO_NEW_PLAYER;
      return ((current_team->nb_ghost) ? egg_to_player(client, list_ia) : 1);
    }
  return (0);
}

static uint8_t			check_team(char const *buf,
					   t_item **client_node,
					   t_client_ia **ia,
					   t_zappy *z)
{
  int				team;
  char				ret;
  t_client_ia			*client;
  t_item			*old_ia;

  ret = 0;
  team = -1;
  client = *ia;
  while (((++team) < (int)z->teams_manager.teams.length) && (!ret))
    {
      if ((!strcmp((((t_team *)(z->teams_manager.teams.data)) + team)->name,
		   buf)) && ((ret = add_on_team(client, team, &z->teams_manager,
						&z->server.clients_ia))) == 2)
	{
	  --(((t_team *)(z->teams_manager.teams.data))[team].nb_ghost);
	  recup_player_from_egg(ia, &z->server.clients_ia);
	  old_ia = *client_node;
	  *client_node = (*client_node)->next;
	  delete_player_on_map(&client->player, &z->world);
	  list_erase(&z->server.clients_ia, old_ia, NULL);
	}
    }
  if (ret)
    (*ia)->client.id = ++(z->server.last_id);
  return (ret);
}

static t_zappy_error		move_ia_to_graphic(t_item **client,
						   t_zappy *zappy)
{
  t_client_graphic		graphic;
  t_item			*old_ia;

  old_ia = *client;
  *client = (*client)->next;
  (void)memcpy(&graphic.client, (void *)old_ia->data, sizeof(graphic.client));
  delete_player_on_map(&((t_client_ia *)(old_ia->data))->player, &zappy->world);
  list_erase(&zappy->server.clients_ia, old_ia, NULL);
  graphic.client.type = ZAPPY_CLIENT_GRAPHIC;
  set_answer_init_graphic(&graphic.client, zappy);
  if (list_push_back(&zappy->server.clients_graphic, &graphic) == EXIT_FAILURE)
    return (ZAPPY_BAD_ALLOC);
  return (ZAPPY_NO_ERROR);
}

t_zappy_error			get_team(t_item **client_node, t_zappy *zappy)
{
  char				buf[1024];
  unsigned int			size;
  t_client_ia			*client;

  client = (t_client_ia *)((*client_node)->data);
  server_recv(&client->client, (void *)buf, 1024);
  if (client->client.connection == ZAPPY_CONNECTE)
    {
      size = strlen(buf);
      if (buf[size - 1] == '\n')
	buf[size - 1] = '\0';
      if (!strcmp("GRAPHIC", buf))
	return (move_ia_to_graphic(client_node, zappy));
      else if (check_team(buf, client_node, &client, zappy))
	{
	  send_new_player_to_graph(&zappy->server.clients_graphic, client,
				   zappy->teams_manager.teams.data);
	  return (ZAPPY_NO_ERROR);
	}
    }
  client->client.connection = ZAPPY_DECONNECTION_AFTER_SEND_MSG;
  set_answer_ok_ko(&client->client, FALSE);
  return (ZAPPY_NO_ERROR);
}
