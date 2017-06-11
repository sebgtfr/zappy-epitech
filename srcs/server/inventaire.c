/*
** inventaire.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy/srcs/test
** 
** Made by 
** Login   <terrea_l@epitech.net>
** 
** Started on  Fri Jun 24 00:41:41 2016 
** Last update Fri Jun 24 11:55:43 2016 
*/

#include <stdio.h>

#include "zappy_map.h"
#include "client_action.h"
#include "mystring.h"

void		inventaire_fin(t_player *player, t_string *str)
{
  char		nb[10];

  string_push_back(str, ", linemate ");
  sprintf(nb, "%d", player->inventory[ZAPPY_LINEMATE]);
  string_push_back(str, nb);
  string_push_back(str, ", deraumere ");
  sprintf(nb, "%d", player->inventory[ZAPPY_DERAUMERE]);
  string_push_back(str, nb);
  string_push_back(str, ", thystame ");
  sprintf(nb, "%d", player->inventory[ZAPPY_THYSTAME]);
  string_push_back(str, nb);
  string_push_back(str, ", mendiane ");
  sprintf(nb, "%d", player->inventory[ZAPPY_MENDIANE]);
  string_push_back(str, nb);
  string_push_back(str, "}\n");
}

void		inventaire(t_client_ia *client, t_zappy __attribute__ ((unused)) *zappy)
{
  t_string	*str;
  char		nb[10];
  t_player	*player;

  player = &(client->player);
  str = &(client->client.msg);
  string_push_back_char(str, '{');
  string_push_back(str, "nourriture ");
  sprintf(nb, "%d", player->inventory[ZAPPY_FOOD]);
  string_push_back(str, nb);
  string_push_back(str, ", sibur ");
  sprintf(nb, "%d", player->inventory[ZAPPY_SIBUR]);
  string_push_back(str, nb);
  string_push_back(str, ", phiras ");
  sprintf(nb, "%d", player->inventory[ZAPPY_PHIRAS]);
  string_push_back(str, nb);
  inventaire_fin(player, str);
}
