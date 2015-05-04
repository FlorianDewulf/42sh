/*
** xchdir.c for 42sh.h in /home/lund/svn/42sh-2016-dewulf_f
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May 18 20:56:34 2012 florian dewulf
** Last update Fri May 18 22:21:37 2012 florian dewulf
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<unistd.h>
#include	"42sh.h"

int		xchdir(char *str)
{
  struct stat	buf;

  if (access(str, F_OK) == -1)
    return (my_puterror_int(FILE_WRONG));
  if (stat(str, &buf) == -1)
    return (my_puterror_int(EXIT_STAT));
  if (S_ISDIR(buf.st_mode) != 1)
    return (my_puterror_int(NO_DIR));
  if (chdir(str) == -1)
    return (my_puterror_int(EXIT_CHDIR));
  return (0);
}
