/*
** time_graph_com.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 22 13:50:14 2016 Sébastien Le Maire
** Last update Fri Jun 24 19:13:00 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"

void			        set_answer_time(t_client *client,
						t_time *timer)
{
  char				data_send[15];
  unsigned int			size;

  if (client->type == ZAPPY_CLIENT_GRAPHIC)
    if ((size = sprintf(data_send, "sgt %u\n", timer->frequency)) > 0)
      string_push_back(&client->msg, data_send);
}

void				cmd_graph_time(t_client *client,
					       t_zappy *zappy,
					       char const *args)
{
  uint32_t			frequency;
  t_zappy_error			err;

  if (args[0])
    {
      frequency = getnbr(args, &err);
      if ((err == ZAPPY_NO_ERROR) && (frequency) && (frequency <= 1000000000))
	change_frequency(&zappy->timer, frequency);
      else
	{
	  string_push_back(&client->msg, "sbp\n");
	  return ;
	}
    }
  set_answer_time(client, &zappy->timer);
}
