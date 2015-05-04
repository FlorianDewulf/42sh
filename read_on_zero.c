/*
** read_on_zero.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Fri May  4 17:25:13 2012 david blervaque
** Last update Wed May 16 23:49:54 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

t_dlr		*fill_list(t_dlr *list, char *str)
{
  t_dlr		*new_elem;
  t_dlr		*tmp;

  if (str == NULL || (new_elem = malloc(sizeof(t_dlr))) == NULL)
    return (my_puterror_null(EXIT_MALLOC));
  new_elem->line = my_strcpy(str);
  new_elem->next = NULL;
  tmp = list;
  if (list == NULL)
    return (new_elem);
  else
    {
      while (tmp->next != NULL)
	tmp = tmp->next;
      tmp->next = new_elem;
      return (list);
    }
}

t_dlr		*read_on_zero(char *name)
{
  t_dlr		*list;
  char		buff[BUFFER];
  int		ret;

  list = NULL;
  my_putstr("> ");
  while ((ret = read(0, buff, 1023)) != -1)
    {

      buff[ret - 1] = '\0';
      if ((list = fill_list(list, my_strcpy(buff))) == NULL)
	return (NULL);
      if (comp(buff, name) == 1)
	return (list);
      my_putstr("> ");
    }
  return (NULL);
}
