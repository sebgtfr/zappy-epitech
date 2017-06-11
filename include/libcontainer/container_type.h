/*
** container_type.h for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/include
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 18:25:27 2016 Sébastien Le Maire
** Last update Mon Jun 20 17:49:27 2016 
*/

#ifndef CONTAINER_TYPE_H_
# define CONTAINER_TYPE_H_

/*
** All typedef functions
*/
typedef void		(*t_fct_clear)(void *content);
typedef void		(*t_fct_foreach)(void *content);
typedef void		(*t_fct_foreach_data)(void *content, void *data);
typedef int		(*t_fct_compare)(void *content, void const *data);

#endif /* !CONTAINER_TYPE_H_ */
