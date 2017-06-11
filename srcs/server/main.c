/*
** main.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon May 23 23:02:19 2016 Sébastien Le Maire
** Last update Sat Jun 25 21:31:18 2016 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "zappy_server.h"

static void		       	delete_zappy(t_zappy *zappy)
{
  unsigned int			size;
  unsigned int			pos;
  t_zappy_map			*map;

  if (zappy)
    {
      vector_delete(&zappy->teams_manager.teams, NULL);
      if (zappy->world.map)
	{
	  size = zappy->world.width * zappy->world.height;
	  pos = 0;
	  map = zappy->world.map;
	  while (pos < size)
	    {
	      list_clear(&map->list, NULL);
	      ++(map);
	      ++pos;
	    }
	  free(zappy->world.map);
	}
      delete_socket(&zappy->server.socket);
      list_clear(&zappy->server.clients_ia, &close_clients);
      list_clear(&zappy->server.clients_graphic, &close_clients);
      list_clear(&zappy->server.eggs, NULL);
    }
}

int				main(int ac, char **av)
{
  t_zappy			zappy;
  int				ret;

  if (ac > 1)
    {
      srand(time(NULL));
      if ((((ret = zappy_error(zappy_init(&zappy, av + 1))) == EXIT_SUCCESS) &&
	   ((ret = zappy_error(launch_server(&zappy))) == EXIT_SUCCESS)) ||
	  (ret == (EXIT_SUCCESS + EXIT_FAILURE + 2)))
	ret = EXIT_SUCCESS;
      delete_zappy(&zappy);
      return (ret);
    }
  else
    (void)fprintf(stderr, "Use -h for help !\n");
  return (EXIT_FAILURE);
}
