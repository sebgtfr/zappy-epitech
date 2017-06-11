/*
** world_manage.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Tue Jun 21 10:49:10 2016 Sébastien Le Maire
** Last update Sun Jun 26 18:53:41 2016 Sébastien Le Maire
*/

#include <string.h>
#include "zappy_server.h"
#include "client_action.h"

static t_zappy_cmd_action const	g_cmd_action[ZAPPY_PLAYER_NO_ACTION] =
  {
    {"avance", 7, FALSE, NULL, avance},
    {"droite", 7, FALSE, NULL, right},
    {"gauche", 7, FALSE, NULL, left},
    {"voir", 7, FALSE, NULL, voir},
    {"inventaire", 7, FALSE, NULL, inventaire},
    {"prend", 7, TRUE, NULL, take},
    {"pose", 7, TRUE, NULL, put},
    {"expulse", 7, FALSE, NULL, expulse},
    {"broadcast", 7, TRUE, NULL, &broadcast},
    {"incantation", 300, FALSE, incantation_start, incantation_end},
    {"fork", 42, FALSE, fatherfork, motherfork},
    {"connect_nbr", 0, FALSE, NULL, connect_nbr},
  };

t_bool				init_world(t_world *world)
{
  uint64_t			size;
  uint64_t			pos;
  t_zappy_map			*map;

  size = world->width * world->height;
  if (!(world->map = malloc(sizeof(*(world->map)) * size)))
    return (FALSE);
  map = world->map;
  pos = 0;
  while (pos < size)
    {
      (void)memset(map->resources, 0, sizeof(map->resources));
      list_init(&map->list, sizeof(t_player *));
      ++(map);
      ++pos;
    }
  size = size << 1;
  random_ressource(world, size, FALSE);
  random_ressource(world, size, TRUE);
  return (TRUE);
}

static void			get_cmd_action(t_client_ia *ia, t_zappy *zappy)
{
  t_action			action;
  t_player_action		play_action;

  if (get_action(&ia->player, &action))
    {
      play_action = ZAPPY_PLAYER_BEGIN;
      while ((play_action < ZAPPY_PLAYER_NO_ACTION) &&
	     (strcmp(g_cmd_action[play_action].order, action.order)))
	++play_action;
      if ((play_action >= ZAPPY_PLAYER_NO_ACTION) ||
	  (BOOL(action.arg[0]) != (g_cmd_action[play_action].have_arg)))
	set_answer_ok_ko(&ia->client, FALSE);
      else
	{
	  ia->player.cur_action = play_action;
	  ia->player.time_action = g_cmd_action[play_action].time;
	  if (g_cmd_action[play_action].init)
	    g_cmd_action[play_action].init(ia, zappy);
	}
    }
}

void				world_manage(t_client_ia *ia, t_zappy *zappy)
{
  if (hp_management(ia, &zappy->server.clients_graphic,
		    &zappy->teams_manager.teams))
    {
      if (ia->player.time_action)
	--(ia->player.time_action);
      if (ia->player.cur_action >= ZAPPY_PLAYER_NO_ACTION)
	get_cmd_action(ia, zappy);
      if ((ia->player.cur_action < ZAPPY_PLAYER_NO_ACTION) &&
	  (!ia->player.time_action))
	{
	  if (g_cmd_action[ia->player.cur_action].action)
	    g_cmd_action[ia->player.cur_action].action(ia, zappy);
	  ia->player.cur_action = ZAPPY_PLAYER_NO_ACTION;
	}
    }
}
