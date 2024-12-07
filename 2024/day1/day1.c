#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define TAB_START_SIZE	1024
#define TAB_INCREMENT	512
#define MAX(i, j)	(i < j) ? j : i
#define MIN(i, j)	(i < j) ? i : j
#define ABS(n)		(n < 0) ? n * -1 : n

char	*get_next_line(int fd);
void	tab_sort(int *tab, int size);
int	day1_1(int *t1, int *t2, int size);
int	day1_2(int *t1, int *t2, int size);

int main()
{
  int	*t1;
  int	*t2;
  int	current_elements;
  char	*buffer;
  char	*ptr;
  int	fd;

  fd = open("input", O_RDONLY);
  t1 = malloc(TAB_START_SIZE * sizeof(int));
  t2 = malloc(TAB_START_SIZE * sizeof(int));
  current_elements = 0;
  buffer = get_next_line(fd);
  while (buffer)
    {
      ptr = strchr(buffer, ' ');
      *ptr = '\0';
      t1[current_elements] = atoi(buffer);
      t2[current_elements++] = atoi(ptr + 3);
      free(buffer);
      buffer = get_next_line(fd);
    }
  free(buffer);
  tab_sort(t1, current_elements);
  tab_sort(t2, current_elements);
  printf("day1 - 1 : %d\n", day1_1(t1, t2, current_elements));
  printf("day1 - 2 : %d\n", day1_2(t1, t2, current_elements));
  free(t1);
  free(t2);
  return (0);
}

int day1_1(int *t1, int *t2, int size)
{
  int i;
  int total;
  int diff;

  i = 0;
  total = 0;
  while (i < size)
    {
      diff = t1[i] - t2[i];
      total += ABS(diff);
      ++i;
    }
  return (total);
}

int day1_2(int *t1, int *t2, int size)
{
  int	total;
  int	i;
  int	j;

  total = 0;
  i = 0;
  while (i < size)
    {
      j = 0;
      while (j < size)
	{
	  if (t1[i] == t2[j])
	    total += t1[i];
	  ++j;
	}
      ++i;
    }
  return (total);
}

void tab_sort(int *tab, int size)
{
  int	i;
  int	j;
  int	tmp;

  i = 0;
  while (i < size)
    {
      j = i + 1;
      while (j < size)
	{
	  if (tab[j] < tab[i])
	    {
	      tmp = tab[i];
	      tab[i] = tab[j];
	      tab[j] = tmp;
	    }
	  ++j;
	}
      ++i;
    }
}
