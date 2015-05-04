/*
** check.c for 42sh.h in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Tue May  1 15:12:00 2012 florian dewulf
** Last update Tue May  8 23:20:23 2012 florian dewulf
*/

#include	<string.h>
#include	"42sh.h"

static int	if_one_char(char *str)
{
  if (str[0] == ';')
    return (PT);
  else if (str[0] == '|')
    return (PIPE);
  else if (str[0] == '>' || str[0] == '<')
    return (REDIR);
  else
    return (COM);
}

static int	if_two_char(char *str)
{
  if (comp(str, "&&"))
    return (AND);
  else if (comp(str, "||"))
    return (OR);
  else if (comp(str, ">>") || comp(str, "<<") || str[1] == '>' ||
	   comp(str, ">&"))
    return (REDIR);
  else
    return (COM);
}

int		check_type(char *str)
{
  if (strlen(str) == 1)
    return (if_one_char(str));
  else if (strlen(str) == 2)
    return (if_two_char(str));
  else
    {
      if (match_fdred(str, "*>") || match_fdred(str, "*>>") ||
	  match_fdred(str, "*>&*"))
	return (REDIR);
    }
  return (COM);
}
