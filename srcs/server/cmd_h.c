/*
** cmd_h.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun 13 10:16:53 2016 Sébastien Le Maire
** Last update Mon Jun 13 11:37:01 2016 Sébastien Le Maire
*/

#include <stdio.h>
#include "zappy_server.h"

static char const		*commmands[NB_CMD] =
  {
    "-p [PORT]\t: Port number",
    "-x [WIDTH]\t: Width of the world",
    "-y [HEIGHT]\t: Height of the world",
    "-n [TEAM ...]\t: teams' name",
    "-c [CLIENTS]\t: Number of clients allowed at the begining of the game",
    "-t [TIME]\t: Time delay of execution of the actions",
    "-h\t\t: Show all commands"
  };

t_zappy_error			cmd_h(__attribute__((unused))t_zappy *zappy,
				      __attribute__((unused))char **args,
				      __attribute__((unused))unsigned *nb_args)
{
  unsigned int			i;

  i = 0;
  (void)printf("USAGE :\n");
  while (i < NB_CMD)
    {
      (void)printf("%8c%s.\n", ' ', commmands[i]);
      ++i;
    }
  return (ZAPPY_EXIT_NO_ERROR);
}
