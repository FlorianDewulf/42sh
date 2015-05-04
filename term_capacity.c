/*
** term_capacity.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May  4 19:47:32 2012 florian dewulf
** Last update Wed May  9 11:23:39 2012 florian dewulf
*/
#include	<termios.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	<curses.h>
#include	<term.h>
#include	"42sh.h"

static int     my_putint(int i)
{
  char	c;

  c = i;
  write(1, &c, 1);
  return (0);
}

char	*xtgetstr_exe(char *str, char *cap)
{
  str = tgetstr(cap, NULL);
  if (str == NULL)
    return (NULL);
  if (tputs(str, 1, my_putint) == -1)
    return (NULL);
  return (str);
}
