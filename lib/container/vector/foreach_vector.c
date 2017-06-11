/*
** foreach_vector.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/vector
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 18:42:13 2016 Sébastien Le Maire
** Last update Wed Jun 22 16:49:22 2016 Sébastien Le Maire
*/

#include "vector.h"

void			vector_foreach(t_vector const *vector,
				       t_fct_foreach foreach)
{
  void			*elem;
  size_t		i;

  if (vector && foreach)
    {
      elem = vector->data;
      i = 0;
      while (i < vector->length)
	{
	  foreach(elem);
	  elem += vector->size_item;
	  ++i;
	}
    }
}

void			*vector_compare(t_vector const *vector,
					t_fct_compare cmp, void const *data)
{
  void			*elem;
  size_t		i;

  if (vector && cmp)
    {
      elem = vector->data;
      i = 0;
      while (i < vector->length)
	{
	  if (!(cmp(elem, data)))
	    return (elem);
	  elem += vector->size_item;
	  ++i;
	}
    }
  return (NULL);
}
