/*
** vector.h for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/include
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 18:02:04 2016 Sébastien Le Maire
** Last update Wed Jun 22 16:48:53 2016 Sébastien Le Maire
*/

#ifndef VECTOR_H_
# define VECTOR_H_

# include <stdlib.h>
# include "container_type.h"

typedef struct			s_vector
{
  size_t			length;
  size_t			capacity;
  size_t		        size_item;
  void				*data;
}				t_vector;

/*
** Vector's functions
** initialisation :
*/
int				vector_init(t_vector *vector,
					    size_t const size_item,
					    size_t const capacity);

/*
** Add elements vector's functions
*/
int				vector_push_back(t_vector *vector,
						 void const *content);
int				vector_resize(t_vector *vector,
					      size_t const size,
					      t_fct_clear clear);

/*
** Delete vector's functions
*/
void				vector_pop_back(t_vector *vector,
						t_fct_clear clear);
void				vector_clear(t_vector *vector,
					     t_fct_clear clear);
void				vector_delete(t_vector *vector,
					      t_fct_clear clear);

/*
** Get information to vector.
*/
void				vector_foreach(t_vector const *vector,
					       t_fct_foreach foreach);
void				*vector_compare(t_vector const *vector,
						t_fct_compare cmp,
						void const *data);

#endif /* !VECTOR_H_ */
