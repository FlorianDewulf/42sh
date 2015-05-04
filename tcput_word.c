/*
** tcput_word.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sun May  6 19:09:52 2012 florian dewulf
** Last update Mon May  7 10:10:36 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

void		tcput_word(char *buff, int begin)
{
  char		*cap;

  cap = NULL;
  while (buff[++begin])
    my_putchar(buff[begin]);
  cap = xtgetstr_exe(cap, "rc");
}
