/*
** cmd_n.c for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/srcs/server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Mon Jun  6 12:39:44 2016 Sébastien Le Maire
** Last update Sat Jun 25 21:31:42 2016 
*/

#include <unistd.h>
#include <string.h>
#include "zappy_server.h"

static int	       		check_group_name(void *content,
						 void const *data)
{
  return (strcmp(((t_team *)content)->name, (char const *)data));
}

static void			init_team(t_team *team, char const *name)
{
  team->name = name;
  team->nb_player = 0;
  team->slot = 0;
  team->max_lvl_player = 0;
  team->nb_ghost = 0;
}

static void			print_warning(void)
{
  char const			*warn;

  warn = "\033[01;31mWarning ! team's name \"GRAPHIC\" is refused !\n\033[00m";
  (void)write(STDERR_FILENO, (void *)warn, strlen(warn));
}

static t_zappy_error		push_team(t_vector *teams,
					  char **teams_name,
					  unsigned int nb_args)
{
  t_team			team;
  uint16_t			i;

  i = 0;
  while (i < nb_args)
    {
      if (strcmp((char const *)(*teams_name), "GRAPHIC"))
	{
	  init_team(&team, *teams_name);
	  if (vector_compare(teams, &check_group_name, (void *)(*teams_name)))
	    return (ZAPPY_GROUP_NAME_ALREADY_EXIST);
	  if (vector_push_back(teams, (void *)&team))
	    return (ZAPPY_BAD_ALLOC);
	}
      else
	print_warning();
      ++i;
      ++teams_name;
    }
  return (ZAPPY_NO_ERROR);
}

t_zappy_error			cmd_n(t_zappy *zappy, char **args,
				      unsigned int *nb_args)
{
  t_zappy_error			ret;
  unsigned int			size;

  *nb_args = 0;
  size = 0;
  while ((args[(*nb_args)]) &&
	 (search_command(*(args + (*nb_args)), NULL) != ZAPPY_NO_ERROR))
    {
      ++(*nb_args);
      if (strcmp(*(args + ((*nb_args) - 1)), "GRAPHIC"))
	++size;
    }
  if (size)
    if (vector_resize(&zappy->teams_manager.teams,
		      zappy->teams_manager.teams.length + size, NULL))
      return (ZAPPY_BAD_ALLOC);
  ret = push_team(&zappy->teams_manager.teams, args, *nb_args);
  return (ret);
}
