/*
** add_vector.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/vector
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 18:28:26 2016 Sébastien Le Maire
** Last update Thu Jun 23 11:36:59 2016 Sébastien Le Maire
*/

#include <string.h>
#include "vector.h"

int			vector_push_back(t_vector *vector, void const *content)
{
  void			*elem;

  if (vector && content)
    {
      if (vector->capacity && (vector->length < vector->capacity))
	elem = vector->data + (vector->size_item * vector->length);
      else
	{
	  ++vector->capacity;
	  if (!(vector->data = realloc(vector->data,
				       vector->size_item * vector->capacity)))
	    {
	      vector->length = 0;
	      vector->capacity = 0;
	      return (EXIT_FAILURE);
	    }
	  elem = vector->data + (vector->size_item * vector->length);
	}
      ++vector->length;
      (void)memcpy(elem, content, vector->size_item);
    }
  return (EXIT_SUCCESS);
}

int			vector_resize(t_vector *vector, size_t const size,
				      t_fct_clear clear)
{
  if (vector)
    {
      if (!size)
	vector_delete(vector, clear);
      else
	{
	  while (vector->length > size)
	    {
	      --vector->length;
	      if (clear)
		clear(vector->data + (vector->size_item * vector->length));
	    }
	  vector->capacity = size;
	  if (!(vector->data = realloc(vector->data, vector->size_item * size)))
	    return (EXIT_FAILURE);
	}
    }
  return (EXIT_SUCCESS);
}
