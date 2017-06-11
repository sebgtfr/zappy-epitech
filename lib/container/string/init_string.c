/*
** init_string.c for libcontainer in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/libcontainer
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 22 16:21:57 2016 Sébastien Le Maire
** Last update Sun Jun 26 02:17:16 2016 Sébastien Le Maire
*/

#include <string.h>
#include "mystring.h"

int				string_char_copy(t_string *str,
						 char const *data)
{
  if (str)
    {
      if (data)
	{
	  str->length = strlen(data);
	  str->capacity = str->length;
	  if (!(str->data = strdup(data)))
	    return (EXIT_FAILURE);
	}
      else
	{
	  str->length = 0;
	  str->capacity = 0;
	  str->data = NULL;
	}
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

int				string_copy(t_string *str,
					    t_string const *data)
{
  if (str)
    {
      if (data && data->data)
	{
	  str->length = data->length;
	  str->capacity = data->capacity;
	  if (!(str->data = strdup(data->data)))
	    return (EXIT_FAILURE);
	}
      else
	{
	  str->length = 0;
	  str->capacity = 0;
	  str->data = NULL;
	}
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

int				string_init(t_string *str, size_t capacity)
{
  if (str)
    {
      if ((str->capacity = capacity))
	{
	  if (!(str->data = calloc(str->capacity + 1, sizeof(char))))
	    return (EXIT_FAILURE);
	}
      else
	str->data = NULL;
      str->length = 0;
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}
