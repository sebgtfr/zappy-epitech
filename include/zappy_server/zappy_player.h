/*
** zappy_player.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 15 15:58:31 2016 Sébastien Le Maire
** Last update Sat Jun 25 20:19:23 2016 Sébastien Le Maire
*/

#ifndef ZAPPY_PLAYER_H_
# define ZAPPY_PLAYER_H_

# include <stdint.h>
# include "zappy_action.h"
# include "zappy_resource.h"

typedef uint32_t       		t_inventory[ZAPPY_SIZE_TAB];

typedef enum			e_player_dir
  {
				UP = 1,
			        RIGHT,
				DOWN,
			        LEFT
  }				t_player_dir;

typedef enum			e_player_action
  {
				ZAPPY_PLAYER_BEGIN = 0,
				ZAPPY_PLAYER_FORWARD = ZAPPY_PLAYER_BEGIN,
				ZAPPY_PLAYER_RIGHT,
				ZAPPY_PLAYER_LEFT,
				ZAPPY_PLAYER_SEE,
				ZAPPY_PLAYER_INVENTORY,
				ZAPPY_PLAYER_TAKE,
				ZAPPY_PLAYER_THROW,
				ZAPPY_PLAYER_EXPULSE,
				ZAPPY_PLAYER_BROADCAST,
				ZAPPY_PLAYER_SPELL,
				ZAPPY_PLAYER_FORK,
				ZAPPY_PLAYER_CONNECT_NBR,
				ZAPPY_PLAYER_NO_ACTION
  }				t_player_action;

typedef struct			s_egg
{
  int				x;
  int				y;
  int				tick;
  int				id;
  int				team;
}				t_egg;

typedef struct			s_player
{
  int				team;
  int				level;
  uint8_t		        hp;
  t_inventory			inventory;
  int				x;
  int				y;
  int				startx;
  int				starty;
  t_player_dir			facing;
  int				expulsed_from;
  int				nb_orders;
  int				id_order;
  t_action			action[MAX_ORDERS + 1];
  t_player_action		cur_action;
  unsigned int			time_action;
}				t_player;

#endif /* !ZAPPY_PLAYER_H_ */
