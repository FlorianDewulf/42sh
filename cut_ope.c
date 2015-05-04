/*
** cut_ope.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Wed May  2 15:23:44 2012 david blervaque
** Last update Thu May 17 10:29:59 2012 florian dewulf
*/

#include	"42sh.h"

char		*cut_ope(char *buff)
{
  int		i;
  int		j;
  char		*ope_tmp;

  i = 0;
  while (buff[i] && buff[i] != '>' && buff[i] != '<')
    i++;
  if (buff[i] == '<' && buff[i + 1] == '<')
    ope_tmp = cut_chain(i, i + 2, buff);
  else if (buff[i] == '<')
    ope_tmp = cut_chain(i, i + 1, buff);
  else
    {
      j = i;
      while (buff[j] == '>')
	j++;
      while (i > 0 && buff[i] != ' ' && buff[i] != '\t')
	i--;
      if (buff[i] == ' ' || buff[i] == '\t')
	i++;
      ope_tmp = cut_chain(i, j, buff);
    }
  return (ope_tmp);
}
