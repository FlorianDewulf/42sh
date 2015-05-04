/*
** check_redir.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Wed Apr 25 12:33:59 2012 florian dewulf
** Last update Wed May  2 01:13:20 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

static int	check_redir_one(char *str, int *curs)
{
  int		tmp;

  tmp = *curs;
  while (str[++tmp] && str[tmp] != ' ' && str[tmp] != '\t');
  while (str[--tmp] != '&')
    if (!(str[tmp] <= '9' && str[tmp] >= '0'))
      return (0);
  if (tmp - 1 != *curs)
    return (0);
  while (*curs > 0 && str[*curs] != ' ' && str[*curs] != '\t')
    (*curs)--;
  if ((*curs) == 0)
    return (0);
  while (str[++(*curs)] != '>')
    if (str[*curs] > '9' || str[*curs] < '0')
      return (0);
  if ((*curs) + 1 != tmp)
    return (0);
  (*curs)--;
  while (*curs > 0 && str[*curs] != ' ' && str[*curs] != '\t')
    (*curs)--;
  (*curs)++;
  return (1);
}

static char	*check_double(int tmp, int *cur, char *str)
{
  int		tempo;

  if (str[*cur - 1] == ';' || str[*cur - 1] == '|' || str[*cur - 1] == '<' ||
      str[*cur + 2] == ';' || str[*cur + 2] == '|' || str[*cur + 2] == '<')
    return (NULL);
  tempo = *cur;
  while (tempo > 0 && str[tempo] != ' ' && str[tempo] != '\t')
    tempo--;
  if (tempo == 0)
    return (cut_chain(tmp, *cur, str));
  while (tempo < *cur)
    if (str[tempo] <= '9' && str[tempo] >= '0')
      tempo++;
    else
      return (cut_chain(tmp, *cur, str));
  while (tempo > 0 && str[tempo] != ' ' && str[tempo] != '\t')
    tempo--;
  (*cur) = tempo + 1;
  return (cut_chain(tmp, *cur, str));
}

static int	take_fd(int tmp, int *cur, char *str)
{
  int		tempo;

  tempo = *cur - 1;
  while (tempo > tmp && str[tempo] <= '9' && str[tempo] >= '0')
    tempo--;
  if (tempo == tmp || (str[tempo] != ' ' && str[tempo] != '\t'))
    return (0);
  return (1);
}

static char	*check_simple(int tmp, int *cur, char *str)
{
  if (str[*cur - 1] == ';' || str[*cur - 1] == '|' || str[*cur - 1] == '<' ||
      str[*cur + 1] == ';' || str[*cur + 1] == '|' || str[*cur + 1] == '<')
    return (NULL);
  if (take_fd(tmp, cur, str))
    {
      while (str[*cur] != ' ' && str[*cur] != '\t' && str[*cur])
	(*cur)--;
      (*cur)++;
    }
  return (cut_chain(tmp, *cur, str));
}

char		*check_redir(char *str, int *cur, int tmp)
{
  if (str[*cur + 1] == '&')
    {
      if (check_redir_one(str, cur))
	{
	  while (str[*cur] != ' ' && str[*cur] != '\t' && str[*cur])
	    (*cur)--;
	  (*cur)++;
	  return (cut_chain(tmp, *cur, str));
	}
      else
	return (NULL);
    }
  if (str[*cur + 1] == '>')
    {
      if (str[*cur + 2] || str[*cur + 2] == '|' || str[*cur + 2] == ';' ||
	  str[*cur + 2] == '>' || str[*cur + 2] == '<')
	return (check_double(tmp, cur, str));
    }
  return (check_simple(tmp, cur, str));
}
