/*
** check_bin.c for 42 in /home/david/Projet/42sh/exec/redir_droite
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Fri May  4 14:08:46 2012 david blervaque
** Last update Tue May 15 18:54:36 2012 florian dewulf
*/

#include	"42sh.h"

char		*check_bin(char *bin)
{
  char		path[] = "/bin/\0";

  bin = concate(path, bin);
  return (bin);
}
