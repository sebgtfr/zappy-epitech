##
## Makefile for toto in /home/le-mai_s/test/zappy
## 
## Made by Sébastien Le Maire
## Login   <le-mai_s@epitech.net>
## 
## Started on  Sun Jun 26 21:42:08 2016 Sébastien Le Maire
## Last update Sun Jun 26 21:28:45 2016 Sébastien Le Maire
##

ifeq ($(DEBUG), yes)

CXXFLAGS			+= -g -g3 -ggdb

endif

PATH_BINARY		= ./
PATH_SRCS		= ./

NAME			= $(PATH_BINARY)toto

CXXFLAGS		+= -Wall -Wextra -Werror
CXXFLAGS		+= -I./

SRCS			= $(PATH_SRCS)Socket.cpp
SRCS			+= $(PATH_SRCS)ClientTCP.cpp
SRCS			+= $(PATH_SRCS)main.cpp

OBJS			= $(SRCS:.cpp=.o)

CXX			= g++

RM			= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
