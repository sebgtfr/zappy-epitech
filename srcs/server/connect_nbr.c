/*
** connect_nbr.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Sat Jun 25 17:16:47 2016
** Last update Sat Jun 25 23:42:10 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

void		connect_nbr(t_client_ia *client, t_zappy *zappy)
{
  t_team	*team;
  int		free_slot;
  char		nb[10];

  team = ((t_team *)(zappy->teams_manager.teams.data)) + client->player.team;
  free_slot = ((zappy->teams_manager.nb_client_max + team->slot)
	       - team->nb_player);
  sprintf(nb, "%d\n", free_slot);
  string_push_back(&(client->client.msg), nb);
}
