/*
** cut_file.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Thu May  3 16:54:51 2012 david blervaque
** Last update Wed May 16 20:11:04 2012 florian dewulf
*/

#include	"42sh.h"

char		*cut_file(char *buff)
{
  int		i;
  int		j;
  char		*file;

  i = 0;
  while (buff[i] && buff[i] != '>' && buff[i] != '<' && buff[i] != '&')
    i++;
  while (buff[i] != ' ')
    i++;
  j = i;
  while (buff[j])
    j++;
  file = xmalloc((j + 1) * sizeof(char));
  j = 0;
  i++;
  while (buff[i] != ' ' && buff[i] != 0)
    file[j++] = buff[i++];
  file[j] = 0;
  return (file);
}
