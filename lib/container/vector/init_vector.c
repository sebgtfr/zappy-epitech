/*
** init_vector.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/vector
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 18:05:33 2016 Sébastien Le Maire
** Last update Wed Jun 22 16:49:09 2016 Sébastien Le Maire
*/

#include "vector.h"

int			vector_init(t_vector *vector, size_t const size_item,
				    size_t const capacity)
{
  if (vector)
    {
      vector->length = 0;
      vector->size_item = size_item;
      vector->capacity = capacity;
      vector->data = ((!capacity) ? NULL :
		      (malloc(sizeof(size_item) * capacity)));
      if (capacity && !vector->data)
	return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
