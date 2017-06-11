/*
** del_list.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/list
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 17:44:16 2016 Sébastien Le Maire
** Last update Wed Jun 15 14:58:53 2016 Sébastien Le Maire
*/

#include "list.h"

void			list_clear(t_list *list, t_fct_clear clear)
{
  t_item		*elem;

  if (list)
    {
      while (list->begin)
	{
	  elem = list->begin;
	  list->begin = list->begin->next;
	  if (clear)
	    clear(elem->data);
	  free(elem);
	}
      list->length = 0;
      list->end = NULL;
    }
}

void			list_pop_front(t_list *list, t_fct_clear clear)
{
  t_item		*tmp;

  if (list && list->begin)
    {
      tmp = list->begin;
      if ((list->begin = list->begin->next))
	list->begin->prev = NULL;
      else
	list->end = NULL;
      if (clear)
	clear(tmp->data);
      free(tmp);
      --(list->length);
    }
}

void			list_pop_back(t_list *list, t_fct_clear clear)
{
  t_item		*tmp;

  if (list && list->end)
    {
      tmp = list->end;
      if ((list->end = list->end->prev))
	list->end->next = NULL;
      else
	list->begin = NULL;
      if (clear)
	clear(tmp->data);
      free(tmp);
      --(list->length);
    }
}

void			list_erase(t_list *list, t_item *item,
				   t_fct_clear clear)
{
  t_item		*next;
  t_item		*prev;

  if (list && list->length && item)
    {
      prev = item->prev;
      next = item->next;
      if (list->begin == item)
	list->begin = list->begin->next;
      if (list->end == item)
	list->end = list->end->prev;
      if (clear)
	clear(item->data);
      free(item);
      if (prev)
	prev->next = next;
      if (next)
	next->prev = prev;
      --(list->length);
    }
}
