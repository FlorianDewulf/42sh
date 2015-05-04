/*
** cut.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Mon Apr 23 17:14:59 2012 florian dewulf
** Last update Sun May 20 20:28:28 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static int	move_curs(char *str, int cur)
{
  char		tempo;

  while (str[cur] && str[cur] != '>' && str[cur] != '<' &&
	 str[cur] != '|' && str[cur] != ';'  && str[cur] != '&')
    {
      if (str[cur] == '"' || str[cur] == '\'')
	{
	  tempo = str[cur];
	  while (str[++cur] && str[cur] != tempo);
	}
      if (str[cur])
	cur++;
    }
  return (cur);
}

static char	*sort_chain(char *str, int *cur)
{
  int		tmp;
  char		*str2;

  tmp = *cur;
  *cur = move_curs(str, *cur);
  if (str[*cur] == '|' || str[*cur] == ';')
    return (check_around(tmp, *cur, str, str[*cur]));
  else if (str[*cur] == '>' && (str2 = check_redir(str, cur, tmp)))
    return (str2);
  else if (str[*cur] == '<' && (str2 = check_left_redir(str, tmp, cur)))
    return (str2);
  else if (str[*cur] == '&' && (str2 = check_and(tmp, cur, str)))
    return (str2);
  else if (!str[*cur])
    return (cut_chain(tmp, *cur, str));
  else
    return (NULL);
}

t_tree		*line_to_list(char *str)
{
  t_tree	*list;
  char		*ret;
  int		curs;

  curs = 0;
  list = NULL;
  while (str[curs])
    {
      ret = sort_chain(str, &curs);
      if ((ret == NULL && str[curs]) || (ret != NULL && ret[0] == '\0'))
	return (NULL);
      else if (ret == NULL && !str[curs])
	return (list);
      add_elem(&list, ret);
      ret = take_separ(str, &curs);
      if (ret == NULL && str[curs])
	return (NULL);
      else if (ret == NULL && !str[curs])
	return (list);
      add_elem(&list, ret);
      while (str[curs] == ' ' || str[curs] == '\t')
	curs++;
    }
  return (list);
}
