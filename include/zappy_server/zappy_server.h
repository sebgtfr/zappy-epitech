/*
** zappy_server.h for Zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Thu Jun  2 07:59:53 2016 Sébastien Le Maire
** Last update Sun Jun 26 21:37:12 2016 
*/

#ifndef ZAPPY_SERVER_H_
# define ZAPPY_SERVER_H_

# include <stdint.h>
# include "list.h"
# include "zappy_error.h"
# include "zappy_time.h"
# include "zappy_client.h"

/*
** Datas zappy server
*/
typedef struct			s_team
{
  char const			*name;
  unsigned int			nb_player;
  unsigned int			slot;
  unsigned int			max_lvl_player;
  unsigned int			nb_ghost;
}				t_team;

typedef struct			s_team_manager
{
  uint32_t			nb_client_max;
  t_vector			teams;
}				t_team_manager;

typedef struct			s_zappy
{
  t_team_manager	        teams_manager;
  t_world			world;
  t_zappy_server		server;
  t_time			timer;
}				t_zappy;

/*
** Param's commands server
*/
typedef t_zappy_error		(*t_zappy_cmd)(t_zappy *, char **,
					       unsigned int *);

/*
** Client manager pointer of function
*/
typedef t_zappy_error		(*t_client_read)(t_item **, t_zappy *);
typedef void			(*t_client_write)(t_client *, t_zappy *);
typedef void			(*t_client_com)(t_client *, t_zappy *);

# define CMP_CLIENT_PTR(c, n)	((n) && (((void *)((n)->data)) == (void *)(c)))

typedef struct			s_zappy_command
{
  char				flag;
  t_zappy_cmd			command;
}				t_zappy_command;

# define NB_CMD			(7)

typedef void			(*t_zappy_fct_action)(t_client_ia *, t_zappy *);

typedef struct			s_zappy_cmd_action
{
  char const			*order;
  unsigned int			time;
  t_bool			have_arg;
  t_zappy_fct_action	        init;
  t_zappy_fct_action		action;
}				t_zappy_cmd_action;

typedef void			(*t_zappy_graph_cmd)(t_client *, t_zappy *,
						     char const *);

typedef struct			s_zappy_cmd_graph
{
  char const			*cmd;
  t_bool			have_arg;
  t_zappy_graph_cmd		action;
}				t_zappy_cmd_graph;

# define NB_GRAPH_CMD		(9)

/*
** Functions :
** getnbr.c
*/
long int			getnbr(char const *str, t_zappy_error *err);

/*
** init.c
*/
t_zappy_error			search_command(char const *flag,
					       uint8_t *index);
t_zappy_error			zappy_init(t_zappy *zappy, char **args);

/*
** Commands :
** cmd_p_x_y_t_c.c
*/
t_zappy_error			cmd_p(t_zappy *zappy, char **args,
				      unsigned int *nb_args);
t_zappy_error			cmd_x(t_zappy *zappy, char **args,
				      unsigned int *nb_args);
t_zappy_error			cmd_y(t_zappy *zappy, char **args,
				      unsigned int *nb_args);
t_zappy_error			cmd_t(t_zappy *zappy, char **args,
				      unsigned int *nb_args);
t_zappy_error			cmd_c(t_zappy *zappy, char **args,
				      unsigned int *nb_args);

/*
** cmd_n.c
*/
t_zappy_error			cmd_n(t_zappy *zappy, char **args,
				      unsigned int *nb_args);

/*
** cmd_h.c
*/
t_zappy_error			cmd_h(t_zappy *zappy, char **args,
				      unsigned int *nb_args);

/*
** select.c
*/
t_zappy_error			launch_server(t_zappy *zappy);

/*
** manager.c
*/
t_zappy_error  			manager(t_zappy *zappy, int *max,
					uint32_t *ticks_gen_resource);

/*
** client.c
*/
t_zappy_error			egg_client(t_zappy_server *server, t_team *team,
					   t_world *world, t_egg *egg);
t_item				*delete_client(t_list *clients, t_item *client,
					       int *max, t_zappy *zappy);

/*
** io_manager.c
*/
t_zappy_error			read_ia_manager(t_item **client,
						t_zappy *zappy);
void			        write_client_manager(t_client *client,
						     t_zappy *zappy);
t_zappy_error			read_graph_manager(t_item **client_node,
						   t_zappy *zappy);

