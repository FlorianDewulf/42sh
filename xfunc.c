/*
** xfunc.c for 42sh in /home/lund/Dossier courant/42sh/func/termcap/pipe
** 
** Made by florian dewulf
** Login   <dewulf_f@epitech.net>
** 
** Started on  Sat May 12 11:24:25 2012 florian dewulf
** Last update Mon May 14 11:46:36 2012 florian dewulf
*/

#include	<stdlib.h>
#include	<unistd.h>

void		xclose(int fd)
{
  if (close(fd) == -1)
    exit(EXIT_FAILURE);
}

void		xdup2(int fd, int fd2)
{
  if (dup2(fd, fd2) == -1)
    exit(EXIT_FAILURE);
}
