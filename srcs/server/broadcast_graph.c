/*
** broadcast_graph.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sat Jun 25 16:14:45 2016 Sébastien Le Maire
** Last update Sat Jun 25 16:33:54 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

void				set_msg_all_client(void *client, void *msg)
{
  string_push_back(&((t_client *)client)->msg, (char const *)msg);
}

void				set_msg_broadcast(uint32_t id, char const *msg,
						  t_list *graph)
{
  t_string			str;
  int				size;

  if ((string_init(&str, 16 + strlen(msg)) != EXIT_FAILURE) &&
      ((size = sprintf(str.data, "pbc %u %s\n", id, msg))) >= 0)
    {
      str.data[size] = '\0';
      str.length = size;
      list_foreach_data(graph, set_msg_all_client, str.data);
    }
  string_clear(&str);
}
