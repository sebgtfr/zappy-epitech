/*
** cmd_init_graph.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Fri Jun 24 17:56:01 2016 Sébastien Le Maire
** Last update Fri Jun 24 19:20:18 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy_server.h"

void				cmd_graph_map(t_client *client, t_zappy *zappy,
					      __attribute__((unused))
					      char const *args)
{
  set_answer_map_size(client, &zappy->world);
}

void				cmd_graph_case(t_client *client,
					       t_zappy *zappy,
					       char const *args)
{
  unsigned int			x;
  unsigned int			y;
  unsigned int			i;
  t_zappy_error			err;

  i = 0;
  while (args[i] && (args[i] >= '0' && args[i] <= '9'))
    ++i;
  if ((i) && (args[i] == ' ') && (args[i + 1] >= '0' && args[i + 1] <= '9'))
    {
      ++i;
      x = getnbr(args, &err);
      if (err != ZAPPY_NUMBER_OVERFLOW)
	{
	  y = getnbr(args + i, &err);
	  if ((err == ZAPPY_NO_ERROR) && (x < zappy->world.width) &&
	      (y < zappy->world.height))
	    {
	      set_answer_data_case(client, &zappy->world, x, y);
	      return ;
	    }
	}
    }
  string_push_back(&client->msg, "sbp\n");
}

void				cmd_graph_all_case(t_client *client,
						   t_zappy *zappy,
						   __attribute__((unused))
						   char const *args)
{
  set_answer_all_case_data(client, &zappy->world);
}


void				cmd_graph_teams(t_client *client,
						t_zappy *zappy,
						__attribute__((unused))
						char const *args)
{
  set_answer_teams_name(client, &zappy->teams_manager.teams);
}
