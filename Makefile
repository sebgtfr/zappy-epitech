##
## Makefile for zappy in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy
## 
## Made by Sébastien Le Maire
## Login   <le-mai_s@epitech.net>
## 
## Started on  Mon May 23 23:03:30 2016 Sébastien Le Maire
## Last update Sun Jun 26 13:13:16 2016 Sébastien Le Maire
##

ifeq ($(DEBUG), yes)

CFLAGS			+= -g -g3 -ggdb

endif

PATH_BINARY		= ./
PATH_SRCS		= ./srcs/
PATH_SRCS_SERVER	= $(PATH_SRCS)server/
PATH_LIB		= ./lib/
PATH_LIB_LIST_SRCS	= $(PATH_LIB)container/list/
PATH_LIB_VECTOR_SRCS	= $(PATH_LIB)container/vector/
PATH_LIB_STRING_SRCS	= $(PATH_LIB)container/string/

NAME_SERVER		= $(PATH_BINARY)zappy_server
NAME_LIB_CONTAINER	= $(PATH_LIB)libcontainer.a

CFLAGS			+= -Wall -Wextra -Werror
CFLAGS			+= -I./include/zappy_server/
CFLAGS			+= -I./include/libcontainer/

LDFLAGS			= -L./lib/ -lcontainer

SRCS_SERVER		= $(PATH_SRCS_SERVER)main.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)getnbr.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)error.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)init.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)cmd_p_x_y_t_c.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)cmd_n.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)cmd_h.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)tcp.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)resource.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)select.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)client.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)send_recv.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)manager.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)io_manager.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)team.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)player.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)action.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)map.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)expulse.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)time.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)basic_ia_com.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)answer_ia.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)answer_init_graph.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)time_graph_com.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)player_graph_com.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)world_manage.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)broadcast.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)broadcast_graph.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)client_action.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)put_take.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)voir.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)inventaire.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)up_players.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)incantation.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)cmd_init_graph.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)cmd_graph.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)graph_expulse.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)fork.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)item_graph_com.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)connect_nbr.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)egg_to_player.c
SRCS_SERVER		+= $(PATH_SRCS_SERVER)incantation_com.c

# srcs libcontainer
SRCS_LIB_LIST		= $(PATH_LIB_LIST_SRCS)init_list.c
SRCS_LIB_LIST		+= $(PATH_LIB_LIST_SRCS)del_list.c
SRCS_LIB_LIST		+= $(PATH_LIB_LIST_SRCS)add_list.c
SRCS_LIB_LIST		+= $(PATH_LIB_LIST_SRCS)foreach_list.c
SRCS_LIB_VECTOR		= $(PATH_LIB_VECTOR_SRCS)init_vector.c
SRCS_LIB_VECTOR		+= $(PATH_LIB_VECTOR_SRCS)del_vector.c
SRCS_LIB_VECTOR		+= $(PATH_LIB_VECTOR_SRCS)add_vector.c
SRCS_LIB_VECTOR		+= $(PATH_LIB_VECTOR_SRCS)foreach_vector.c
SRCS_LIB_STRING		= $(PATH_LIB_STRING_SRCS)init_string.c
SRCS_LIB_STRING		+= $(PATH_LIB_STRING_SRCS)del_string.c
SRCS_LIB_STRING		+= $(PATH_LIB_STRING_SRCS)add_string.c

OBJS_SERVER		= $(SRCS_SERVER:.c=.o)

OBJS_LIB_CONTAINER	= $(SRCS_LIB_LIST:.c=.o) $(SRCS_LIB_VECTOR:.c=.o) $(SRCS_LIB_STRING:.c=.o)

CC			= gcc

AR			= ar rc

RAN			= ranlib

RM			= rm -f

NAME_CLIENT		= zappy_ai
PATH_CLIENT		= ./ia_client/

all: $(NAME_LIB_CONTAINER) $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) -o $(NAME_SERVER) $(OBJS_SERVER) $(LDFLAGS)

$(NAME_LIB_CONTAINER): $(OBJS_LIB_CONTAINER)
	$(AR) $(NAME_LIB_CONTAINER) $(OBJS_LIB_CONTAINER)
	$(RAN) $(NAME_LIB_CONTAINER)

$(NAME_CLIENT):
	ln -s $(PWD)/$(PATH_CLIENT)/$(NAME_CLIENT) $(PWD)/$(NAME_CLIENT)

clean:
	$(RM) $(OBJS_SERVER)
	$(RM) $(OBJS_LIB_CONTAINER)
	cd $(PATH_CLIENT) && ./clean_py.sh || echo "error with $@"

fclean: clean
	$(RM) $(NAME_SERVER)
	$(RM) $(NAME_LIB_CONTAINER)
	$(RM) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re
