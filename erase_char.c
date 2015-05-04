/*
** erase_char.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May  6 19:55:14 2012 florian dewulf
** Last update Mon May  7 13:52:33 2012 florian dewulf
*/

#include	<stdio.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<string.h>
#include	<stdlib.h>
#include	"42sh.h"

static void	tcerase_char(char *buff, int begin)
{
  char		*cap;

  cap = NULL;
  while (buff[++begin])
    my_putchar(buff[begin]);
  my_putchar(' ');
  cap = xtgetstr_exe(cap, "rc");
}

void		erase_char(int *curs, char *buffer)
{
  char		*cap;
  int		tempo;

  cap = NULL;
  tempo = curs[0] - 1;
  while (buffer[++tempo])
    buffer[tempo - 1] = buffer[tempo];
  buffer[tempo - 1] = '\0';
  go_to_left(curs);
  xtgetstr_exe(cap, "sc");
  tcerase_char(buffer, curs[0] - 1);
}
