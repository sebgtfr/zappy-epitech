/*
** answer_init_graph.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun 23 21:38:59 2016 Sébastien Le Maire
** Last update Sun Jun 26 21:01:01 2016 
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

void				set_answer_map_size(t_client *client,
						    t_world *world)
{
  char				map_size[25];
  int				size;

  if (client->type == ZAPPY_CLIENT_GRAPHIC)
    {
      if ((size = sprintf(map_size, "msz %u %u\n",
			  world->width, world->height)) > 0)
	{
	  map_size[size] = '\0';
	  string_push_back(&client->msg, map_size);
	}
    }
}

void				set_answer_data_case(t_client *client,
						     t_world *world,
						     unsigned int x,
						     unsigned int y)
{
  if (client->type == ZAPPY_CLIENT_GRAPHIC)
    push_msg_data_case(&client->msg, x, y,
		       (world->map + POS(x, y, world->width)));
}

void				set_answer_all_case_data(t_client *client,
							 t_world *world)
{
  unsigned int			x;
  unsigned int			y;

  if (client->type == ZAPPY_CLIENT_GRAPHIC)
    {
      x = 0;
      if (string_resize(&client->msg, client->msg.capacity +
			((world->height * world->width) * 24)) == EXIT_FAILURE)
	return ;
      while (x < world->height)
	{
	  y = 0;
	  while (y < world->width)
	    {
	      set_answer_data_case(client, world, x, y);
	      ++y;
	    }
	  ++x;
	}
    }
}

void				set_answer_teams_name(t_client *client,
						      t_vector *teams)
{
  unsigned int			i;
  unsigned int			size;
  t_team			*team;

  if (client->type == ZAPPY_CLIENT_GRAPHIC)
    {
      i = 0;
      team = ((t_team *)(teams->data));
      while (i++ < teams->length)
	{
	  size = strlen(team->name) + 5;
	  if ((string_resize(&client->msg, client->msg.capacity + size + 1))
	      == EXIT_SUCCESS)
	    {
	      string_push_back(&client->msg, "tna ");
	      string_push_back(&client->msg, team->name);
	      string_push_back_char(&client->msg, '\n');
	    }
	  ++(team);
	}
    }
}

void			        set_answer_init_graphic(t_client *client,
							t_zappy *zappy)
{
  if (client->type == ZAPPY_CLIENT_GRAPHIC)
    {
      set_answer_map_size(client, &zappy->world);
      set_answer_time(client, &zappy->timer);
      set_answer_all_case_data(client, &zappy->world);
      set_answer_teams_name(client, &zappy->teams_manager.teams);
      set_msg_all_new_player(&zappy->server.clients_ia, &client->msg,
			     (t_team *)zappy->teams_manager.teams.data);
    }
}
