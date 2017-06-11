/*
** graph_expulse.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sat Jun 25 21:15:44 2016 Sébastien Le Maire
** Last update Sun Jun 26 02:06:11 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

void				msg_expulse_exe(t_string *msg, uint32_t id)
{
  char				data[20];
  unsigned int			size;

  if ((size = sprintf(data, "pex %u\n", id)) > 0)
    {
      data[size] = '\0';
      string_init(msg, size + 2);
      string_push_back(msg, data);
    }
}

void			        msg_expulse_pos_player(t_string *msg,
						       t_client_ia *ia)
{
  char				data[40];
  unsigned int			size;

  if ((size = sprintf(data, "ppo %u %d %d %d\n", ia->client.id, ia->player.x,
		      ia->player.y, ia->player.facing)) > 0)
    {
      data[size] = '\0';
      string_push_back(msg, data);
    }
}
