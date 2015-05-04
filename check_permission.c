/*
** check_permission.c for 42sh in /home/lund/svn/42sh-2016-dewulf_f
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May 18 19:29:51 2012 florian dewulf
** Last update Fri May 18 19:48:21 2012 florian dewulf
*/

#include	<unistd.h>
#include	<stdlib.h>
#include	"42sh.h"

int		check_permission(char *str)
{
  if (access(str, F_OK) == -1)
    return (my_puterror_int(NO_FILE));
  else if (access(str, X_OK) == -1)
    return (my_puterror_int(FAIL_PERMI));
  return (0);
}
