/*
** paste_all.c for 42sh.h in /home/lund/Dossier courant/42sh/func/termcap
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 18:10:28 2012 florian dewulf
** Last update Sun May 13 00:01:15 2012 florian dewulf
*/

#include	<stdlib.h>
#include	"42sh.h"

char		*paste_all(char **board)
{
  int		nb;
  char		*tmp;
  char		*str;

  nb = -1;
  while (board[++nb])
    if (board[nb][0] != ';')
      board[nb] = epur_space(board[nb]);
  nb = 0;
  if (board[0] == NULL)
    return (NULL);
  str = my_strcpy(board[0]);
  while (board[++nb])
    {
      tmp = concate(str, " ");
      xfree(str);
      str = concate(tmp, board[nb]);
      xfree(tmp);
      xfree(board[nb]);
    }
  return (str);
}
