/*
** add_string.c for libcontainer in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/libcontainer
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 22 16:31:41 2016 Sébastien Le Maire
** Last update Sun Jun 26 02:22:14 2016 Sébastien Le Maire
*/

#include <string.h>
#include "mystring.h"

int			string_resize(t_string *str, size_t capacity)
{
  if (str)
    {
      if (str->capacity != capacity)
	{
	  if (!(str->data = realloc(str->data, capacity + 2)))
	    {
	      str->capacity = 0;
	      str->length = 0;
	      return (EXIT_FAILURE);
	    }
	  str->capacity = capacity;
	}
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

int			string_push_back(t_string *str, char const *data)
{
  size_t		size;
  size_t		capacity;

  if (str && data)
    {
      size = strlen(data);
      capacity = str->capacity - str->length;
      if ((capacity = (capacity < size) ? (size - capacity) : 0))
	if ((string_resize(str, str->capacity + capacity + 1)) == EXIT_FAILURE)
	  return (EXIT_FAILURE);
      (void)strncpy(str->data + str->length, data, size);
      str->length += size;
      str->data[str->length + 1] = '\0';
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}

int			string_push_back_char(t_string *str, char const c)
{
  size_t		capacity;

  if (str)
    {
      if (!(capacity = (str->capacity - str->length)))
	if ((string_resize(str, str->capacity + 1)) == EXIT_FAILURE)
	  return (EXIT_FAILURE);
      str->data[str->length] = c;
      str->data[str->length + 1] = '\0';
      ++(str->length);
      return (EXIT_SUCCESS);
    }
  return (EXIT_FAILURE);
}
