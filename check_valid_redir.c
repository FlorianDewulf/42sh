/*
** check_valid_redir.c for 42sh in /home/lund/svn/Correction
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon May 21 22:50:28 2012 florian dewulf
** Last update Mon May 21 23:52:10 2012 florian dewulf
*/

#include	<string.h>
#include	"42sh.h"

int		valid_redir(char *str)
{
  char		**tab;
  int		curs;

  curs = -1;
  tab = mini_lex(str);
  while (tab[++curs]);
  if (curs > 5)
    return (0);
  else if (curs == 5 && ((tab[1][strlen(tab[1] - 1)] == '<' &&
			  tab[3][strlen(tab[3] - 1)] == '>') ||
			 (tab[1][strlen(tab[1] - 1)] == '>' &&
			  tab[3][strlen(tab[3] - 1)] == '<')))
    return (in_order(tab));
  else if (curs == 5)
    return (0);
  return (2);
}

int		check_valid_redir(t_tree *list)
{
  t_tree	*tmp;

  tmp = list;
  while (tmp)
    {
      if (tmp->type == REDIR && valid_redir(tmp->exp) == 0)
	return (0);
      tmp = tmp->right;
    }
  return (1);
}
