/*
** zappy_client.h for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/zappy_server
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Tue Jun 14 11:18:59 2016 Sébastien Le Maire
** Last update Sun Jun 26 00:27:10 2016 Sébastien Le Maire
*/

#ifndef ZAPPY_CLIENT_H_
# define ZAPPY_CLIENT_H_

# include "vector.h"
# include "list.h"
# include "zappy_bool.h"
# include "zappy_network.h"
# include "zappy_map.h"
# include "mystring.h"

typedef enum			e_connected
  {
				ZAPPY_CONNECTE,
				ZAPPY_DISCONNECTE,
				ZAPPY_CONNECTION_UNDEFINE,
				ZAPPY_DECONNECTION_AFTER_SEND_MSG
  }				t_connected;

typedef enum			s_client_type
  {
				ZAPPY_CLIENT_IA,
				ZAPPY_CLIENT_GRAPHIC,
				ZAPPY_CLIENT_UNDEFINED
  }				t_client_type;

/*
** Communication
*/
typedef enum			e_zappy_com
  {
				ZAPPY_COM_WELCOME,
				ZAPPY_COM_INFO_NEW_PLAYER,
				ZAPPY_COM_DEAD,
				ZAPPY_COM_TIME,
				ZAPPY_COM_LAST
  }				t_zappy_com;

typedef struct			s_client
{
  t_socket			socket;
  t_connected			connection;
  t_client_type			type;
  t_zappy_com			com;
  t_string			msg;
  uint32_t			id;
  uint32_t     			id_egg;
}				t_client;

typedef struct			s_client_ia
{
  t_client			client;
  t_player			player;
}				t_client_ia;

typedef struct			s_client_graphic
{
  t_client			client;
}				t_client_graphic;

/*
** client.c
*/
t_zappy_error			new_client(t_zappy_server *server, int *max,
					   t_world *world);
void				close_clients(void *clients);
void				client_set_com(t_list *clients, t_zappy_com com);

/*
** send_recv.c
*/
void				server_send(t_client *client,
					    void const *msg, size_t len);
void				server_recv(t_client *client,
					    void *msg, size_t len);

/*
** player.c
*/
void				delete_player_on_map(t_player *player,
						     t_world *world);
t_bool				hp_management(t_client_ia *client,
					      t_list *list_graph,
					      t_vector *team);

/*
** map1.c
*/
t_client_ia			*convert_player_to_client(t_player *player);

#endif /* !ZAPPY_CLIENT_H_ */
