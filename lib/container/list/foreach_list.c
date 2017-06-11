/*
** foreach_list.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/list
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 17:44:39 2016 Sébastien Le Maire
** Last update Wed Jun 22 12:09:53 2016 
*/

#include "list.h"

void			list_foreach(t_list const *list, t_fct_foreach foreach)
{
  t_item		*elem;

  if (list && foreach)
    {
      elem = list->begin;
      while (elem)
	{
	  foreach((void *)elem->data);
	  elem = elem->next;
	}
    }
}

void			list_foreach_data(t_list const *list,
					  t_fct_foreach_data foreach,
					  void *data)
{
  t_item		*elem;

  if (list && foreach)
    {
      elem = list->begin;
      while (elem)
	{
	  foreach((void *)elem->data, data);
	  elem = elem->next;
	}
    }
}

void			*list_compare(t_list const *list, t_fct_compare cmp,
				      void const *data)
{
  t_item		*elem;

  if (list && cmp)
    {
      elem = list->begin;
      while (elem)
	{
	  if (!(cmp((void *)elem->data, data)))
	    return ((void *)elem->data);
	  elem = elem->next;
	}
    }
  return (NULL);
}
