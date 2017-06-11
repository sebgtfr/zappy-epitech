/*
** map.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Thu Jun 16 15:00:48 2016
** Last update Sun Jun 26 21:33:52 2016 
*/

#include "zappy_map.h"

int	cmp_ptr(void *content, void const *data)
{
  return (!(*(t_player **)content == *(t_player **)data));
}

t_bool				remove_resource(t_world *world, int x, int y,
						t_zappy_resource type)
{
  if (BETWEEN_0_TO_MAX(type, ZAPPY_SIZE_TAB) &&
      BETWEEN_0_TO_MAX(x, (int)world->width) &&
      BETWEEN_0_TO_MAX(y, (int)world->height) &&
      (world->map[POS(x, y, world->width)].resources[type] > 0))
    {
      --(world->map[POS(x, y, world->width)].resources[type]);
      return (TRUE);
    }
  return (FALSE);
}

t_bool				add_resource(t_world *world, int x, int y,
					     t_zappy_resource type)
{
  if (BETWEEN_0_TO_MAX(type, ZAPPY_SIZE_TAB) &&
      BETWEEN_0_TO_MAX(x, (int)world->width) &&
      BETWEEN_0_TO_MAX(y, (int)world->height))
    {
      ++(world->map[POS(x, y, world->width)].resources[type]);
      return (TRUE);
    }
  return (FALSE);
}

t_bool				move_player(t_world *w, t_player *p)
{
  void				*tmp;

  tmp = list_compare(&(w->map[POS(p->x, p->y, w->width)].list), cmp_ptr, &p);
  if (!tmp)
    return (FALSE);
  list_erase(&(w->map[POS(p->x, p->y, w->width)].list),
	     LIST_DATA_TO_ITEM(tmp), NULL);
  if (p->facing == RIGHT)
    p->x = MOD(p->x + 1, (int)(w->width));
  else if (p->facing == LEFT)
    p->x = MOD(p->x - 1, (int)(w->width));
  else if (p->facing == UP)
    p->y = MOD(p->y - 1, (int)(w->height));
  else
    p->y = MOD(p->y + 1, (int)(w->height));
  list_push_back(&(w->map[POS(p->x, p->y, w->width)].list), &p);
  return (TRUE);
}

void				rotate_player(t_player *p, t_player_dir dir)
{
  t_player_dir new;

  new = (dir == LEFT) ? (p->facing - 1) : (p->facing + 1);
  if (new == 5)
    p->facing = UP;
  else if (new == 0)
    p->facing = LEFT;
  else
    p->facing = new;
}
