/*
** list.h for libmylist in /home/le-mai_s/librairie/librairie_C/libmylist/include
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sun Feb 28 19:06:00 2016 Sébastien Le Maire
** Last update Wed Jun 22 16:48:54 2016 Sébastien Le Maire
*/

#ifndef LIST_H_
# define LIST_H_

# include <stdlib.h>
# include "container_type.h"

struct				s_item
{
  struct s_item			*prev;
  struct s_item			*next;
  char			        data[0];
}				__attribute__((packed));

typedef struct s_item  		t_item;

typedef struct			s_list
{
  t_item			*begin;
  t_item			*end;
  size_t			length;
  size_t			size_item;
}				t_list;

# define LIST_DATA_TO_ITEM(i)	((t_item *)((void *)(i) - (2 * sizeof(void *))))

/*
** List's functions
** initialisation :
*/
void				list_init(t_list *list,
					  size_t const size_item);

/*
** Insert's functions :
*/
int				list_push_back(t_list *list,
					       void const *content);
int				list_push_front(t_list *list,
						void const *content);
int				list_insert(t_list *list,
					    void const *content,
					    size_t const offset);

/*
** Get information to list.
*/
void				list_foreach(t_list const *list,
					     t_fct_foreach foreach);
void				list_foreach_data(t_list const *list,
						  t_fct_foreach_data foreach,
						  void *data);
void				*list_compare(t_list const *list,
					      t_fct_compare cmp,
					      void const *data);

/*
** Delete list's functions.
*/
void				list_pop_front(t_list *list,
					       t_fct_clear clear);
void				list_pop_back(t_list *list,
					      t_fct_clear clear);
void				list_clear(t_list *list,
					   t_fct_clear clear);
void				list_erase(t_list *list, t_item *item,
					   t_fct_clear clear);

#endif /* !LIST_H_ */
