/*
** xopen.c for 42 in /home/david/Projet/42sh/exec
** 
** Made by david blervaque
** Login   <blerva_d@epitech.net>
** 
** Started on  Thu Apr 26 16:44:16 2012 david blervaque
** Last update Tue May 22 19:51:50 2012 florian dewulf
*/

#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	"42sh.h"

int		xopen(char *name, int index)
{
  int		ret;

  if (index == 0)
    ret = open(name, O_RDWR | O_TRUNC);
  else if (index == 1)
    ret = open(name, O_RDWR | O_APPEND);
  else
    {
      ret = open(name, O_RDONLY);
      if (ret == -1)
	{
	  printf("%s : not exist\n", name);
	  return (-1);
	}
    }
  if (ret == -1)
    ret = open(name, O_RDWR | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC,
	       S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
  return (ret);
}
