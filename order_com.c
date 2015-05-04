/*
** order_com.c for 42sh in /home/seth/my_42sh
** 
** Made by kevin lansel
** Login   <lansel_k@epitech.net>
** 
** Started on  Tue May 22 12:21:10 2012 kevin lansel
** Last update Tue May 22 23:06:12 2012 florian dewulf
*/

#include	<stdlib.h>
#include	<string.h>
#include	"42sh.h"

static void	reduc_func(char *com, int *i)
{
  if (com[*i] && com[*i] >= '0' && com[*i] <= '9')
    while (com[*i] && com[*i] >= '0' && com[*i] <= '9')
      (*i)++;
  if (com[*i] == '<' || com[*i] == '>')
    {
      while (com[*i] && (com[*i] == '>' || com[*i] == '<'))
	(*i)++;
      while (com[*i] && com[*i] == ' ')
	(*i)++;
      while (com[*i] && com[*i] != ' ')
	(*i)++;
      while (com[*i] && com[*i] == ' ')
	(*i)++;
    }
}

int		func(char *com, int *i, int tmp)
{
  int		memo;

  *i = tmp;
  (*i)++;
  reduc_func(com, i);
  reduc_func(com, i);
  if (com[*i] == '\0' || com[*i] == '|' || com[*i] == ';' || com[*i] == '&')
    return (0);
  else
    {
      memo = *i;
      while (com[*i] && com[*i] != '|' && com[*i] != ';' && com[*i] != '&')
	(*i)++;
    }
  return (memo);
}

char		*cut_com(char *com, int *i, int tmp, int memo)
{
  char		*p1;
  char		*p2;
  char		*p3;
  char		*p4;
  char		*res1;
  char		*res2;
  char		*res3;

  p1 = cut_chain(0, tmp, com);
  p2 = cut_chain(tmp, memo, com);
  p3 = cut_chain(memo, *i, com);
  p4 = cut_chain(*i, strlen(com), com);
  res1 = concate(p1, p3);
  res2 = concate(p2, p4);
  res3 = concate(res1, res2);
  xfree(p1);
  xfree(p2);
  xfree(p3);
  xfree(p4);
  xfree(res1);
  xfree(res2);
  return (res3);
}

static char	*reduc_order_com(char *com, int *i)
{
  int		tmp;

  (*i != 0) ? ((*i)--) : 1;
  while ((*i) != 0 && ((com[*i] >= '0' && com[*i] <= '9') || com[*i] == '<' ||
		       com[*i] == '>'))
    (*i)--;
  tmp = *i;
  while (*i != 0 && (com[*i] == ' ' || com[*i] == '\t'))
    (*i)--;
  return (order_com_bis(i, tmp, com));
}

char		*order_com(char *com)
{
  int		i;
  char		tempo;

  i = 0;
  while (com[i])
    {
      while (com[i] && com[i] != '<' && com[i] != '>')
	{
	  if (com[i] == '"' || com[i] == '\'')
	    {
	      tempo = com[i];
	      while (com[++i] && com[i] != tempo);
	      if (com[i] == '\0')
		i--;
	    }
	  i++;
	}
      if (com[i] == '>' || com[i] == '<')
	{
	  if ((com = reduc_order_com(com, &i)) == NULL)
	    return (NULL);
	}
    }
  return (com);
}
