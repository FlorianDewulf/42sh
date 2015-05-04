/*
** read_simple.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May 11 21:11:13 2012 florian dewulf
** Last update Fri May 18 00:32:34 2012 florian dewulf
*/

#include	<stdlib.h>
#include	<unistd.h>
#include	"42sh.h"

static int	check_valid_chars(char *buffer)
{
  int		curs;

  curs = -1;
  while (buffer[++curs])
    if (buffer[curs] < ' ' || buffer[curs] >= 127)
      return (1);
  return (0);
}

char		*read_simple(char *str)
{
  char		buffer[512];
  int		ret;

  if (str != NULL)
    xfree(str);
  if ((ret = read(0, buffer, 511)) <= 0)
    return (NULL);
  buffer[ret - 1] = '\0';
  if (check_valid_chars(buffer))
    return (my_strcpy(""));
  str = my_strcpy(buffer);
  if (str)
    return (epur_space(str));
  return (str);
}
