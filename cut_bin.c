/*
** cut_bin.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Fri May  4 11:19:13 2012 david blervaque
** Last update Wed May 16 20:29:49 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*malloc_my_bin(char *buff)
{
  int		i;
  int		j;
  char		*bin;

  i = 0;
  j = -1;
  while (buff[i] && buff[i] != '>' && buff[i] != '<' && buff[i] != '&')
    i++;
  while (i > 0 && buff[i] != ' ')
    i--;
  bin = xmalloc((i + 1) * sizeof(char));
  while (++j < i)
    bin[j] = buff[j];
  bin[j] = '\0';
  return (bin);
}

char		*cut_bin(char *bin)
{
  int		i;

  i = 0;
  while (bin[i] != ' ' && bin[i] != 0)
    i++;
  bin[i] = 0;
  return (bin);
}
