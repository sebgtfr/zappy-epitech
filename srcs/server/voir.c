/*
** voir.c for zappy in /home/terrea_l/Projets/PSU_2015_zappy/srcs/server
** 
** Made by 
** Login   <terrea_l@epitech.net>
** 
** Started on  Thu Jun 23 14:23:14 2016 
** Last update Sun Jun 26 21:30:59 2016 
*/

#include "zappy_map.h"
#include "client_action.h"
#include "mystring.h"

void		push_resources(t_string *str, int nb_resource,
			       char const *type)
{
  int		k;

  k = 0;
  while (k++ < nb_resource)
    string_push_back(str, type);
}

void		add_case(t_world *world, int x, int y, t_string *str)
{
  int		*resources;
  unsigned int	k;

  resources = world->map[POS(x, y, world->width)].resources;
  push_resources(str, resources[ZAPPY_FOOD], " nourriture");
  push_resources(str, resources[ZAPPY_LINEMATE], " linemate");
  push_resources(str, resources[ZAPPY_DERAUMERE], " deraumere");
  push_resources(str, resources[ZAPPY_SIBUR], " sibur");
  push_resources(str, resources[ZAPPY_MENDIANE], " mendiane");
  push_resources(str, resources[ZAPPY_PHIRAS], " phiras");
  push_resources(str, resources[ZAPPY_THYSTAME], " thystame");
  k = 0;
  while (k++ < world->map[POS(x, y, world->width)].list.length)
    string_push_back(str, " joueur");
}

void		voir_vertical(t_client_ia *client, t_zappy *zappy)
{
  int		k;
  int		i;
  int		dir;
  t_string	*str;

  dir = (client->player.facing == DOWN) ? 1 : (-1);
  str = &(client->client.msg);
  string_push_back_char(str, '{');
  k = 0;
  while (k <= client->player.level)
    {
      i = k * (-1);
      while (i <= k)
	{
	  add_case(&(zappy->world),
		   MOD(client->player.x + i, (int)zappy->world.width),
		   MOD(client->player.y + dir * k,
		       (int)zappy->world.height), str);
	  if (i != k || k != client->player.level)
	    string_push_back_char(str, ',');
	  i++;
	}
      k = k + 1;
    }
  string_push_back(str, "}\n");
}

void		voir_horizontal(t_client_ia *client, t_zappy *zappy)
{
  int		k;
  int		i;
  int		dir;
  t_string	*str;

  dir = (client->player.facing == RIGHT) ? 1 : (-1);
  str = &(client->client.msg);
  string_push_back_char(str, '{');
  k = 0;
  while (k <= client->player.level)
    {
      i = k * (-1);
      while (i <= k)
	{
	  add_case(&(zappy->world),
		   MOD(client->player.x + dir * k,
		       (int)zappy->world.width),
		   MOD(client->player.y + i, (int)zappy->world.height), str);
	  if (i != k || k != client->player.level)
	    string_push_back_char(str, ',');
	  i++;
	}
      k = k + 1;
    }
  string_push_back(str, "}\n");
}

void		voir(t_client_ia *client, t_zappy *zappy)
{
  if (client->player.facing == UP || client->player.facing == DOWN)
    voir_vertical(client, zappy);
  else
    voir_horizontal(client, zappy);
}
