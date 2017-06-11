/*
** cmd_p_x_y_t_c.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun  6 12:32:45 2016 Sébastien Le Maire
** Last update Fri Jun 24 18:13:53 2016 Sébastien Le Maire
*/

#include <limits.h>
#include "zappy_server.h"

t_zappy_error			cmd_p(t_zappy *zappy, char **args,
				      unsigned int *nb_args)
{
  t_zappy_error			err;
  long int			val;

  *nb_args = 1;
  val = getnbr(args[0], &err);
  if ((val <= 0) || (val > USHRT_MAX))
    return (ZAPPY_INVALID_PORT);
  zappy->server.port = (uint16_t)val;
  return (err);
}

t_zappy_error			cmd_x(t_zappy *zappy, char **args,
				      unsigned int *nb_args)
{
  t_zappy_error			err;

  *nb_args = 1;
  zappy->world.width = getnbr(args[0], &err);
  if ((err == ZAPPY_NO_ERROR) && (!zappy->world.width))
    err = ZAPPY_INVALID_MAP;
  return (err);
}

t_zappy_error			cmd_y(t_zappy *zappy, char **args,
				      unsigned int *nb_args)
{
  t_zappy_error			err;

  *nb_args = 1;
  zappy->world.height = getnbr(args[0], &err);
  if ((err == ZAPPY_NO_ERROR) && (!zappy->world.height))
    err = ZAPPY_INVALID_MAP;
  return (err);
}

t_zappy_error			cmd_t(t_zappy *zappy, char **args,
				      unsigned int *nb_args)
{
  t_zappy_error			err;

  *nb_args = 1;
  zappy->timer.frequency = getnbr(args[0], &err);
  if ((err == ZAPPY_NO_ERROR) &&
      (((!zappy->timer.frequency)) || (zappy->timer.frequency > 1000000000)))
    err = ZAPPY_INVALID_TIMER;
  return (err);
}

t_zappy_error			cmd_c(t_zappy *zappy, char **args,
				      unsigned int *nb_args)
{
  t_zappy_error			err;

  *nb_args = 1;
  zappy->teams_manager.nb_client_max = getnbr(args[0], &err);
  if ((err == ZAPPY_NO_ERROR) && (!zappy->teams_manager.nb_client_max))
    err = ZAPPY_INVALID_MAX_CLIENTS;
  return (err);
}
