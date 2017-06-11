/*
** init_list.c for libcontainer in /home/le-mai_s/librairie/librairie_C/libcontainer/srcs/list
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 17:42:55 2016 Sébastien Le Maire
** Last update Mon Jun 20 16:23:24 2016 Sébastien Le Maire
*/

#include "list.h"

void			list_init(t_list *list, size_t const size_item)
{
  if (list)
    {
      list->begin = NULL;
      list->end = NULL;
      list->length = 0;
      list->size_item = size_item;
    }
}
