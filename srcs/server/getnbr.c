/*
** getnbr.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sun Jun  5 22:55:34 2016 Sébastien Le Maire
** Last update Fri Jun 24 18:06:32 2016 Sébastien Le Maire
*/

#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "zappy_error.h"

long int			getnbr(char const *str, t_zappy_error *err)
{
  long int			nb;
  char				*endptr;

  nb = 0;
  if (str && str[0])
    {
      errno = 0;
      *err = ZAPPY_NO_ERROR;
      nb = strtol(str, &endptr, 10);
      if (err)
	{
	  if ((str == endptr) || (*endptr))
	    *err = ZAPPY_NOT_NUMBER;
	  if ((errno == ERANGE) && ((nb == LONG_MAX) || (nb == LONG_MIN)))
	    *err = ZAPPY_NUMBER_OVERFLOW;
	}
    }
  else if (err)
    *err = ZAPPY_NOT_NUMBER;
  return (nb);
}
