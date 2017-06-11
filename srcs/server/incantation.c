/*
** incantation_start.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy/srcs
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Fri Jun 24 12:02:59 2016
** Last update Sun Jun 26 16:23:48 2016 Sébastien Le Maire
*/

#include "client_action.h"
#include "zappy_map.h"

void			check_players(void *content, void *param)
{
  t_player		*player;
  t_incantation_data	*data;

  player = *(t_player **)content;
  data = (t_incantation_data *)param;
  if (player->level != data->lvl)
    data->can_up = 0;
}

int			get_valid_players(t_zappy_map *m, int level)
{
  t_incantation_data	data;

  data.lvl = level;
  data.can_up = 1;
  list_foreach_data(&(m->list), check_players, &data);
  if (data.can_up)
    {
      if ((level == 1 && m->list.length == 1) ||
	  (level == 2 && m->list.length == 2) ||
	  (level == 3 && m->list.length == 2) ||
	  (level == 4 && m->list.length == 4) ||
	  (level == 5 && m->list.length == 4) ||
	  (level == 6 && m->list.length == 6) ||
	  (level == 7 && m->list.length == 6))
	return (1);
    }
  return (0);
}

int		check_other_levels(t_zappy_map *m, int lvl, t_player *player)
{
  if (player)
    set_start_pos(player);
  return ((lvl == 4 && m->resources[ZAPPY_LINEMATE] == 1 &&
	   m->resources[ZAPPY_DERAUMERE] == 1 &&
	   m->resources[ZAPPY_SIBUR] == 2 && m->resources[ZAPPY_PHIRAS] == 1 &&
	   m->resources[ZAPPY_MENDIANE] == 0 &&
	   m->resources[ZAPPY_THYSTAME] == 0) ||
	  (lvl == 5 && m->resources[ZAPPY_LINEMATE] == 1 &&
	   m->resources[ZAPPY_DERAUMERE] == 2 &&
	   m->resources[ZAPPY_SIBUR] == 1 &&
	   m->resources[ZAPPY_MENDIANE] == 3 &&
	   m->resources[ZAPPY_PHIRAS] == 0 &&
	   m->resources[ZAPPY_THYSTAME] == 0) ||
	  (lvl == 6 && m->resources[ZAPPY_LINEMATE] == 1 &&
	   m->resources[ZAPPY_DERAUMERE] == 2 &&
	   m->resources[ZAPPY_SIBUR] == 3 &&
	   m->resources[ZAPPY_MENDIANE] == 0 &&
	   m->resources[ZAPPY_PHIRAS] == 1 &&
	   m->resources[ZAPPY_THYSTAME] == 0) ||
	  (lvl == 7 && m->resources[ZAPPY_LINEMATE] == 2 &&
	   m->resources[ZAPPY_DERAUMERE] == 2 &&
	   m->resources[ZAPPY_SIBUR] == 2 &&
	   m->resources[ZAPPY_MENDIANE] == 2 &&
	   m->resources[ZAPPY_PHIRAS] == 2 &&
	   m->resources[ZAPPY_THYSTAME] == 1));
}

void		incantation_start(t_client_ia *client, t_zappy *zappy)
{
  t_zappy_map	*m;

  m = &(zappy->world.map[POS(client->player.x, client->player.y,
			     zappy->world.width)]);
  if (get_valid_players(m, client->player.level) &&
      ((client->player.level == 1 && m->resources[ZAPPY_LINEMATE] == 1 &&
	m->resources[ZAPPY_DERAUMERE] == 0 && m->resources[ZAPPY_SIBUR] == 0 &&
	m->resources[ZAPPY_MENDIANE] == 0 && m->resources[ZAPPY_PHIRAS] == 0 &&
	m->resources[ZAPPY_THYSTAME] == 0) ||
       (client->player.level == 2 && m->resources[ZAPPY_LINEMATE] == 1 &&
	m->resources[ZAPPY_DERAUMERE] == 1 && m->resources[ZAPPY_SIBUR] == 1 &&
	m->resources[ZAPPY_MENDIANE] == 0 && m->resources[ZAPPY_PHIRAS] == 0 &&
	m->resources[ZAPPY_THYSTAME] == 0) ||
       (client->player.level == 3 && m->resources[ZAPPY_LINEMATE] == 2 &&
	m->resources[ZAPPY_DERAUMERE] == 0 && m->resources[ZAPPY_SIBUR] == 1 &&
	m->resources[ZAPPY_MENDIANE] == 0 && m->resources[ZAPPY_PHIRAS] == 2 &&
	m->resources[ZAPPY_THYSTAME] == 0) ||
       check_other_levels(m, client->player.level, &(client->player))))
    com_incantation_start(client, m, &zappy->server.clients_graphic);
  else
    {
      client->player.cur_action = ZAPPY_PLAYER_NO_ACTION;
      client->player.time_action = 0;
      set_answer_ok_ko(&client->client, FALSE);
    }
}

void		incantation_end(t_client_ia *client, t_zappy *zappy)
{
  t_zappy_map	*m;
  int		can_up;

  m = &(zappy->world.map[POS(client->player.x, client->player.y,
			     zappy->world.width)]);
  can_up = get_valid_players(m, client->player.level);
  if (can_up && client->player.x == client->player.startx &&
      client->player.y == client->player.starty &&
      ((client->player.level == 1 && m->resources[ZAPPY_LINEMATE] == 1 &&
	m->resources[ZAPPY_DERAUMERE] == 0 && m->resources[ZAPPY_SIBUR] == 0 &&
	m->resources[ZAPPY_MENDIANE] == 0 && m->resources[ZAPPY_PHIRAS] == 0 &&
	m->resources[ZAPPY_THYSTAME] == 0) ||
       (client->player.level == 2 && m->resources[ZAPPY_LINEMATE] == 1 &&
	m->resources[ZAPPY_DERAUMERE] == 1 && m->resources[ZAPPY_SIBUR] == 1 &&
	m->resources[ZAPPY_MENDIANE] == 0 && m->resources[ZAPPY_PHIRAS] == 0 &&
	m->resources[ZAPPY_THYSTAME] == 0) ||
       (client->player.level == 3 && m->resources[ZAPPY_LINEMATE] == 2 &&
	m->resources[ZAPPY_DERAUMERE] == 0 && m->resources[ZAPPY_SIBUR] == 1 &&
	m->resources[ZAPPY_MENDIANE] == 0 && m->resources[ZAPPY_PHIRAS] == 2 &&
	m->resources[ZAPPY_THYSTAME] == 0) ||
       check_other_levels(m, client->player.level, NULL)))
    clean_case(m);
  else
    can_up = 0;
  up_all(&(zappy->teams_manager.teams), &(m->list), can_up, zappy);
}
