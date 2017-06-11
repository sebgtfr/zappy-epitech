/*
** del_string.c for libcontainer in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/libcontainer
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 22 16:44:57 2016 Sébastien Le Maire
** Last update Wed Jun 22 21:13:03 2016 Sébastien Le Maire
*/

#include "mystring.h"

void			string_clear(t_string *str)
{
  if (str && str->data)
    {
      free(str->data);
      str->data = NULL;
      str->length = 0;
      str->capacity = 0;
    }
}
