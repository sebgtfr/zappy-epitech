/*
** client_action.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Sun Jun 26 00:22:12 2016 Sébastien Le Maire
** Last update Sun Jun 26 16:22:34 2016 Sébastien Le Maire
*/

#ifndef CLIENT_ACTION_H_
# define CLIENT_ACTION_H_

# include "zappy_server.h"

typedef struct		s_incantation_data
{
  int			lvl;
  int			can_up;
}			t_incantation_data;

typedef struct		s_up_data
{
  t_vector		*teams;
  int			can_up;
}			t_up_data;

void			up_players(void *content, void *data);
void			clean_case(t_zappy_map *m);
void			set_start_pos(t_player *player);
void			avance(t_client_ia *client, t_zappy *zappy);
void			left(t_client_ia *client, t_zappy *zappy);
void			right(t_client_ia *client, t_zappy *zappy);
void			expulse(t_client_ia *client, t_zappy *zappy);
void			take(t_client_ia *client, t_zappy *zappy);
void			put(t_client_ia *client, t_zappy *zappy);
void			voir(t_client_ia *client, t_zappy *zappy);
void			inventaire(t_client_ia *client, t_zappy *zappy);
void			incantation_start(t_client_ia *client, t_zappy *zappy);
void			incantation_end(t_client_ia *client, t_zappy *zappy);
void		        fatherfork(t_client_ia *client, t_zappy *zappy);
void			motherfork(t_client_ia *client, t_zappy *zappy);
void			connect_nbr(t_client_ia *client, t_zappy *zappy);
void			up_all(t_vector *teams, t_list *list, int can_up,
			       t_zappy *z);

#endif /* !CLIENT_ACTION_H_ */
