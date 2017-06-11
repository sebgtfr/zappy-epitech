/*
** zappy_action.h for zappy in /home/karraz_s/rendu/PSU_2015_zappy
**
** Made by stephane karraz
** Login   <karraz_s@epitech.net>
**
** Started on  Mon Jun 20 13:30:30 2016 stephane karraz
** Last update Sun Jun 26 21:36:51 2016 
*/

#ifndef ZAPPY_ACTION_H_
# define ZAPPY_ACTION_H_

# define MAX_ORDERS	10
# define LEN_ORDER	32
# define LEN_ARG	1024

# define LAST_ORDER(o)	((!(o)) ? (MAX_ORDERS - 1) : ((o) - 1))

typedef struct		s_action
{
  char			order[LEN_ORDER + 1];
  char			arg[LEN_ARG + 1];
}			t_action;

#endif /* !ZAPPY_ACTION_H_ */
