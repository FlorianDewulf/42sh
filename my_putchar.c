/*
** my_putchar.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May  4 11:16:14 2012 florian dewulf
** Last update Fri May  4 11:16:43 2012 florian dewulf
*/

#include	<unistd.h>
#include	"42sh.h"

void		my_putchar(char c)
{
  write(1, &c, 1);
}
