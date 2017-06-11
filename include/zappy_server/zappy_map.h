/*
** zappy_map.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Tue Jun  7 10:58:11 2016 Sébastien Le Maire
** Last update Sun Jun 26 18:40:55 2016 Sébastien Le Maire
*/

#ifndef ZAPPY_MAP_H_
# define ZAPPY_MAP_H_

# include <stdint.h>
# include "zappy_bool.h"
# include "zappy_player.h"
# include "zappy_resource.h"
# include "list.h"
# include "mystring.h"

# define MOD(v, m)		((v) % (m) < 0) ? ((v) % (m) + (m)) : (v) % (m)
# define POS(x, y, w)		((y) * (w) + (x))
# define BETWEEN_0_TO_MAX(v, m)	(((v) >= (0)) && ((v) < (m)))

typedef struct			s_zappy_move
{
  t_player			*player;
  t_list			*dest;
  uint32_t			width;
  uint32_t			height;
  t_string			graph;
}				t_zappy_move;

typedef struct			s_zappy_map
{
  int				resources[ZAPPY_SIZE_TAB];
  t_list			list;
}				t_zappy_map;

typedef struct			s_world
{
  uint32_t			width;
  uint32_t		        height;
  t_zappy_map			*map;
}			        t_world;

t_bool				remove_resource(t_world *world, int x, int y,
						t_zappy_resource type);
t_bool				add_resource(t_world *world, int x, int y,
					     t_zappy_resource type);
t_bool				move_player(t_world *w, t_player *p);
void				init_player(t_player *player, t_world *world,
					    int set_pos);
void				rotate_player(t_player *p, t_player_dir dir);
void				expulse_players(t_world *w, t_player *p,
						t_list *graph);
void				random_ressource(t_world *pos, uint64_t turn, t_bool food);
void				gen_resources(uint32_t *ticks,
					      t_world *world,
					      uint32_t nb_player,
					      t_list *clients_graph);

#endif /* !ZAPPY_MAP_H_ */
