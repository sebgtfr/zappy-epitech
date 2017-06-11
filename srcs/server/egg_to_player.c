/*
** egg_to_player.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sat Jun 25 17:18:12 2016 Sébastien Le Maire
** Last update Sun Jun 26 21:35:51 2016 
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

static int	       		check_ghost(void *content, void const *data)
{
  t_client_ia			*ia;

  ia = (t_client_ia *)content;
  if ((ia->client.connection == ZAPPY_CONNECTION_UNDEFINE) &&
      (ia->client.socket.fd == -1) && (ia->player.team == *(int const *)data))
    return (0);
  return (1);
}

uint8_t				egg_to_player(t_client_ia *new_ia,
					      t_list *list_ia)
{
  t_client_ia			*ia_ghost;
  uint32_t     			id_egg;

  if ((ia_ghost = (t_client_ia *)list_compare(list_ia, check_ghost,
					      &new_ia->player.team)))
    {
      id_egg = ia_ghost->client.id_egg;
      (void)memcpy((void *)ia_ghost, (void *)new_ia, sizeof(t_client));
      ia_ghost->client.id_egg = id_egg;
      new_ia->client.id_egg = id_egg;
      return (2);
    }
  return (1);
}

static int			check_old_player_on_egg(void *content,
							void const *data)
{
  t_client const		*old_ia;
  t_client_ia			*ia;

  ia = (t_client_ia *)content;
  old_ia = (t_client const *)data;
  if ((ia->client.id_egg) && (!ia->client.id) &&
      ((void *)old_ia != (void *)ia) && (old_ia->id_egg == ia->client.id_egg))
    return (0);
  return (1);
}

void				recup_player_from_egg(t_client_ia **old_ptr,
						      t_list *list_ia)
{
  *old_ptr = (t_client_ia *)list_compare(list_ia, check_old_player_on_egg,
					 *old_ptr);
}

void				set_msg_egg_player(t_string *msg,
						   uint32_t id)
{
  char				data[16];
  unsigned int			size;

  if ((size = sprintf(data, "ebo %u\n", id)) > 0)
    {
      data[size] = '\0';
      string_push_back(msg, data);
    }
}
