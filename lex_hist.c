/*
** lex_hist.c for 42sh in /home/lund/svn/42sh-2016-dewulf_f
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 19 14:12:03 2012 florian dewulf
** Last update Sun May 20 19:46:48 2012 florian dewulf
*/

#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

static char	*paste_str(char *begin, char *send, char *end,
			   t_history **history)
{
  char		*str;

  str = rmbhistory(send, history);
  xfree(send);
  if (str == NULL)
    return (NULL);
  if ((send = concate(begin, str)) == NULL)
    return (NULL);
  xfree(begin);
  xfree(str);
  begin = concate(send, end);
  xfree(send);
  xfree(end);
  str = begin;
  if (str == NULL)
    return (NULL);
  printf("%s\n", str);
  return (str);
}

static char	*replace_histo_nb(char *str, int *curs, t_history **history)
{
  char		*exp_begin;
  char		*exp_end;
  int		begin;
  char		*send;

  begin = *curs;
  while (str[++(*curs)] && str[(*curs)] != ' ' && str[(*curs)] != '\t' &&
	 str[(*curs)] != '!' && str[(*curs)] != '"');
  if ((exp_begin = cut_chain(0, begin, str)) == NULL)
    return (str);
  if ((exp_end = cut_chain(*curs, strlen(str), str)) == NULL)
    {
      xfree(exp_begin);
      return (str);
    }
  if ((send = cut_chain(begin, *curs, str)) == NULL)
    {
      xfree(exp_end);
      return (str);
    }
  if ((send = paste_str(exp_begin, send, exp_end, history)) == NULL)
    return (str);
  *curs = -1;
  return (send);
}

static char	*replace_com(char *str, int *curs, t_history **history)
{
  char		*exp_begin;
  char		*exp_end;
  char		*send;

  if ((exp_begin = cut_chain(0, *curs, str)) == NULL)
    return (str);
  if ((exp_end = cut_chain(*curs + 2, strlen(str), str)) == NULL)
    {
      xfree(exp_begin);
      return (str);
    }
  if ((send = cut_chain(*curs, *curs + 2, str)) == NULL)
    {
      xfree(exp_end);
      return (str);
    }
  (*curs) += 2;
  if ((send = paste_str(exp_begin, send, exp_end, history)) == NULL)
    return (str);
  *curs = -1;
  return (send);
}

char		*lex_hist(char *str, t_history *history)
{
  int		curs;

  curs = -1;
  while (str[++curs])
    {
      if (str[curs] == '!' && str[curs + 1] == '!')
	str = replace_com(str, &curs, &history);
      else if (str[curs] == '!')
	str = replace_histo_nb(str, &curs, &history);
    }
  return (str);
}
