/*
** mystring.h for libcontainer in /home/le-mai_s/rendu/tek2/systemUnix/PSU_2015_zappy/include/libcontainer
**
** Made by Sébastien Le Maire
** Login   <le-mai_s@epitech.net>
**
** Started on  Wed Jun 22 16:16:19 2016 Sébastien Le Maire
** Last update Fri Jun 24 23:26:05 2016 Sébastien Le Maire
*/

#ifndef MYSTRING_H_
# define MYSTRING_H_

# include <stdlib.h>

typedef struct			s_string
{
  size_t			length;
  size_t			capacity;
  char				*data;
}				t_string;

/*
** String's functions
** initialisation :
*/
int				string_copy(t_string *str,
					    t_string const *data);
int				string_char_copy(t_string *str,
						 char const *data);
int				string_init(t_string *str, size_t capacity);

/*
** Add elements string's functions
*/
int				string_push_back(t_string *str,
						 char const *data);
int				string_push_back_char(t_string *str,
						      char const c);
int				string_resize(t_string *str, size_t capacity);

/*
** Delete string's functions
*/
void				string_clear(t_string *str);

#endif /* !MYSTRING_H_ */
