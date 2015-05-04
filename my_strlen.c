/*
** my_strlen.c for 42sh in /home/lund/Dossier courant/42sh/func
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri Apr 20 18:36:05 2012 florian dewulf
** Last update Fri Apr 20 18:36:40 2012 florian dewulf
*/

#include	"42sh.h"

int		my_strlen(char *str)
{
  int		curs;

  curs = -1;
  while (str[++curs]);
  return (curs);
}
