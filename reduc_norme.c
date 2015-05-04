/*
** reduc_norme.c for 42sh in /home/lund/Dossier courant/42sh/v1.0
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Fri May 18 10:31:31 2012 florian dewulf
** Last update Fri May 18 10:45:46 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		**concate_loop_access(char **path, char **new_path, char *str)
{
  int		pos;

  pos = -1;
  while (path[++pos])
    if ((new_path[pos] = concate(path[pos], str)) == NULL)
      return (my_puterror_null(EXIT_MALLOC));
  new_path[pos] = NULL;
  return (new_path);
}