/*
** team.c
*/
t_zappy_error  			get_team(t_item **client, t_zappy *zappy);

/*
** action.c
*/
t_bool				get_action(t_player *player,
					   t_action *action);
void			        receiv_action(t_client_ia *client);
void			        get_one_action(t_client *client,
					       t_action *action);

/*
** world_manage.c
*/
t_bool				init_world(t_world *world);
void				world_manage(t_client_ia *client,
					     t_zappy *zappy);

/*
** broadcast.c
*/
void				broadcast(t_client_ia *ia, t_zappy *zappy);

/*
** basic_ia_com.c
*/
void				send_welcome(t_client *client, t_zappy *zappy);
void				send_info_new_player(t_client *client,
						     t_zappy *zappy);
void				send_dead(t_client *client, t_zappy *zappy);

/*
** answer_ia.c
*/
void				set_answer_ok_ko(t_client *client, t_bool ok);

/*
** answer_init_graphic.c
*/
void			        set_answer_map_size(t_client *client,
						    t_world *world);
void			        set_answer_data_case(t_client *client,
						     t_world *world,
						     unsigned int x,
						     unsigned int y);
void			        set_answer_all_case_data(t_client *client,
							 t_world *world);
void			        set_answer_teams_name(t_client *client,
						      t_vector *teams);
void			        set_answer_init_graphic(t_client *client,
							t_zappy *zappy);

/*
** time_graph_com.c
*/
void			        set_answer_time(t_client *client,
						t_time *timer);
void				cmd_graph_time(t_client *client,
					       t_zappy *zappy,
					       char const *args);

/*
** player_graph_com.c
*/
void				set_msg_new_player(t_client_ia *ia,
						   t_string *msg, t_team *team);
void				set_msg_all_new_player(t_list *clients,
						       t_string *msg,
						       t_team *team);
void				set_msg_pos_player(t_client *client,
						   t_client_ia *ia);
void				set_msg_lvl_player(t_client *client,
						   t_client_ia *ia);
void				set_msg_inventory_player(t_client *client,
							 t_client_ia *ia);

/*
** broadcast_graph.c
*/
void				set_msg_all_client(void *client, void *msg);
void				set_msg_broadcast(uint32_t id, char const *msg,
						  t_list *graph);

/*
** item_graph_com.c
*/
void				set_all_client_msg_item(t_zappy *zappy,
							t_client_ia *ia,
							t_zappy_resource res,
							char const *cmd);

/*
** cmd_init_graph.c
*/
void				cmd_graph_map(t_client *client, t_zappy *zappy,
					      char const *args);
void				cmd_graph_case(t_client *client,
					       t_zappy *zappy,
					      char const *args);
void				cmd_graph_all_case(t_client *client,
						   t_zappy *zappy,
						   char const *args);
void				cmd_graph_teams(t_client *client,
						t_zappy *zappy,
						char const *args);

/*
** cmd_graph.c
*/
void				cmd_graph_pos_player(t_client *client,
						     t_zappy *zappy,
						     char const *args);
void				cmd_graph_lvl_player(t_client *client,
						     t_zappy *zappy,
						     char const *args);
void				cmd_graph_inventoty_player(t_client *client,
							   t_zappy *zappy,
							   char const *args);

/*
** graph_expulse.c
*/
void				msg_expulse_exe(t_string *msg, uint32_t id);
void			        msg_expulse_pos_player(t_string *msg,
						       t_client_ia *ia);

/*
** egg_to_player.c
*/
uint8_t				egg_to_player(t_client_ia *new_ia,
					      t_list *list_ia);
void				recup_player_from_egg(t_client_ia **old_ptr,
						      t_list *list_ia);
void				set_msg_egg_player(t_string *msg,
						   uint32_t id);

/*
** incantation_com.c
*/
void				com_incantation_start(t_client_ia *ia,
						      t_zappy_map *map,
						      t_list *clients_graph);
void				push_msg_lvl_player(t_string *msg,
						    t_client_ia *ia);
void				push_msg_data_case(t_string *msg,
						   unsigned int x,
						   unsigned int y,
						   t_zappy_map *map_case);
void				msg_incantation_player_end(t_list *case_player,
							   t_string *msg,
							   t_world *world,
							   t_player *ref);

#endif /* !ZAPPY_SERVER_H_ */
