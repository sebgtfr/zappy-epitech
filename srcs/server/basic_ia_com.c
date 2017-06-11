/*
** basic_ia_com.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun 20 18:40:57 2016 Sébastien Le Maire
** Last update Sat Jun 25 17:10:21 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

void				send_welcome(t_client *client,
					     __attribute__((unused))t_zappy *z)
{
  server_send(client, "BIENVENUE\n", 10);
}

void				send_info_new_player(t_client *client,
						     t_zappy *zappy)
{
  t_team			*team;
  t_client_ia			*ia;
  char				nb[31];
  int				size;
  int				free_slot;

  if (client->type == ZAPPY_CLIENT_IA)
    {
      ia = (t_client_ia *)client;
      team = ((t_team *)(zappy->teams_manager.teams.data)) + ia->player.team;
      free_slot = ((zappy->teams_manager.nb_client_max + team->slot)
		   - team->nb_player);
      if ((size = sprintf(nb, "%d\n%d %d\n", free_slot,
			  zappy->world.width, zappy->world.height)) > 0)
	{
	  nb[size] = '\0';
	  server_send(client, nb, size);
	}
    }
}

void				send_dead(t_client *client,
					  __attribute__((unused))t_zappy *z)
{
  if (client->type != ZAPPY_CLIENT_GRAPHIC)
    {
      client->connection = ((client->connection == ZAPPY_CONNECTION_UNDEFINE) ?
			    ZAPPY_DISCONNECTE :
			    ZAPPY_DECONNECTION_AFTER_SEND_MSG);
      server_send(client, "mort\n", 5);
      string_clear(&client->msg);
    }
}
