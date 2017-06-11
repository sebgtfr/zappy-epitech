/*
** resource.c for resource.c in /home/sebastien/unix/PSU_2015_zappy/srcs/server
**
** Made by sebastien
** Login   <sebastien@epitech.net>
**
** Started on  Mon Jun 13 14:52:35 2016 sebastien
** Last update Sun Jun 26 20:08:43 2016 Sébastien Le Maire
*/

#include <stdlib.h>
#include "zappy_server.h"

void		random_ressource(t_world *pos, uint64_t turn, t_bool food)
{
  int		x;
  int		y;
  uint64_t	i;

  i = 0;
  while (i < turn)
    {
      x = rand() % pos->width;
      y = rand() % pos->height;
      if (food)
	add_resource(pos, x, y, ZAPPY_FOOD);
      else
	add_resource(pos, x, y, rand() % (ZAPPY_SIZE_TAB - 1) + 1);
      ++i;
    }
}

void				gen_resources(uint32_t *ticks,
					      t_world *world,
					      uint32_t nb_player,
					      t_list *clients_graph)
{
  uint64_t			size;
  t_item			*node;

  if (*ticks)
    --(*ticks);
  if (!(*ticks) && (nb_player))
    {
      if (nb_player > 1024)
	nb_player = 1024;
      size = (nb_player * 80);
      random_ressource(world, size, TRUE);
      random_ressource(world, size >> 3, FALSE);
      *ticks = 3150;
      node = clients_graph->begin;
      while (node)
	{
	  set_answer_all_case_data((t_client *)node->data, world);
	  node = node->next;
	}
    }
}
