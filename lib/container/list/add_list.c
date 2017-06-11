/*
** add_list.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/list
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 17:43:08 2016 Sébastien Le Maire
** Last update Thu Jun  2 18:31:46 2016 Sébastien Le Maire
*/

#include <string.h>
#include "list.h"

static t_item  		*list_new_item(void const *content,
				       size_t const size)
{
  t_item		*elem;

  if ((!(elem = malloc(sizeof(*elem) + size))))
    return (NULL);
  (void)memcpy((void *)elem->data, content, size);
  elem->prev = NULL;
  elem->next = NULL;
  return (elem);
}

int			list_push_back(t_list *list,
				       void const *content)
{
  t_item		*elem;

  if ((!list) || (!content) ||
      (!(elem = list_new_item(content, list->size_item))))
    return (EXIT_FAILURE);
  if (!list->begin)
    list->begin = elem;
  else
    {
      list->end->next = elem;
      elem->prev = list->end;
    }
  list->end = elem;
  ++(list->length);
  return (EXIT_SUCCESS);
}

int			list_push_front(t_list *list,
					void const *content)
{
  t_item		*elem;

  if ((!list) || (!(elem = list_new_item(content, list->size_item))))
    return (EXIT_FAILURE);
  if (!list->end)
    list->end = elem;
  elem->next = list->begin;
  if (list->begin)
    list->begin->prev = elem;
  list->begin = elem;
  ++(list->length);
  return (EXIT_SUCCESS);
}

static t_item		*list_get_item_at_offset(t_list *list,
						 size_t const offset)
{
  size_t		i;
  t_item		*elem;

  i = 0;
  elem = list->begin;
  while ((elem) && (i < offset))
    {
      elem = elem->next;
      ++i;
    }
  return (elem);
}

int			list_insert(t_list *list,
				    void const *content,
				    size_t const offset)
{
  t_item		*elem;
  t_item		*current;

  if ((!list) || (offset > list->length))
    return (EXIT_FAILURE);
  if (!offset)
    return (list_push_front(list, content));
  else if (offset == (list->length - 1))
    return (list_push_back(list, content));
  else
    {
      if ((!(current = list_get_item_at_offset(list, offset))) ||
	  (!(elem = list_new_item(list, list->size_item))))
	return (EXIT_FAILURE);
      ++(list->length);
      elem->next = current;
      elem->prev = current->prev;
      current->prev->next = elem;
      current->prev = elem;
    }
  return (EXIT_SUCCESS);
}
