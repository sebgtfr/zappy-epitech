/*
** put_take.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy
**
** Made by
** Login   <terrea_l@epitech.net>
**
** Started on  Thu Jun 23 16:42:19 2016
** Last update Sat Jun 25 15:54:13 2016 Sébastien Le Maire
*/

#include <string.h>
#include "zappy_map.h"
#include "client_action.h"

t_zappy_resource	get_resource(char *str)
{
  if (!(strcmp(str, "nourriture")))
    return (ZAPPY_FOOD);
  if (!(strcmp(str, "linemate")))
    return (ZAPPY_LINEMATE);
  if (!(strcmp(str, "deraumere")))
    return (ZAPPY_DERAUMERE);
  if (!(strcmp(str, "sibur")))
    return (ZAPPY_SIBUR);
  if (!(strcmp(str, "mendiane")))
    return (ZAPPY_MENDIANE);
  if (!(strcmp(str, "phiras")))
    return (ZAPPY_PHIRAS);
  if (!(strcmp(str, "thystame")))
    return (ZAPPY_THYSTAME);
  return (ZAPPY_SIZE_TAB);
}

void			put(t_client_ia *client, t_zappy *zappy)
{
  t_player		*player;
  t_zappy_resource	resource;

  player = &(client->player);
  resource = get_resource(player->action[LAST_ORDER(player->id_order)].arg);
  if (resource == ZAPPY_SIZE_TAB || player->inventory[resource] == 0)
    set_answer_ok_ko(&client->client, FALSE);
  else
    {
      set_answer_ok_ko(&client->client, TRUE);
      player->inventory[resource] -= 1;
      add_resource(&(zappy->world), player->x, player->y, resource);
      set_all_client_msg_item(zappy, client, resource, "pgt");
    }
}

void			take(t_client_ia *client, t_zappy *zappy)
{
  t_player		*player;
  t_zappy_resource	resource;
  t_bool		ok;

  player = &(client->player);
  resource = get_resource(player->action[LAST_ORDER(player->id_order)].arg);
  if (resource == ZAPPY_SIZE_TAB)
    set_answer_ok_ko(&client->client, FALSE);
  else
    {
      if ((ok = remove_resource(&(zappy->world), player->x,
				player->y, resource)))
	{
	  player->inventory[resource] += 1;
	  set_all_client_msg_item(zappy, client, resource, "pdr");
	}
      set_answer_ok_ko(&client->client, ok);
    }
}
