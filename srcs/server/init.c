/*
** init.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun  6 13:18:22 2016 Sébastien Le Maire
** Last update Sat Jun 25 19:08:55 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include <string.h>
#include "zappy_server.h"

static t_zappy_command const	g_cmd[NB_CMD] =
  {
    {'p', &cmd_p},
    {'x', &cmd_x},
    {'y', &cmd_y},
    {'t', &cmd_t},
    {'c', &cmd_c},
    {'n', &cmd_n},
    {'h', &cmd_h}
  };

static t_zappy_error		zappy_write_data_server(t_zappy_error err,
							t_zappy *zappy)
{
  unsigned int			i;

  if (err == ZAPPY_NO_ERROR)
    {
      (void)printf("\033[01;32mListening on port %u...\n", zappy->server.port);
      (void)printf("Configuration : Max(%u) WorldX(%u) WorldY(%u) T(%u)\n",
		   zappy->teams_manager.nb_client_max, zappy->world.width,
		   zappy->world.height, zappy->timer.frequency);
      (void)printf("Teams :\n");
      i = 0;
      while (i < zappy->teams_manager.teams.length)
	{
	  (void)printf("\tName(%s) Max(%u)\n",
		       ((t_team *)zappy->teams_manager.teams.data)[i].name,
		       zappy->teams_manager.nb_client_max);
	  ++i;
	}
      (void)printf("Generating world...done\033[00m\n");
    }
  return (err);
}

static t_zappy_error		zappy_load_datas(t_zappy *zappy)
{
  if (!(zappy->teams_manager.teams.length))
    return (ZAPPY_NO_TEAM);
  if (!(zappy->server.port))
    return (ZAPPY_NO_PORT);
  if (!zappy->world.width)
    zappy->world.width = 20;
  if (!zappy->world.height)
    zappy->world.height = 20;
  if (!zappy->timer.frequency)
    zappy->timer.frequency = 100;
  if (!zappy->teams_manager.nb_client_max)
    zappy->teams_manager.nb_client_max = 4;
  if (!init_world(&zappy->world))
    return (ZAPPY_BAD_ALLOC);
  return (zappy_write_data_server(connect_server(&zappy->server), zappy));
}

static void			zappy_init_datas(t_zappy *zappy)
{
  vector_init(&zappy->teams_manager.teams, sizeof(t_team), 0);
  zappy->teams_manager.nb_client_max = 0;
  (void)memset((void *)&zappy->world, 0, sizeof(zappy->world));
  (void)memset((void *)&zappy->server, 0, sizeof(zappy->server));
  zappy->server.socket.fd = -1;
  zappy->timer.frequency = 0;
  list_init(&zappy->server.clients_ia, sizeof(t_client_ia));
  list_init(&zappy->server.clients_graphic, sizeof(t_client_graphic));
  list_init(&zappy->server.eggs, sizeof(t_egg));
}

t_zappy_error			search_command(char const *flag,
					       uint8_t *index)
{
  uint8_t			i;

  if ((flag[0] != '-') || (flag[2]))
    return (ZAPPY_UNKNOWN_CMD);
  i = 0;
  while ((i < NB_CMD) && (g_cmd[i].flag != flag[1]))
    ++i;
  if (index)
    *index = i;
  return ((i == NB_CMD) ? ZAPPY_UNKNOWN_CMD : ZAPPY_NO_ERROR);
}

t_zappy_error			zappy_init(t_zappy *zappy, char **args)
{
  uint32_t			nb_args;
  uint8_t			i;
  t_zappy_error			err;

  nb_args = 0;
  zappy_init_datas(zappy);
  while (*args)
    {
      if ((err = search_command(*args, &i)) != ZAPPY_NO_ERROR)
	return (err);
      ++args;
      if ((err = g_cmd[i].command(zappy, args, &nb_args)) != ZAPPY_NO_ERROR)
	return (err);
      args += nb_args;
    }
  return (zappy_load_datas(zappy));
}
