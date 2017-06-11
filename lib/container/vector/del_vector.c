/*
** del_vector.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/vector
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 18:42:25 2016 Sébastien Le Maire
** Last update Wed Jun 22 16:49:26 2016 Sébastien Le Maire
*/

#include "vector.h"

void			vector_pop_back(t_vector *vector, t_fct_clear clear)
{
  if (vector && vector->data && vector->length)
    {
      --vector->length;
      if (clear)
	clear(vector->data + (vector->length * vector->size_item));
    }
}

void			vector_clear(t_vector *vector, t_fct_clear clear)
{
  void			*elem;
  size_t		i;

  if (vector)
    {
      if (clear && vector->data)
	{
	  elem = vector->data;
	  i = 0;
	  while (i < vector->length)
	    {
	      clear(elem);
	      ++i;
	    }
	}
      vector->length = 0;
    }
}

void			vector_delete(t_vector *vector, t_fct_clear clear)
{
  if (vector)
    {
      vector_clear(vector, clear);
      if (vector->data)
	{
	  free(vector->data);
	  vector->data = NULL;
	}
      vector->capacity = 0;
    }
}
